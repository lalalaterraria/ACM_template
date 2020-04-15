#include<iostream>
#include<vector>
using namespace std;

struct nod{
    int u,v,back,ans,nxt;
}e[100010];
int head[100010],cnt;
void add(int u,int v){
    e[++cnt]={u,v,0,0,head[u]};
    head[u]=cnt;
}

int vis[100010],tag[100010];
void dfs1(int u,int fa){
    vis[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int &v=e[i].v;
        if(v==fa||e[i].back)continue;
        if(vis[v])e[i].back=e[i^1].back=1,tag[u]+=1,tag[v]-=1;
        else dfs1(v,u);   
    }
}
void dfs2(int u,int fa){
     for(int i=head[u];i;i=e[i].nxt){
        int &v=e[i].v;
        if(v==fa)continue;
        if(!e[i].back){
            dfs2(v,u);
            if(tag[v])e[i].ans=1;
            tag[u]+=tag[v];
        }
    }
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t;cin>>t;
    while(t--){
        int n,m;cin>>n>>m;cnt=1;
        for(int i=1;i<=n;i++)head[i]=1;
        for(int i=1;i<=m;i++){
            int a,b;cin>>a>>b;
            add(a,b);add(b,a);
        }
        dfs1(1,0);dfs2(1,0);
        int ans=0;
        for(int i=1;i<=cnt;i++){
            if(e[i].ans)ans++;
        }
        cout<<ans<<endl;
        for(int i=1;i<=cnt;i++){
            if(e[i].ans)cout<<i<<" ";
        }
        cout<<endl;
    }
}