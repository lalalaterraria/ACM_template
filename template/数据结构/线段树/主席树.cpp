#include<iostream>
using namespace std;
#define mid (l+r)/2;
const int maxn=2e5+10;
int ls[maxn<<5],rs[maxn<<5],sum[maxn<<5];
int tot=0;
void build(int l,int r){
    int rt=++tot;
    sum[rt]=0;
}
void upd(int pre,int l,int r){
    int rt=++tot;
    ls[rt]=ls[pre],rs[rt]=rs[pre],sum[rt]=sum[pre]+1;
    if(l==r){
        return;
    }
    
}