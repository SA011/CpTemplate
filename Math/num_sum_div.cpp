

// This is naive and good
ll num_div(ll n)
{
    ll ans=1;
    for(int i=0;i<prime_ind&&prime[i]*prime[i]<=n;i++)
    {
        ll d=1;
        while(n%prime[i]==0)n/=prime[i],d++;
        ans*=d;
    }
    if(n!=1)ans*=2;
    return ans-1;
}

//number of divisor for a single number. has some problem careful
ll num_div(ll n)
{
    ll ans=1;
    for(ll i=0;i<prime_ind&&prime[i]*prime[i]*prime[i]<=n;i++)
    {
        ll a=0;
        while(n%prime[i]==0)n/=prime[i],a++;
        ans*=(a+1);
    }
    if(is_prime(n))ans*=2;
    else
    {
        ll x=sqrt(n);
        if(x*x==n&&is_prime(x))ans*=3;
        else ans*=4;
    }
    return ans;
}

// sum of divisor for a single number

ll sum_div(ll n)
{
    ll ans=1;
    ll x=n;
    for(ll i=0;i<prime_ind&&prime[i]*prime[i]<=n;i++)
    {
        ll a=1;
        ll nw=1;
        while(n%prime[i]==0)n/=prime[i],a*=prime[i],nw+=a;
        ans*=nw;
    }
    if(n!=1)ans*=(n+1);
    ans-=x;
    return ans;
}
