# include "POI.h"
# include<stdio.h>
# include<string.h>
# include<fstream>
# include<string>
# include<string.h>
# include<stdlib.h>
# include<algorithm>
using namespace std;

double POI::Dist(pair<double,double> A,pair<double,double> B){
    //地球经纬度坐标差转化距离方法 sqrt( (经度差*cos(平均纬度) *6371km*2*Pi/360)^2+(纬度差*6371km*2*Pi/360)^2
    double res1=(A.first-B.first)*cos((A.second+B.second)/2.0/180.0*PI)*6371*2*PI/360;
    double res2=(A.second-B.second)*6371*2*PI/360;
    return sqrt(res1*res1+res2*res2);
}

void POI::get_rest(Road &road){
    FILE* fin,*fout;
    fin=fopen("POI_restaurant.csv","r");if(fin==NULL) puts("Cannot open!!!");
    //fout=fopen("POIout.txt","w");if(fout==NULL) puts("Cannot Write!!!");
    char s[1010];
    fgets(s,1000,fin);
    while(fgets(s,1000,fin)){
        rest[cnt++].init(s);
        //road.normal(rest[cnt-1].pos);
    }
    fclose(fin);
}

void POI::get_hash(Road &road){
    hashToPOI.clear();
    for(int i=0;i<cnt;i++){
        //printf("hash: %I64x\n",road.geohash(rest[i].pos));
        //if(road.geohash(rest[i].pos)==0) printf("%s (%.4lf,%.4lf)\n",rest[i].name,rest[i].pos.first,rest[i].pos.second);
        hashToPOI[road.geohash(rest[i].pos)]=i;
    }
}


void POI::update(pair<double,double> p,Road &road){
    static double tmp;
    it=hashToPOI.lower_bound(road.geohash(p));
    for(int i=0;i<50;i++){
        if(it==hashToPOI.end()) break;
        tmp=road.Dist(rest[it->second].pos,p);

        if(tmp<2) rest[it->second].tot++;
        else if(tmp<0.5) rest[it->second].tot+=3;

        it++;
    }

    it=hashToPOI.lower_bound(road.geohash(p));
    for(int i=0;i<50;i++){
        if(it==hashToPOI.begin()) break;
        it--;
        tmp=road.Dist(rest[it->second].pos,p);
        if(tmp<2) rest[it->second].tot++;
        else if(tmp<0.5) rest[it->second].tot+=3;
    }
}

void POI::get_tot(Road &road,Order &order){
    for(int i=0;i<order.cnt;i++){
        update(order.o[i].st,road);
        update(order.o[i].ed,road);
    }

    FILE *fout;
    fout=fopen("POIscore.txt","w");if(fout==NULL) puts("Cannot Write!!!");
    for(int i=0;i<cnt;i++){
        fprintf(fout,"%s :%d\n",rest[i].name,rest[i].tot);
    }
}

bool POI::cmp(const pair<int,int> &A,const pair<int,int> &B){
    return A.second>B.second;
}

void POI::Introduce(pair<double,double> p,Road &road){
    int len=0;
    double tmp;
    long long _hash=road.geohash(p);

    it=hashToPOI.lower_bound(_hash);
    for(int i=0;i<50;i++){
        if(it==hashToPOI.end()) break;
        List[len].first=it->second;
        tmp=Dist(p,rest[it->second].pos);
        List[len++].second=(tmp<0.5?2:(tmp<3?1.7:1.4))*rest[it->second].tot;
        it++;
    }

    it=hashToPOI.lower_bound(_hash);
    for(int i=0;i<50;i++){
        if(it==hashToPOI.begin()) break;
        it--;
        List[len].first=it->second;
        tmp=Dist(p,rest[it->second].pos);
        List[len++].second=(tmp<0.5?5:(tmp<3?3:1))*rest[it->second].tot;
    }

    bool ok=true;
    for(int i=0;;i++){
        ok=false;
        for(int j=0;j<len;j++) if(cmp(List[j+1],List[j])) swap(List[j],List[j+1]),ok=true;
        if(!ok) break;
    }
    for(int i=0;i<20&&i<len;i++){
        printf("%d: %s : val:%d score:%d dist:%.2lf\n",i+1,rest[List[i].first].name,rest[List[i].first].tot,List[i].second,Dist(rest[List[i].first].pos,p));
    }
}

void POI::solve(Road &road,Order &order){
    pair<double,double> pos;
    int x;
    get_rest(road);
    get_hash(road);
    get_tot(road,order);

    while(1){
        puts("input your pos ");
        scanf("%lf %lf",&pos.first,&pos.second);
        Introduce(pos,road);
        printf("input 1 to continue;else to break;\n");
        scanf("%d",&x);
        if(x==1) continue;
        else break;
    }
}


