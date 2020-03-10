// https://loj.ac/problem/130
#include<iostream>
using namespace std;
#define ll long long

struct SeTree_single{
    #define ls rt<<1
    #define rs rt<<1|1
    #define mid (l+r)/2
    ll t[1000010<<2];
    void php(int rt){t[rt]=t[ls]+t[rs];}
    void upd(int rt,int l,int r,int x,int y){
        if(l==r){
            t[rt]+=y;
            return;
        }
        if(x<=mid)upd(ls,l,mid,x,y);
        else upd(rs,mid+1,r,x,y);
        php(rt);
    }
    ll que(int rt,int l,int r,int x,int y){
        if(x<=l&&r<=y){
            return t[rt];
        }
        ll ret=0;
        if(x<=mid)ret+=que(ls,l,mid,x,y);
        if(y>mid)ret+=que(rs,mid+1,r,x,y);
        return ret;
    }
    void build(int rt,int l,int r,int a[]){
        if(l==r){
            t[rt]=a[l];
            return;
        }
        build(ls,l,mid,a);
        build(rs,mid+1,r,a);
        php(rt);
    }
} tr;

int a[1000010];
int main(){
    ios::sync_with_stdio;cin.tie(0);
    int n,q;cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    tr.build(1,1,n,a);
    for(int i=1;i<=q;i++){
        int t,a,b;cin>>t>>a>>b;
        if(t==1){
            tr.upd(1,1,n,a,b);
        }
        else cout<<tr.que(1,1,n,a,b)<<'\n';
    }
}