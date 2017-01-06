# include "State.h"

State::State(void) {}
State::~State(void) {}

int State::get_num(char *s,int &pos){
    while(s[pos]<'0'||s[pos]>'9') pos++;
    int tmp=0;
    while(s[pos]>='0'&&s[pos]<='9'){
        tmp=tmp*10+s[pos]-'0';pos++;
    }
    return tmp;
}

void State::init(char *s,int len){
        int pos=0;
        id=get_num(s,pos);
        year=get_num(s,pos);;
        month=get_num(s,pos);;
        day=get_num(s,pos);
        hour=get_num(s,pos);;
        minute=get_num(s,pos);;
        second=get_num(s,pos);
        longtitude_x=get_num(s,pos);;
        longtitude_y=get_num(s,pos);
        latitude_x=get_num(s,pos);;
        latitude_y=get_num(s,pos);
        BaoJing=get_num(s,pos);
        KongChe=get_num(s,pos);
        DingDeng=get_num(s,pos);
        GaoJia=get_num(s,pos);
        ShaChe=get_num(s,pos);
        Speed_x=get_num(s,pos);Speed_y=get_num(s,pos);
        Speed=(double)Speed_x+(double)Speed_y*0.000001;
        Direction_x=get_num(s,pos);Direction_y=get_num(s,pos);
        Direction=(double)Direction_x+(double)Direction_y*0.000001;
        Satellite=get_num(s,pos);
        takein=takeoff=0;
        longtitude=(double)longtitude_x+(double)longtitude_y*0.000001;
        latitude=(double)latitude_x+(double)latitude_y*0.000001;
        //printf("%.6f %.6f\n",longtitude,latitude);
        int tt=pos+10;
        for(;pos<len&&pos<tt;pos++){
            if(s[pos]=='T'&&s[pos+1]=='a'&&s[pos+2]=='k'&&s[pos+3]=='e'){
                if(s[pos+4]=='O') takeoff=1;
                else takein=1;
                break;
            }
        }
}
