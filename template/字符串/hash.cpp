#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define pii pair<int,int>
pii base={131,137};
pii mod={1e9+7,1e9+9};
struct myhash{
    pii has[1000010];
    pii bas[1000010];
    // 注意字符串从1开始存
    void init(char s[],int n){
        has[0]={0,0};bas[0]={1,1};
        for(int i=1;i<=n;i++){
            has[i].st=(1ll*has[i-1].st*base.st+s[i])%mod.st;
            has[i].nd=(1ll*has[i-1].nd*base.nd+s[i])%mod.nd;
            bas[i].st=1ll*bas[i-1].st*base.st%mod.st;
            bas[i].nd=1ll*bas[i-1].nd*base.nd%mod.nd;
        }
    }
    pii shift(pii x,int y){
        return {1ll*x.st*bas[y].st%mod.st,1ll*x.nd*bas[y].nd%mod.nd};
    }
    pii str(int l,int r){
        pii tmp=shift(has[l-1],r-l+1); 
        return {(has[r].st-tmp.st+mod.st)%mod.st,(has[r].nd-tmp.nd+mod.nd)%mod.nd};
    }
} H,H2;