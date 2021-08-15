
// number of co-prime of n less than n
ll phi(ll n)
{
    ll ans=n;
    for(ll i=2;i*i<=n;i++)
    {
        if(n%i==0)ans-=ans/i;
        while(n%i==0)n/=i;
    }
    return ans;
}
ll eulerphi(ll n)
{
     ll ans=n;
      for(ll i=0;i<prime_ind&&prime[i]*prime[i]<=n;i++)
    {
        if(n%prime[i]==0)ans-=ans/prime[i];
        while(n%prime[i]==0)n/=prime[i];
    }
    if(n!=1)ans-=ans/n;
    return ans;
}

//generating all phi(1..n)
ll phl[asz];

void phi_all()
{
    for(ll i=2;i<asz;i++)phl[i]=i;
    phl[0]=0;
    phl[1]=1;
    for(ll i=2;i<asz;i++)
    {
        if(phl[i]==i)
        {
            //got a prime
            phl[i]=i-1;
            for(ll j=2;j*i<asz;j++)
                phl[i*j]=(phl[i*j]/i)*(i-1);
        }
    }
}
