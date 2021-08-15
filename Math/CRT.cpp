
ll extended_euclid(ll a,ll b,ll &x,ll &y)
{
    if(a==0)
    {
        x=0,y=1;
        return b;
    }
    ll x1,y1;
    ll ans=extended_euclid(b%a,a,x1,y1);
    x=y1-(b/a)*x1;
    y=x1;
    return ans;
}
ll mult(ll a, ll b, ll md) {
    ll result = 0;
    while (b) {
        if (b & 1)
            result = (result + a) % md;
        a = (a + a) % md;
        b >>= 1;
    }
    return result;
}

ii CRT(vector<ii> &v){
    int n=v.size();
    ii imp={-1,-1};
    if(n==0)return imp;
    ii cur=v[0];
    for(int i=1;i<n;i++){
        ll g=__gcd(cur.second,v[i].second);
        if(cur.first%g!=v[i].first%g)return imp;
        ll a,b;
        extended_euclid(cur.second/g,v[i].second/g,a,b);
        ll l=cur.second/g*v[i].second;
        a%=l,b%=l;
        if(a<0)a+=l;
        if(b<0)b+=l;
        ll u=(mult(mult(cur.second/g,v[i].first,l),a,l)+mult(mult(cur.first,v[i].second/g,l),b,l))%l;
        cur={u,l};
    }
    return cur;
}
