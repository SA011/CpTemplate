
//string hashing

ll compute_hash(string &s,ll p,ll md)
{
    ll pr=1;
    ll ans=0;
    for(char c:s)
    {
        ans=(ans+pr*(c-'a'+1))%md;
        pr=(pr*p)%md;
    }
    return ans;
}
ll hashed[asz],pn[asz];

void full_hash(string &s,ll p,ll md)
{
    hashed[0]=0;
    pn[0]=1;
    for(ll i=0;i<s.size();i++)
    {
        hashed[i+1]=(hashed[i]+pn[i]*(s[i]-'a'+1))%md;
        pn[i+1]=(pn[i]*p)%md;
    }
}
ll hashed_compute(ll a,ll b,ll n,ll md)
{

    return ((hashed[b]-hashed[a]+md)*pn[n-a-1])%md;
}
bool comp_hash_elem(ll a,ll b,ll a1,ll b1,ll n,ll md)
{
    if((b-a)!=(b1-a1))return 0;
    ll x=hashed_compute(a,b,n,md);
    ll y=hashed_compute(a1,b1,n,md);
    return x==y;
}
ll pninv[asz];
void preprocess(ll p, ll md)
{
    pninv[0]=1;
    pninv[1]=fastpow(p,md-2,md);
    for(ll i=2;i<asz;i++)
        pninv[i]=(pninv[1]*pninv[i-1])%md;
}

ll hashed_value(ll a, ll b,ll md)
{
    return (((hashed[a+1]-hashed[b]+md)%md)*pninv[b])%md;
}
