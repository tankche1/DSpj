/*
This code intend to calculate the driver's profit in real date
*/

# include "basic_analysis.h"
# include<math.h>
# include<iostream>
# include<fstream>
# include<string>
# include<string.h>
# include<algorithm>
using namespace std;

Basic::Basic(void) {
    PI=acos(-1.0);
    memset(hour_income,0,sizeof(hour_income));
    memset(hour_outcome,0,sizeof(hour_outcome));
}

Basic::~Basic(void) {}

double Basic::Dist(State A,State B){
    //地球经纬度坐标差转化距离方法 sqrt( (经度差*cos(平均纬度) *6371km*2*Pi/360)^2+(纬度差*6371km*2*Pi/360)^2
    double res1=(A.longtitude-B.longtitude)*cos((A.latitude+B.latitude)/2.0/180.0*PI)*6371*2*PI/360;
    double res2=(A.latitude-B.latitude)*6371*2*PI/360;
    return sqrt(res1*res1+res2*res2);
}

void Basic::solve(){
    char row[1010],need[1010];
    double average=0;
    FILE* fin,*fout;
    fout=fopen("Basicout.txt","w");
    if(fout==NULL) puts("Cannot Write!!!");

    int cnt=0;
    for(int Drive_bh=6961;Drive_bh<=12843;Drive_bh++){
        cnt=0;
        sprintf(need,"%d",Drive_bh);
        fin=fopen(string("C:/Trajectory/Trajectory/[part-00000][" + string(need) + "]Sample.csv").c_str(),"r");
        if(fin==NULL) puts("Cannot open!!!");

        fgets(row,1000,fin);
        double dist=0,income=0,outcome=0,tmp;
        bool ok=false;

        while(fgets(row,1000,fin)){
            int len=strlen(row);
            if(len<10) continue;
            st[cnt].init(row,len);

            if(st[cnt].takein){
                dist=0;
                ok=true;
            }
            if(cnt>0&&((st[cnt-1].longtitude!=st[cnt].longtitude)||(st[cnt-1].latitude!=st[cnt].latitude)))
                tmp=Dist(st[cnt-1],st[cnt]);
            else {tmp=0;}

            if(tmp>0){
                outcome+=tmp*0.5;
                hour_outcome[st[cnt].hour]+=tmp;
            }
            if(st[cnt].DingDeng==0&&(!st[cnt].takein))
                dist+=tmp;

            if(st[cnt].takeoff){
                if(dist<0.25) ;
                else{
                    if(dist<=3) income+=14;
                    else income+=14+2.4*(dist-3);
                    hour_income[st[cnt].hour]+=income;
                }
                dist=0;
            }
            cnt++;
        }
        fprintf(fout,"Drive_bh:%d income:%.2f outcome:%.2f profit:%.2f\n",Drive_bh,income,outcome,income-outcome);
        average+=income-outcome;
        if(Drive_bh%100==0) printf("Drive_bh:%d\n",Drive_bh);
        fclose(fin);
    }
    average=average/((12843-6961+1)*1.0);
    printf("average:%.2f\n",average);
    fprintf(fout,"average:%.2f\n",average);

    for(int i=0;i<24;i++) fprintf(fout,"hour:%d - %d income:%.2f outcome:%.2f profit:%.2f \n",
                                 i,i+1,hour_income[i],hour_outcome[i],hour_income[i]-hour_outcome[i]);
    for(int i=0;i<24;i++) printf("hour:%d - %d income:%.2f outcome:%.2f profit:%.2f \n",
                                 i,i+1,hour_income[i],hour_outcome[i],hour_income[i]-hour_outcome[i]);
    fclose(fout);
}

void Basic::getOrder(){
    string s;
    char row[1010];
    char need[100];
    char _row[1010];
    FILE* fin,*fout;
    fout=fopen("Order.txt","w");
    if(fout==NULL) puts("Cannot Write!!!");

    int cnt=0;
    for(int Drive_bh=6961;Drive_bh<=12843;Drive_bh++){
        cnt=0;
        sprintf(need,"%d",Drive_bh);
        fin=fopen(string("C:/Trajectory/Trajectory/[part-00000][" + string(need) + "]Sample.csv").c_str(),"r");
        if(fin==NULL) puts("Cannot open!!!");

        fgets(row,1000,fin);;
        int last;
        bool ok=false;

        while(fgets(row,1000,fin)){
            int len=strlen(row);
            if(len<10) continue;
            st[cnt].init(row,len);
            if(st[cnt].takein) memcpy(_row,row,sizeof(row));
            if(st[cnt].takein) ok=true;
            if(st[cnt].takeoff&&ok) {fprintf(fout,"%s",_row);fprintf(fout,"%s",row);}
            cnt++;
        }

        if(Drive_bh%100==0) printf("Drive_bh:%d\n",Drive_bh);
        fclose(fin);
    }
    fclose(fout);
}

void Basic::getDriver(){
    State info;
    char row[1010],need[1010];
    FILE* fin,*fout;
    fout=fopen("driver.txt","w");
    if(fout==NULL) puts("Cannot Write!!!");

    int cnt=0;
    for(int Drive_bh=6961;Drive_bh<=12843;Drive_bh++){
        bool time0=false,time1=false,time2=false,time3=false;
        cnt=0;
        sprintf(need,"%d",Drive_bh);
        fin=fopen(string("C:/Trajectory/Trajectory/[part-00000][" + string(need) + "]Sample.csv").c_str(),"r");
        if(fin==NULL) puts("Cannot open!!!");

        fgets(row,1000,fin);
        bool ok=false;

        while(fgets(row,1000,fin)){
            int len=strlen(row);
            if(len<10) continue;
            info.init(row,len);
            if(!time0&&info.hour<6) {time0=1;fprintf(fout,"%s",row);}
            if(!time1&&(info.hour>=6&&info.hour<12)) {time1=1;fprintf(fout,"%s",row);}
            if(!time2&&(info.hour>=12&&info.hour<18)) {time2=1;fprintf(fout,"%s",row);}
            if(!time3&&(info.hour>=18&&info.hour<24)) {time3=1;fprintf(fout,"%s",row);}

        }
        if((!time0)||(!time1)||(!time2)||(!time3)) {printf("oops!!! %d\n",Drive_bh);}
        if(Drive_bh%100==0) printf("Drive_bh:%d\n",Drive_bh);
        fclose(fin);
    }
    fclose(fout);
}
