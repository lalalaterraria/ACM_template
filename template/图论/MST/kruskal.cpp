// https://www.luogu.com.cn/problem/P3366
#include<bits/stdc++.h>
using namespace std;
struct nod{
    int u,v,w;
    bool operator<(const nod x) const {
        return w<x.w;
    }
}e[200010];
int n,m;
int pre[5010];
int find(int x){return pre[x]==x?x:pre[x]=find(pre[x]);}
void kruskal(){
    sort(e+1,e+m+1);
    for(int i=1;i<=n;i++)pre[i]=i;
    
    int ans=0;
    int cnt=0;
    for(int i=1;i<=m;i++){
        int fu=find(e[i].u);
        int fv=find(e[i].v);
        if(fu!=fv){
            ans+=e[i].w;
            pre[fv]=fu;
            cnt++;
        }
    }

    if(cnt == n-1) cout<<ans<<endl;
    else cout<<"orz"<<endl; //如果是森林
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w;
    }
    kruskal();
}