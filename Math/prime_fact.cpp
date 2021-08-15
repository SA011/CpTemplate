
// prime factors for a number. Stores in array v and returns the length of v
pair<ll,ll> v[asz];
ll prime_factors(ll n)
{
    ll ind=0;
    for(ll i=0;i<prime_ind&&prime[i]*prime[i]<=n;i++)
    {
        ll a=0;
        while(n%prime[i]==0)n/=prime[i],a++;
        if(a)v[ind]=make_pair(prime[i],a),ind++;
    }
    if(n!=1)v[ind]=make_pair(n,1),ind++;
    return ind;
}
