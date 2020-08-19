#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int mod1=1e9+9;
const int mod2=998244353;
struct Mint{
    int v1,v2;
    Mint(){v1=v2=0;}
    Mint(int x){v1=v2=x;}
    Mint(int a,int b){v1=v2=b;}
    bool operator==(Mint x){return v1==x.v1&&v2==x.v2;}
    Mint operator*(int x){return Mint((ll)v1*x%mod1,(ll)v2*x%mod2);}
    Mint operator+(int x){return Mint((v1+x)%mod1,(v2+x)%mod2);}
    Mint operator-(int x){return Mint((v1+mod1-x)%mod1,(v2+mod2-x)%mod2);}

    Mint operator*(Mint x){return Mint((ll)v1*x.v1%mod1,(ll)v2*x.v2%mod2);}
    Mint operator+(Mint x){return Mint((v1+x.v1)%mod1,(v2+x.v2)%mod2);}
    Mint operator-(Mint x){return Mint((v1+mod1-x.v1)%mod1,(v2+mod2-x.v2)%mod2);}

} h[100010],b[100010];
Mint geth(int x,int y){return h[y]-h[x-1]*b[y-x+1];} 