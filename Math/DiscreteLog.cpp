ll discreteLog(ll a, ll base, ll md){
    ll n = ceil(sqrt(md));
    if(a == 1)return 0;
    ll e = 1, f = 0;
    ll x = 1;
    for(ll d = __gcd(base, md); d != 1; d = __gcd(base, md)){
        if(a % d)return __INT64_MAX__;
        a /= d, md /= d;
        e = (e * base / d) % md;
        f++;
        if(a == e)return f;
    }
    for(int i = 0; i < n; i++)x = (x * base) % md;
    ll np = e;
    unordered_map<ll, ll> mp;
    for(int i = 1; i <= n; i++){
        np = (np * x) % md;
        if(mp.find(np) == mp.end())mp[np] = i;
    }
    ll ans = __INT64_MAX__;
    for(int i = 0; i < n; i++){
        if(mp.find(a) != mp.end())ans = min(ans, mp[a] * n - i + f);
        a = (a * base) % md;
    }
    return ans;
}
