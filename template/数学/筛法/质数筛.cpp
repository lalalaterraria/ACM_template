const int maxn=500010;
int P[maxn],cnt;bool vis[maxn];
void init(){
	for(int i=2;i<maxn;i++){
		if(!vis[i])P[cnt++]=i;
		for(int j=0;j<cnt&&i*P[j]<maxn;j++){
			vis[i*P[j]]=1;
			if(i%P[j]==0) break;
		}
	}
}