int phi(int n){
    int ret=n,lim=n;
    for(int i=2; i*i<=lim; i++)
        if(n%i==0){
            ret=ret/i*(i-1);
            while(n%i==0) n/=i;
        }
    if(n>1) ret=ret/n*(n-1);
    return ret;
}