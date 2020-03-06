#include<iostream>
using namespace std;
#define ls rt<<1
#define rs rt<<1|1
#define mid (l+r)/2
#define ll long long
ll t[1000010<<2],laz[1000010<<2];
void php(int rt){t[rt]=t[ls]+t[rs];}
void phd(int rt,int l,int r){
    if(laz[rt]){
        t[ls]+=laz[rt]*(mid-l+1);
        laz[ls]+=laz[rt];

        t[rs]+=laz[rt]*(r-mid);
        laz[rs]+=laz[rt];
        
        laz[rt]=0;
    }
}
void upd(int rt,int l,int r,int x,int y,int z){
    if(x<=l&&r<=y){
        t[rt]+=1ll*z*(r-l+1);
        laz[rt]+=z;
        return;
    }
    phd(rt,l,r);
    if(x<=mid)upd(ls,l,mid,x,y,z);
    if(y>mid)upd(rs,mid+1,r,x,y,z);
    php(rt);
}
ll que(int rt,int l,int r,int x,int y){
    if(x<=l&&r<=y){
        return t[rt];
    }
    phd(rt,l,r);
    ll ret=0;
    if(x<=mid)ret+=que(ls,l,mid,x,y);
    if(y>mid)ret+=que(rs,mid+1,r,x,y);
    return ret;
}
int a[1000010];
void build(int rt,int l,int r){
    if(l==r){
        t[rt]=a[l];
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    php(rt);
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,q;cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    for(int i=1;i<=q;i++){
        int tag,a,b;cin>>tag>>a>>b;
        if(tag==1){
            int x;cin>>x;
            upd(1,1,n,a,b,x);
        }
        else {
            cout<<que(1,1,n,a,b)<<"\n";
        }
    }
}
