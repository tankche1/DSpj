# pragma once
# include "State.h"

/*
This code intend to calculate the driver's profit in real date
*/

class Basic{
public:
    double PI;
    State st[10010];
    double hour_income[24],hour_outcome[24];

    Basic(void);
    ~Basic(void);

    double Dist(State A,State B);
    void solve();
    void getDriver();

    void getOrder();
};
