ll bigmod(ll a, ll p, ll m){
    ll res = 1, x = a;
    while(p){
        if(p & 1) res = (res * x) % m;
        x = (x * x) % m;
        p >>= 1;
    }
    return res;
}
