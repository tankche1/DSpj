# include<string.h>
# include<fstream>
# include<string>
# include<string.h>
# include "Order.h"
# include "Road.h"
# include "stayStrategy.h"
using namespace std;

void Stay::normalOrder(Order &order,Road &road){
    static pair<int,int> dest;
    for(int i=0;i<order.cnt;i++){
        order.o[i].passenger=road.findNearestRoad(order.o[i].st);
        order.o[i].dest=road.findNearestRoad(order.o[i].ed);
    }
}

int Stay::getNearestorder(pair<double,double> pos,Road &road,Order &order){
    static int ans;ans=-1;
    static double dist;dist=100000;
    it=hashToorder.lower_bound(road.geohash(pos));
    for(int i=0;i<5;i++){
        if(it==hashToorder.end()) break;
        if(road.Dist(order.o[it->second].st,pos)<dist)
            dist=road.Dist(order.o[it->second].st,pos),ans=it->second;
        it++;
    }

    it=hashToorder.lower_bound(road.geohash(pos));
    for(int i=0;i<5;i++){
        if(it==hashToorder.begin()) break;
        it--;
        if(road.Dist(order.o[it->second].st,pos)<dist)
            dist=road.Dist(order.o[it->second].st,pos),ans=it->second;

    }
    return ans;
}

void Stay::stayStrategy(Order &order,Road &road){
    normalOrder(order,road);
    int limit[4]={6*3600,12*3600,18*3600,24*3600};
    State driver;
    pair<double,double> pos;
    double Ti;
    char s[1010];int len;
    double average[4]={0,0,0,0};
    double money[4];

    FILE* fin,*fout;
    fin=fopen("driver.txt","r");if(fin==NULL) puts("Cannot open!!!");
    fout=fopen("stayout.txt","w");if(fout==NULL) puts("Cannot Write!!!");

    int cnt=0,orderBh=0,want;
    double dist1,dist2;
    pair<int,int> passenger,driv,dest;

    for(int Drive_bh=6961;Drive_bh<=12843;Drive_bh++){
        printf("Acting as %d\n",Drive_bh);
        money[0]=money[1]=money[2]=money[3]=0;
        hashToorder.clear();
        orderBh=0;

        for(int i=0;i<4;i++){
            fgets(s,1000,fin);len=strlen(s);
            driver.init(s,len);
            pos=pair<double,double>(driver.longtitude,driver.latitude);
            Ti=driver.hour*3600+driver.minute*60+driver.second;
            while(Ti>limit[i]) i++;


            while(1){
                if(Ti>limit[i]) break;
                while(orderBh<order.cnt&&order.o[orderBh].Ti<Ti){
                    hashToorder[road.geohash(order.o[orderBh].st)]=orderBh;
                    orderBh++;
                }
                want=-1;
                want=getNearestorder(pos,road,order);
                if(want!=-1&&road.Dist(pos,order.o[want].st)>3) want=-1;
                if(want==-1) {Ti=Ti+200;continue;}
                passenger=order.o[want].passenger;
                driv=road.findNearestRoad(pos);

                dest=order.o[want].dest;
                dist1=road.shortestPath(driv.first,driv.second,pos,passenger.first,passenger.second,order.o[want].st);
                dist2=road.shortestPath(passenger.first,passenger.second,order.o[want].st,dest.first,dest.second,order.o[want].ed);
                it=hashToorder.find(road.geohash(order.o[want].st));
                hashToorder.erase(it);

                money[i]+=(dist2>=3?(14+2.4*(dist2-3)):14)-(dist1+dist2)*0.5;
                Ti+=(dist1+dist2)/40*3600;
                pos=order.o[want].ed;
            }

        }
        fprintf(fout,"(%d,%.2lf,%.2lf,%.2lf,%.2lf)\n",Drive_bh,money[0],money[1],money[2],money[3]);
        printf("(%d,%.2lf,%.2lf,%.2lf,%.2lf)\n",Drive_bh,money[0],money[1],money[2],money[3]);

        average[0]+=money[0];average[1]+=money[1];average[2]+=money[2];average[3]+=money[3];

        //if(Drive_bh%100==0) printf("Drive_bh:%d\n",Drive_bh);

    }
    fprintf(fout,"average0:%.2lf\n",average[0]);
    fprintf(fout,"average1:%.2lf\n",average[1]);
    fprintf(fout,"average2:%.2lf\n",average[2]);
    fprintf(fout,"average3:%.2lf\n",average[3]);

    fclose(fin);
    fclose(fout);
}

void Stay::lowStrategy(Order &order,Road &road){
    normalOrder(order,road);
    int limit[4]={6*3600,12*3600,18*3600,24*3600};
    State driver;
    pair<double,double> pos;
    double Ti,tmp;
    char s[1010];int len;
    double average[4]={0,0,0,0};
    double money[4];

    FILE* fin,*fout;
    fin=fopen("driver.txt","r");if(fin==NULL) puts("Cannot open!!!");
    fout=fopen("lowout.txt","w");if(fout==NULL) puts("Cannot Write!!!");

    int cnt=0,orderBh=0,now,want,x,lastTi;
    double dist1,dist2;
    pair<int,int> passenger,driv,dest;
    vector<int> path;

    for(int Drive_bh=6961;Drive_bh<=12843;Drive_bh++){
    //for(int Drive_bh=7322;Drive_bh<=12843;Drive_bh++){
        printf("Acting as %d\n",Drive_bh);
        money[0]=money[1]=money[2]=money[3]=0;
        hashToorder.clear();
        orderBh=0;

        for(int i=0;i<4;i++){
            fgets(s,1000,fin);len=strlen(s);
            driver.init(s,len);
            pos=pair<double,double>(driver.longtitude,driver.latitude);
            Ti=driver.hour*3600+driver.minute*60+driver.second;
            while(Ti>limit[i]) i++;

            now=-1;
            while(1){
                if(Ti>limit[i]) break;
                while(orderBh<order.cnt&&order.o[orderBh].Ti<Ti){
                    hashToorder[road.geohash(order.o[orderBh].st)]=orderBh;
                    orderBh++;
                }
                want=-1;
                want=getNearestorder(pos,road,order);
                if(want==-1) {Ti=Ti+200;continue;}
                if(road.Dist(pos,order.o[want].st)<3){
                    passenger=order.o[want].passenger;
                    driv=road.findNearestRoad(pos);

                    dest=order.o[want].dest;
                    dist1=road.shortestPath(driv.first,driv.second,pos,passenger.first,passenger.second,order.o[want].st);
                    dist2=road.shortestPath(passenger.first,passenger.second,order.o[want].st,dest.first,dest.second,order.o[want].ed);
                    it=hashToorder.find(road.geohash(order.o[want].st));
                    hashToorder.erase(it);

                    money[i]+=(dist2>=3?(14+2.4*(dist2-3)):14)-(dist1+dist2)*0.5;
                    Ti+=(dist1+dist2)/40*3600;
                    pos=order.o[want].ed;
                }
                else{
                    driv=road.findNearestRoad(pos);
                    passenger=order.o[want].passenger;
                    road.shortestPath(driv.first,driv.second,pos,passenger.first,passenger.second,order.o[want].st);
                    if(road.last[passenger.first]==-1) swap(passenger.first,passenger.second);
                    x=passenger.first;
                    if(road.last[x]==-1){
                        puts("FLY!!!");it=hashToorder.find(road.geohash(order.o[want].st));hashToorder.erase(it);
                        pos=order.o[want].st;
                        continue;
                    }
                    path.clear();path.push_back(x);
                    //printf("st1:%d st2:%d ed1:%d ed2:%d\n",driv.first,driv.second,passenger.first,passenger.second);
                    while(road.last[x]!=driv.first&&road.last[x]!=driv.second){
                        path.push_back(road.last[x]);
                        //printf("x:%d\n",x);
                        x=road.last[x];
                    }
                    reverse(path.begin(),path.end());
                    lastTi=Ti;
                    if((int)path.size()==1){
                        it=hashToorder.find(road.geohash(order.o[want].st));
                        hashToorder.erase(it);
                        continue;
                    }
                    for(int e=0;e<(int)path.size();e++){
                        tmp=road.Dist(pos,road.point[path[e++]]);
                        money[i]-=tmp*0.5;
                        Ti+=tmp/10*3600;
                        pos=road.point[path[e-1]];
                        if(Ti-lastTi>300){
                            lastTi=Ti;
                            want=getNearestorder(pos,road,order);
                            if(road.Dist(pos,order.o[want].st)<3) break;
                        }
                    }
                }

            }

        }
        fprintf(fout,"(%d,%.2lf,%.2lf,%.2lf,%.2lf)\n",Drive_bh,money[0],money[1],money[2],money[3]);
        printf("(%d,%.2lf,%.2lf,%.2lf,%.2lf)\n",Drive_bh,money[0],money[1],money[2],money[3]);

        average[0]+=money[0];average[1]+=money[1];average[2]+=money[2];average[3]+=money[3];

    }
    fprintf(fout,"average0:%.2lf\n",average[0]);
    fprintf(fout,"average1:%.2lf\n",average[1]);
    fprintf(fout,"average2:%.2lf\n",average[2]);
    fprintf(fout,"average3:%.2lf\n",average[3]);

    fclose(fin);
    fclose(fout);
}
