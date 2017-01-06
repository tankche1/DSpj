# include <iostream>
# include "basic_analysis.h"
# include "Road.h"
# include "Order.h"
# include "State.h"
# include "stayStrategy.h"
# include "POI.h"

using namespace std;

Basic basic;
Road road;
Order order;
Stay stay;
POI poi;

/*
    This code can solve the basic analysis problem
    read from C:/Trajectory/Trajectory/ and write at Basicout.txt
*/
void solve_Basic(){
    basic.solve();
}

/*
    getOrder�������԰�����takein��takeout�Ķ�����Ϣ�ҵ��������Order.txt
*/
void getOrder(){
    basic.getOrder();
}

/*
�������˾�����ĸ�ʱ�εĳ�ʼ���ݵ�driver.txt
*/
void getDriver(){
    basic.getDriver();
}

/*
��RoadNetwork.csv�а�·����Ϣ�洢���� ʹ��map�Ѿ�γ��ӳ�䵽�� ʹ��vector���
*/

void getRoad(){
    road.getRoad();
}

/*
�õ�ÿ�����geohashֵ
*/
void getHash(){
    road.getAllhash();
}

/*
�õ����ж������ҷ���Order������
*/
void pushOrder(){
    order.insertOrder();
}



/*
���ԭ�ش�����������˾��������ʱ�������stayout.txt
*/
void calcstayStrategy(){
    stay.stayStrategy(order,road);
}

/*
�������Ѳ�β�������˾��������ʱ�������lowout.txt
*/
void calclowStrategy(){
    stay.lowStrategy(order,road);
}

/*
������POI�Ĳ͹���һ����ֵval ��val�����POI_restaurant.txt
���ҿ�������ص�ľ�γ�ȣ�����20������ȵĲ�����
*/
void calcPOI(){
    poi.solve(road,order);
}

int main()
{
    //printf("%.2lf\n",road.Dist(pair<double,double>(130.0,30.0),pair<double,double>(130.0,31.0)));
    //printf("%.2lf\n",road.Dist(pair<double,double>(131.0,30.0),pair<double,double>(130.0,30.0)));
    //solve_Basic();
    //getOrder();
    //getDriver();
    getRoad();
    getHash();
    pushOrder();
    //calcstayStrategy();
    calclowStrategy();
    //calcPOI();
    return 0;
}
