# pragma once
class State{
public:
    int id,datetime,Title,BaoJing,KongChe,DingDeng,GaoJia,ShaChe,Satellite,Hint;
    double Speed,Direction;
    int Speed_x,Speed_y,Direction_x,Direction_y;
    int year,month,day;
    int hour,minute,second;
    int longtitude_x,longtitude_y;
    int latitude_x,latitude_y;
    double longtitude,latitude;
    bool takein,takeoff;
    //int BaoJing,KongChe,DingDeng,GaoJia,ShaChe,Speed,Direction,Satellite;

    State(void) ;
    ~State(void) ;
    int get_num(char *s,int &pos);
    void init(char *s,int len);
};
