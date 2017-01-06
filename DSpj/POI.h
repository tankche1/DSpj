# pragma once
# include "basic_analysis.h"
# include "Road.h"
# include "Order.h"
# include "State.h"
# include   <map>
# include<math.h>
# include<string.h>
# define maxn 140000
using namespace std;

class POI
{
public:
    POI() {cnt=0;PI=acos(-1.0);}
    ~POI() {}
    typedef struct Rest{
        pair<double,double> pos;
        int tot;
        char name[200];

        Rest() {tot=0;}
        void init(char *s){
            //puts(s);
            int len=strlen(s),tpos;
            for(tpos=0;tpos<len;tpos++){
                name[tpos]=s[tpos];
                if(s[tpos]==',') {tpos++;break;}
            }
            for(;tpos<len;tpos++){
                name[tpos]=s[tpos];
                if(s[tpos]==',') {tpos++;break;}
            }name[tpos]='\0';
            sscanf(s+tpos,"%lf,%lf",&pos.first,&pos.second);
            //printf("pos!! :%.3lf %.3lf\n",pos.first,pos.second);
        }
    }Rest;
    Rest rest[maxn];
    pair<int,int> List[500];
    int cnt;
    double PI;
    map<long long,int> hashToPOI;
    map<long long,int>::iterator it;

    double Dist(pair<double,double> A,pair<double,double> B);
    bool cmp(const pair<int,int> &A,const pair<int,int> &B);
    void update(pair<double,double> p,Road &road);
    void get_rest(Road &road);
    void get_tot(Road &road,Order &order);
    void get_hash(Road &road);
    void Introduce(pair<double,double> p,Road &road) ;
    void solve(Road &road,Order &order);

};
