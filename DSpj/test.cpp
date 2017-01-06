# include <iostream>
# include "basic_analysis.h"
# include "Road.h"
# include "Order.h"
# include "State.h"
# include "stayStrategy.h"

using namespace std;

Basic basic;
Road road;
Order order;

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
    stayStrategy(order,road);
}



int main()
{
    //solve_Basic();
    //getOrder();
    //getDriver();
    getRoad();
    getHash();
    pushOrder();

    return 0;
}
