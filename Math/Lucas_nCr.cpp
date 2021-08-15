
ll f[asz],invf[asz];
void pre(ll md){
    f[0]=1;
    invf[1]=invf[0]=1;
    for(int i=2;i<md;i++)invf[i]=(md-(md/i)*invf[md%i]%md)%md;
    for(int i=1;i<md;i++)f[i]=f[i-1]*i%md,invf[i]=invf[i-1]*invf[i]%md;
}
ll nCr(int n,int r,int md){
    if(n<r)return 0;
    return f[n]*invf[n-r]%md*invf[r]%md;
}
ll nCr_lucas(int n,int r,int md){
    if(n<r)return 0;
    ll ans=1;
    while(n!=0){
        ans=ans*nCr(n%md,r%md,md)%md;
        n/=md;
        r/=md;
    }
    return ans;
}
