#include<bits/stdc++.h>
using namespace std;
int a[400010];
inline bool pd(int x,int d){
	return x&(1<<d);
}
int sort(int L,int R,int d){
	int l=L,r=R;
	while(l<r){
		while(l<r&&!pd(a[l],d))l++;
		while(l<r&&pd(a[r],d))r--;
		swap(a[l],a[r]);l++,r--;
	}
	int m=L-1;
	while(m<R&&!pd(a[m+1],d))m++;
	return m;
}