# pragma once
# include<map>
# include<vector>
# include<iostream>
# include<string.h>
# include<math.h>
# include<queue>
# include<fstream>
# include<algorithm>
using namespace std;
# define maxn 210010
# define maxm 400000

# define weidu 111
# define jingdu 96

class Road
{
public:
    map<pair<double,double> ,int>point_id;//把坐标映射到点
    map<long long,int> hashTopoint;//把hash映射到点
    pair<double,double> point[maxn];
    vector<int> road[maxn];
    int p_cnt;
    int road_cnt;
    double eps,PI;
    int last[maxn];
    long long phash[maxn];

    typedef struct HeapNode{
        int u;double dis;double real;int from;
        HeapNode() {}
        HeapNode(int u,double dis,double real,int from):u(u),dis(dis),real(real),from(from) {}
        bool operator <(const HeapNode &rhs)const{
            return dis>rhs.dis;
        }
    }HeapNode;

    priority_queue<HeapNode> Q;
    bool used[maxn];
    int Stack[maxn],Stack_top;

    Road(void);
    ~Road(void);

    double Dist(pair<double,double> A,pair<double,double> B);
    void normal(pair<double,double> &p);
    long long geohash(pair<double,double> p);
    int getId(pair<double,double> p);
    void getRoad();
    void getAllhash();
    double pointToseg(pair<double,double> P,pair<double,double> A,pair<double,double> B);
    pair<int,int> findNearestRoad(pair<double,double> p);//找到离p点最近的边(a,b)
    pair<double,double> realPointonRoad(pair<double,double> P,pair<double,double> A,pair<double,double> B);//返回p点的投影
    double shortestPath(int st1,int st2,pair<double,double> p,int ed1,int ed2,pair<double,double> ped);

};
