#include<iostream>
using namespace std;
#define ls rt<<1
#define rs rt<<1|1
#define mid (l+r)/2
int t[100010<<2],laz[100010<<2];
void php(int rt){t[rt]=max(t[ls],t[rs]);}
void phd(int rt){
    t[ls]+=laz[rt];
    laz[ls]+=laz[rt];

    t[rs]+=laz[rt];
    laz[rs]+=laz[rt];

    laz[rt]=0;
}
void upd(int rt,int l,int r,int x,int y,int z){
    if(x<=l&&r<=y){
        t[rt]+=z;
        laz[rt]+=z;
        return;
    }
    phd(rt);
    if(x<=mid)upd(ls,l,mid,x,y,z);
    if(y>mid)upd(rs,mid+1,r,x,y,z);
    php(rt);
}
int que(int rt,int l,int r,int x,int y){
    if(x<=l&&r<=y){
        return t[rt];
    }
    phd(rt);
    int ret=-1<<30;
    if(x<=mid)ret=max(ret,que(ls,l,mid,x,y));
    if(y>mid)ret=max(ret,que(rs,mid+1,r,x,y));
    return ret;
}
int a[100010];
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
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    int q;cin>>q;
    for(int i=1;i<=q;i++){
        int tag,a,b;cin>>tag>>a>>b;
        if(tag==1){
            int tmp;cin>>tmp;
            upd(1,1,n,a,b,tmp);
        }
        else{
            cout<<que(1,1,n,a,b)<<"\n";
        }
    }
}
