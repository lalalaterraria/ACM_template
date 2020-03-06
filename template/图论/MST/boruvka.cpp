// https://www.luogu.com.cn/problem/P3366
#include<bits/stdc++.h>
using namespace std;
struct nod{
    int u,v,w;
}e[200010];

int pre[5010];
int find(int x){return x==pre[x]?x:pre[x]=find(pre[x]);}

int n,m;
pair<int,int> best[5010];
int vis[200010];
void boruvka(){
    for(int i=1;i<=n;i++)pre[i]=i;

    const int inf = 0x3f3f3f3f;
    int ans=0,cnt=0;
    int flg=1;
    while(flg){
        flg=0;
        for(int i=1;i<=n;i++)best[i]={inf,inf};
        for(int i=1;i<=m;i++){
            int fu=find(e[i].u);
            int fv=find(e[i].v);
            if(fu==fv)continue;
            best[fu]=min(best[fu],make_pair(e[i].w,i));
            best[fv]=min(best[fv],make_pair(e[i].w,i));
        }
        for(int i=1;i<=n;i++){
            int val=best[i].first;
            int ind=best[i].second;
            if(val==inf||vis[ind])continue;
            flg=1;
            cnt++;
            ans+=val;
            vis[ind]=1;
            pre[find(e[ind].u)]=e[ind].v;
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
    boruvka();
}