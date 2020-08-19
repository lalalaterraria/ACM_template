#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1e9+7;
struct mat{
    int n;ll a[105][105];
    mat operator*(mat x){
        mat ret={n};
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                for(int k=1;k<=n;k++){
                    ret.a[i][j]=(ret.a[i][j]+a[i][k]*x.a[k][j])%mod;
                }
            }
        }
        return ret;
    }
    void print(){
        cout<<endl;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

// 注意下标从1开始
mat matpow(mat a,ll b){
    mat ret={a.n};
    for(int i=1;i<=ret.n;i++)ret.a[i][i]=1;
    while(b){
        if(b&1)ret=ret*a;
        a=a*a;b>>=1;
    }
    return ret;
}