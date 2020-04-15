#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e7+10;
char str[maxn], s[maxn<<1];
int r[maxn<<1]; // 含#的回文半径，实际为r-1

// str，s均从0开始
// str[i]->s[(i+1)<<1]
void manacher(){
	int l=0;
    s[l++]='$';
    s[l++]='#';
	for(int i=0;str[i];i++)s[l++]=str[i],s[l++]='#';
	int pos=0,maxr=0;
	for (int i=0;s[i];i++){
		r[i]=i<maxr?min(r[2*pos-i],maxr-i):1;
		while(s[i+r[i]]==s[i-r[i]])r[i]++;
		if(i+r[i]>maxr)pos=i,maxr=i+r[i];
	}
}

int main(){
    cin>>str;
    manacher();
    int ans=0;
    for(int i=0;s[i];i++)ans=max(ans,r[i]-1);
    cout<<ans<<endl;
    return 0;
}