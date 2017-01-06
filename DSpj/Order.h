# pragma once
# include "State.h"
# include<stdio.h>
# include<algorithm>
using namespace std;

# define N 210000

class Order
{
public:
    Order(void);
    ~Order(void);
    typedef struct Ord{
        State in,off;
        pair<double,double> st,ed;
        pair<int,int> passenger,dest;
        double dist;
        int Ti;
        Ord() {}
        bool operator <(const Ord &rhs)const{
            return Ti<rhs.Ti;
        }
    }Ord;
    Ord o[N];
    int cnt;

    bool cmp(Ord A,Ord B);
    void insertOrder();
};
