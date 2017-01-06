# pragma once
# include "basic_analysis.h"
# include "Road.h"
# include "Order.h"
# include "State.h"
# include   <map>

class Stay
{
public:
    map<long long,int> hashToorder;
    map<long long,int>::iterator it;
    void normalOrder(Order &order,Road &road);
    int getNearestorder(pair<double,double> pos,Road &road,Order &order);
    void stayStrategy(Order &order,Road &road);
    void lowStrategy(Order &order,Road &road);
};
