# include "Road.h"

Road::Road(void) {
    p_cnt=road_cnt=0;eps=1e-5;PI=acos(-1.0);memset(used,0,sizeof(used));memset(last,-1,sizeof(last));
}

Road::~Road(void) {}

double Road::Dist(pair<double,double> A,pair<double,double> B){
    //地球经纬度坐标差转化距离方法 sqrt( (经度差*cos(平均纬度) *6371km*2*Pi/360)^2+(纬度差*6371km*2*Pi/360)^2
    double res1=(A.first-B.first)*cos((A.second+B.second)/2.0/180.0*PI)*6371*2*PI/360;
    double res2=(A.second-B.second)*6371*2*PI/360;
    return sqrt(res1*res1+res2*res2);
}

int Road::getId(pair<double,double> p){
    if(!point_id.count(p)){
        point_id[p]=p_cnt;
        point[p_cnt]=p;
        p_cnt++;
    }
    return point_id[p];
}

void Road::normal(pair<double, double > &p){
    int tmp;
    tmp=(int)(p.first*100000);
    p.first=(double)tmp/100000.0;
    tmp=(int)(p.second*100000);
    p.second=(double)tmp/100000.0;
}

void Road::getRoad(){
    //puts("hei!!");
    int len,a,b,tmp;
    FILE* fin;
    fin=fopen(string("C:/Trajectory/RoadNetwork.csv").c_str(),"r");
    if(fin==NULL) puts("Cannot open RoadNetwork.csv");
    char s[1010];
    fgets(s,1000,fin);//去掉第一行
    pair<double,double> now,last;
    bool have_last=0;
    while(fgets(s,1000,fin)){
        len=strlen(s);
        if(len<10){
            have_last=0;
            continue;
        }

        sscanf(s,"%lf,%lf",&now.second,&now.first);
        normal(now);

        if(have_last){
            a=getId(last);b=getId(now);
            road[a].push_back(b);road[b].push_back(a);road_cnt++;
        }

        last=now;have_last=1;
    }
    printf("road_cnt:%d p_cnt:%d\n",road_cnt,p_cnt);

}

long long Road::geohash(pair<double,double> p){
    //double x_down=120.0,x_up=123.0,x_mid,y_down=30.0,y_up=33.0,y_mid;
    double x_down=0,x_up=180,x_mid,y_down=20,y_up=45,y_mid;
    long long res=0;
    for(int i=0;i<31;i++){
        x_mid=(x_down+x_up)/2.0;
        if(p.first<=x_mid) res=res<<1,x_up=x_mid;
        else res=(res<<1)|1,x_down=x_mid;

        y_mid=(y_down+y_up)/2.0;
        if(p.second<=y_mid) res=res<<1,y_up=y_mid;
        else res=(res<<1)|1,y_down=y_mid;
    }
    return res;
}

void Road::getAllhash(){
    hashTopoint.clear();
    for(int i=0;i<p_cnt;i++){
        phash[i]=geohash(point[i]);
        //if(hashTopoint.count(phash[i])) puts("There are coincide point!");
        hashTopoint[phash[i]]=i;
        //printf("i:%d %.7f %.7f hash:%I64x\n",i,point[i].first,point[i].second,phash[i]);
    }

    /*map<long long,int>::iterator it;
    for(it=hashTopoint.begin();it!=hashTopoint.end();it++){
        printf("(%.2lf,%.2lf)\n",point[it->second].first,point[it->second].second);
    }*/
}

double Road::pointToseg(pair<double,double> P,pair<double,double> A,pair<double,double> B){
    //A.first*=jingdu;A.second*=weidu;P.first*=jingdu;P.second*=weidu;
    //B.first*=jingdu;B.second*=weidu;
    double cross=(B.first-A.first)*(P.first-A.first)+(B.second-A.second)*(P.second-A.second);
    if(cross<=0) return sqrt((P.first-A.first)*(P.first-A.first)+(P.second-A.second)*(P.second-A.second));

    double d2=(B.first-A.first)*(B.first-A.first)+(B.second-A.second)*(B.second-A.second);
    if(cross>=d2) return sqrt((P.first-B.first)*(P.first-B.first)+(P.second-B.second)*(P.second-B.second));

    double r=cross/d2;
    pair<double,double> C;
    C.first=A.first+(B.first-A.first)*r;
    C.second=A.second+(B.second-A.second)*r;
    return sqrt((P.first-C.first)*(P.first-A.first)+(P.second-A.second)*(P.second-A.second));
    //return Dist(P,realPointonRoad(P,A,B));
}


pair<int,int> Road::findNearestRoad(pair<double,double> p){
    static map<long long,int>::iterator it;
    static pair< int,int > ans;
    static double dist;dist=1000000;
    static int st;
    static long long _hash;_hash=geohash(p);
    normal(p);

    it=hashTopoint.lower_bound(_hash);
    for(int i=0;i<10;i++){
        it++;
        if(it==hashTopoint.end()) break;
        st=it->second;
        for(int e=0;e<(int)road[st].size();e++){
            if(pointToseg(p,point[st],point[road[st][e]])<dist){
                dist=pointToseg(p,point[st],point[road[st][e]]);ans.first=st;ans.second=road[st][e];
            }
        }
    }

    it=hashTopoint.lower_bound(_hash);
    for(int i=0;i<10;i++){
        if(it==hashTopoint.begin()) break;
        it--;
        st=it->second;
        for(int e=0;e<(int)road[st].size();e++){
            if(pointToseg(p,point[st],point[road[st][e]])<dist){
                dist=pointToseg(p,point[st],point[road[st][e]]);ans.first=st;ans.second=road[st][e];
            }
        }
    }
    return ans;
}

pair<double,double> Road::realPointonRoad(pair<double,double> P,pair<double,double> A,pair<double,double> B){
    double cross=(B.first-A.first)*(P.first-A.first)+(B.second-A.second)*(P.second-A.second);
    if(cross<=0) return A;

    double d2=(B.first-A.first)*(B.first-A.first)+(B.second-A.second)*(B.second-A.second);
    if(cross>=d2) return B;

    double r=cross/d2;
    pair<double,double> C;
    C.first=A.first+(B.first-A.first)*r;
    C.second=A.second+(B.second-A.second)*r;
    return C;
}

double Road::shortestPath(int st1,int st2,pair<double,double> pst,int ed1,int ed2,pair<double,double> ped){
    while(!Q.empty()) Q.pop();
    while(Stack_top>=0) {used[Stack[Stack_top]]=0;last[Stack[Stack_top--]]=-1;}
    Q.push(HeapNode(st1,Dist(point[st1],ped)+Dist(pst,point[st1]),Dist(pst,point[st1]),st1));
    Q.push(HeapNode(st2,Dist(point[st2],ped)+Dist(pst,point[st2]),Dist(pst,point[st2]),st2));

    Stack_top=-1;
    static bool found;found=false;
    static double ans;ans=0;
    static int x;
    static double base;
    static int from;
    while(!Q.empty()){
        x=Q.top().u;
        base=Q.top().real;
        from=Q.top().from;
        Q.pop();
        if(used[x]) continue;
        last[x]=from;used[x]=1;Stack[++Stack_top]=x;
        if(x==ed1||x==ed2){
            found=true;ans=base;break;
        }

        for(int e=0;e<road[x].size();e++){
            Q.push(HeapNode(road[x][e],base+Dist(point[road[x][e]],point[x])+Dist(point[road[x][e]],ped),base+Dist(point[road[x][e]],point[x]),x));
        }
    }

    if(!found){
        puts("I am a helicopter!");return ans=Dist(pst,ped);
    }

    return ans;
}

