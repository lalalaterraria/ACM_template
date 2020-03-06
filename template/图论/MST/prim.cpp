// https://www.luogu.com.cn/problem/P3366
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int> > e[5010];

int n,m;
int dis[5010];
int vis[5010];
void prim(){
    const int inf=0x3f3f3f3f;
    for(int i=1;i<=n;i++)dis[i]=inf;

    dis[1]=0;
    int ans=0;
    for(int i=1;i<=n;i++){
        int minn=inf,pos;
        for(int j=1;j<=n;j++){
            if(vis[j])continue;
            if(dis[j]<minn){
                minn=dis[j];
                pos=j;
            }
        }
        //如果是森林
        if(minn==inf){
            cout<<"orz"<<endl;
            return;
        }
        ans+=minn;
        for(auto it:e[pos]){
            int v=it.first;
            int w=it.second;
            if(vis[v])continue;
            dis[v]=min(dis[v],w);
        }
        vis[pos]=1;
    }
    cout<<ans<<endl;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b,w;cin>>a>>b>>w;
        e[a].push_back({b,w});
        e[b].push_back({a,w});
    }
    prim();
}
