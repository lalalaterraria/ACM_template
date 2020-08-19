#include<iostream>
using namespace std;
#define ll long long
struct SeTree_sum{
    #define ls rt<<1
    #define rs rt<<1|1
    #define mid (l+r)/2

    ll t[1000010<<2],laz[1000010<<2];
    void php(int rt){t[rt]=t[ls]+t[rs];}
    void phd(int rt,int l,int r){
        t[ls]+=laz[rt]*(mid-l+1);laz[ls]+=laz[rt];
        t[rs]+=laz[rt]*(r-mid);laz[rs]+=laz[rt];
        laz[rt]=0;
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
    ios::sync_with_stdio(0);cin.tie(0);
    int n,q;cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    tr.build(1,1,n,a);
    for(int i=1;i<=q;i++){
        int tag,a,b;cin>>tag>>a>>b;
        if(tag==1){
            int x;cin>>x;
            tr.upd(1,1,n,a,b,x);
        }
        else {
            cout<<tr.que(1,1,n,a,b)<<"\n";
        }
    }
}
