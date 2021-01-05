#include<algorithm>
using namespace std;
#define maxn 100000
int a[maxn],b[maxn];
int LIS(int a[], int n){
	int len = 1; b[0] = a[0];
	for(int i=1;i<=n-1;i++) b[a[i] > b[len - 1] ? len++ : lower_bound(b, b + len, a[i]) - b] = a[i];
	return len;
}