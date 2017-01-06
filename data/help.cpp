# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;

int belong(double x){
    if(x<1300) return (int)(x)/100;
    else return 13;
}
int data[50];

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    double x;
    while(scanf("%lf",&x)==1){
            //printf("%.3lf\n",x);
        data[belong(x)]++;
        //printf("%.3lf\n",x);
    }
    for(int i=0;i<=12;i++) printf("%d-%d,%d\n",(i)*100,(i+1)*100,data[i]);
    printf(">=1300,%d\n",data[13]);
    return 0;
}
