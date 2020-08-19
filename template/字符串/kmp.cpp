//KMP
//博文:https://blog.csdn.net/dyx404514/article/details/41314009
//题目:https://www.luogu.org/problemnew/show/P3375

#include<cmath>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
#define mst(a,b) memset(a,b,sizeof a)
#define fo(i,a,b) for(int i=a;i<=b;i++)

int f[1000005];
char a[1000005];
char b[1000005];
int m, n;

//默认字符串从0开始,f[i]初始化为0
void kmp()
{
	//初始化,不需要初始化全部
	f[0] = 0;
	//求前缀数组,这里本质是DP
	for (int i = 1; i < m; i++)
	{
		//j是当前需要匹配的下标
		int j = f[i-1];
		//b[j] != b[i]说明子序列对称但是最后一位对不住,往f[j]里再找子序列,直到确定对称位置j+1,或者无对称
		while (j && b[i] != b[j]) j = f[j-1];
		//最后又多匹配了一位,子序列长度加一即可
		f[i] = b[i] == b[j] ? j+1 : 0;
	}

	//主体
	int j = 0;
	fo(i,0,n-1)
	{
		while (j && a[i] != b[j])j = f[j - 1];
		if (a[i]==b[j]) j++;
		if (j == m)
		{
			printf("%d\n", i - m + 2);
			j = f[j - 1];
		}
	}
}

int main()
{
	cin >> a >> b;
	while (a[n++]); n--;
	while (b[m++]); m--;
	kmp();

	fo(i, 0, m - 2) printf("%d ", f[i]); printf("%d\n", f[m-1]);
}