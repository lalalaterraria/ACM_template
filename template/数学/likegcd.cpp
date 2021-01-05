// F(a,b,c,n)=∑^n_{i=0}(⌊(a∗i+b)/c⌋)
#define LL long long
LL fd(LL a,LL b,LL c,LL n){
	if(a==0) return((b/c)*(n+1));
	if(a>=c||b>=c) return fd(a%c,b%c,c,n)+(a/c)*n*(n+1)/2+(b/c)*(n+1);
	LL m=(a*n+b)/c;
	LL v=fd(c,c-b-1,a,m-1);
	return n*m-v;
}