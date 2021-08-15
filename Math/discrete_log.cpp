
ll discrete_log(ll base,ll result,ll md)
{
    ll n=ceil(sqrt(md));
    if(result==1)return 0;
    ll e=1,f=0;
    ll x=1;
    for(ll d=__gcd(base,md);d!=1;d=__gcd(base,md))
    {
        if(result%d)return __INT64_MAX__;
        result/=d,md/=d;
        e=(e*base/d)%md;
        f++;
        if(result==e)return f;
    }
    for(ll i=0;i<n;i++)x=(x*base)%md;
    ll np=e;
    unordered_map<ll,ll> mp;
    for(ll i=1;i<=n;i++)
    {
        np=(np*x)%md;
        if(mp.find(np)==mp.end())mp[np]=i;
    }
    ll ans=__INT64_MAX__;
    for(ll i=0;i<n;i++)
    {
        if(mp.find(result)!=mp.end())ans=min(ans,mp[result]*n-i+f);
        result=(result*base)%md;
    }
    return ans;
}
