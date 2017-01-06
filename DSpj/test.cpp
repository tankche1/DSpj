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
    getOrder函数可以把所有takein和takeout的订单信息找到并输出到Order.txt
*/
void getOrder(){
    basic.getOrder();
}

/*
输出所有司机在四个时段的初始数据到driver.txt
*/
void getDriver(){
    basic.getDriver();
}

/*
从RoadNetwork.csv中把路的信息存储下来 使用map把经纬度映射到点 使用vector存边
*/

void getRoad(){
    road.getRoad();
}

/*
得到每个点的geohash值
*/
void getHash(){
    road.getAllhash();
}

/*
得到所有订单并且放在Order类里面
*/
void pushOrder(){
    order.insertOrder();
}



/*
输出原地待命策略所有司机的利润及时间段利润到stayout.txt
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
