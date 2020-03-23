const int maxn=500010;
int P[maxn],mu[maxn],cnt;
bool vis[maxn];
void init(){
	mu[1]=1;
	for(int i=2;i<maxn;i++){
		if(!vis[i])P[cnt++]=i,mu[i]=-1;
		for(int j=0;j<cnt&&i*P[j]<maxn;j++){
			vis[i*P[j]]=1;
			if(i%P[j]==0) break;
			else mu[i*P[j]]=-mu[i];
		}
	}
	// for(int i=1;i<=20;i++)cout<<i<<" "<<vis[i]<<" "<<mu[i]<<endl;
}