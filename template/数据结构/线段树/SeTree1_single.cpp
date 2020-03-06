#include<iostream>
using namespace std;
#define ls rt<<1
#define rs rt<<1|1
#define mid (l+r)/2
#define ll long long
ll t[4000010];
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
int a[1000010];
void build(int rt,int l,int r){
    // cout<<rt<<" "<<l<<" "<<r<<endl;
    if(l==r){
        t[rt]=a[l];
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    php(rt);
}
int main(){
    ios::sync_with_stdio;cin.tie(0);
    int n,q;cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    for(int i=1;i<=q;i++){
        int t,a,b;cin>>t>>a>>b;
        if(t==1){
            upd(1,1,n,a,b);
        }
        else cout<<que(1,1,n,a,b)<<'\n';
    }
}