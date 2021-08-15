

ll fastpow(ll val,ll pwr,ll md=0)
{
    if(pwr==0)return 1;
    if(md){
    if(pwr%2)return (val*fastpow((val*val)%md,pwr/2,md))%md;
    return fastpow((val*val)%md,pwr/2,md);
    }
    else
    {
        if(pwr%2)return val*fastpow(val*val,pwr/2);
        return fastpow(val*val,pwr/2);
    }
}

ll bigmod(ll a,ll p, ll m)
{
    ll res=1,x=a;
    while(p)
    {
        if(p&1)res=(res*x)%m;
        x=(x*x)%m;
        p>>=1;
    }
    return res;
}
