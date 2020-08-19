#include<bits/stdc++.h>
using namespace std;
template<class T>
struct fs{
    T first,second;
    // y>0
    fs regular(T x, T y){
        if(x==0) return {0,1};
        int flg=1;
        if(x<0) flg=-1,x=-x;
        T gcd=__gcd(x,y);
        return {flg*x/gcd,y/gcd};
    }

    fs operator+(fs b){
        fs a={first,second};
        T x=a.first*b.second+a.second*b.first;
        T y=a.second*b.second;
        return regular(x,y);
    }

    fs operator-(fs b){
        fs a={first,second};
        T x=a.first*b.second-a.second*b.first;
        T y=a.second*b.second;
        return regular(x,y);
    }

    fs operator*(fs b){
        fs a={first,second};
        T x=a.first*b.first;
        T y=a.second*b.second;
        return regular(x,y);
    }

    fs operator/(fs b){
        fs a={first,second};
        T x=a.first*b.second;
        T y=a.second*b.first;
        return regular(x,y);
    }

    fs C(int n,int m){
        T x=1,y=1;
        for(int i=n-m+1;i<=n;i++)x*=i;
        for(int i=1;i<=m;i++)y*=i;
        T gcd=__gcd(x,y);
        return {x/gcd,y/gcd};
    }
};