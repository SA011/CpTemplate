/* FIBONACCI
    F(n-1)*F(n+1)-F(n)*F(n)=(-1)^n
    F(n+k)=F(k)F(n+1)+F(k-1)F(n)
    GCD(F(n),F(m))=F(GCD(n,m))
    F(2k)=F(k)(2*F(k+1)-F(k))
    F(2k+1)=F(k+1)^2+F(k)^2
*/
//returns {f(n),(n+1)}
pair<ll,ll> fib(ll a,ll md=0)
{
    if(a==0)return {0,1};
    auto p=fib(a/2,md);
    ll c=(p.first*p.first)+(p.second*p.second);
    ll d=p.first*(2*p.second+md-p.first);
    if(md)c%=md,d%=md;
    if(a&1)
    {
        if(md)return {c,(c+d)%md};
        return {c,c+d};
    }
    return {d,c};
}
ll fibsum(ll n)
{
    if(n<=0)return 0;
    return 2*fibsum(n-1)-fibsum(n-3);
}

ll catalan(ll n)
{
    if(n==0)return 1;
    return (4*n-2)*catalan(n-1)/(n+1);
}


ll count_dig_of_fact_n_base_b(ll n,ll b)
{
    if(n<2)return 1;
    // ans=n*logb(n/e)+logb(2*pi*n)/2
    double x=n*log(n/M_E)/log(b)+log(2*PI*n)/log(b)/2;
    return floor(x)+1;
}

