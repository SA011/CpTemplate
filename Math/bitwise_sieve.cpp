int bs[(asz+63)/64];
ll prime[asz];
ll prime_ind=0;

bool isprime(ll x)
{
    if(x==2||x==3)return true;
    if(x%2==0||x%3==0)return false;
    return !(bs[x/64] & (1 << ((x >> 1) & 31)));
}
void make_comp(ll x)
{
    bs[x/64] |= (1 << ((x >> 1) & 31));
}
void sieve()
{
    ll k=2;
    prime[prime_ind++]=2;
    prime[prime_ind++]=3;
    for(ll i=5;i<asz;i+=k,k=6-k)
    {
        if(isprime(i)){

            prime[prime_ind++]=i;
            ll r;
                if(i%6==1)r=4;
        else r=2;
            if((long long)i*i<asz)for(ll j=i*i;j<asz;j+=r*i,r=6-r)make_comp(j);
        }
    }
}





//4 sec prime genarator

#define asz 1000000001
#define bbb 15625001
int bs[bbb];
bool isprime(ll x)
{
    return !(bs[x/64] & (1 << ((x >> 1) & 31)));
}
void make_comp(ll x)
{
    bs[x/64] |= (1 << ((x >> 1) & 31));
}
ll skip[210 ];
int prime[60000005];
int cnt=0;
void sieve()
{

    ll incr[]={10,2,4,2,4,6,2,6,4,2,4,6,6,2,6,4,2,6,4,6,8,4,2,4,2,4,8,6,4,6,2,4,6,2,6,6,4,2,4,6,2,6,4,2,4,2,10,2};
    prime[cnt++] = 2;
    prime[cnt++] = 3;
    prime[cnt++] = 5;
    prime[cnt++] = 7;
    ll u=1;
    for(ll i=11;i<asz;i+=incr[u++])
    {
        if(isprime(i)){
        if((long long)i*i<asz)
        {
            ll k=skip[i%210];
            for(ll j=i*i;j<asz;j+=incr[k++]*i)
            {
                make_comp(j);
                if(k==48)k=0;
            }
        }
        prime[cnt++] = i;
        }
        if(u==48)u=0;
    }
}
