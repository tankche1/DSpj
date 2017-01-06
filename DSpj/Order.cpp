# include "Order.h"
# include<iostream>
# include<fstream>
# include<string>
# include<string.h>
# include<algorithm>
using namespace std;

Order::Order(void) {cnt=0;}

Order::~Order(void) {}

bool Order::cmp(Ord A,Ord B){
    return A.Ti<B.Ti;
}

void Order::insertOrder(){
    char s[1010];
    int len;
    FILE *fin;
    fin=fopen("Order.txt","r");
    if(fin==NULL) puts("Cannot open Order.txt");

    while(fgets(s,1000,fin)){
        len=strlen(s);
        o[cnt].in.init(s,len);
        fgets(s,1000,fin);
        len=strlen(s);
        o[cnt].off.init(s,len);
        o[cnt].Ti=o[cnt].in.hour*3600+o[cnt].in.minute*60+o[cnt].in.second;
        o[cnt].Ti-=300;
        if(o[cnt].Ti<0) o[cnt].Ti+=300;
        o[cnt].st=pair<double,double> (o[cnt].in.longtitude,o[cnt].in.latitude);
        o[cnt].ed=pair<double,double> (o[cnt].off.longtitude,o[cnt].off.latitude);
        cnt++;
    }
    printf("order->cnt:%d\n",cnt);
    sort(o,o+cnt);
}
