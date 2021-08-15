



// DOUBLE HASHING FOR MORE ACCURACY

ii compute_hash(string &s,ll p1,ll md1,ll p2,md2)
{
    ll pr1=1;
    ll pr2=1;
    ii ans={0,0};
    for(char c:s)
    {
        ans.first=(ans.first+pr1*(c-'a'+1))%md1;
        ans.second=(ans.second+pr2*(c-'a'+1))%md2;
        pr2=(pr2*p2)%md2;
        pr1=(pr1*p1)%md1;
    }
    return ans;
}
ii hashed[asz],pn[asz];

void full_hash(string &s,ll p1,ll md1,ll p2,ll md2)
{
    hashed[0]={0,0};
    pn[0]={1,1};
    for(ll i=0;i<s.size();i++)
    {
        hashed[i+1]=make_pair((hashed[i].first+(pn[i].first)*(s[i]-'a'+1))%md1,(hashed[i].second+(pn[i].second)*(s[i]-'a'+1))%md2);
        pn[i+1]=make_pair(((pn[i].first)*p1)%md1,((pn[i].second)*p2)%md2);
    }
}
ii hashed_compute(ll a,ll b,ll n,ll md1,ll md2)
{

    return make_pair(((hashed[b].first-hashed[a].first+md1)*(pn[n-a-1].first))%md1,((hashed[b].second-hashed[a].second+md2)*(pn[n-a-1].second))%md2);
}
bool comp_hash_elem(ll a,ll b,ll a1,ll b1,ll n,ll md1,ll md2)
{
    if((b-a)!=(b1-a1))return 0;
    ii x=hashed_compute(a,b,n,md1,md2);
    ii y=hashed_compute(a1,b1,n,md1,md2);
    return x==y;
}
ii pninv[asz];
void preprocess(ll p1, ll md1,ll p2,ll md2)
{
    pninv[0]={1,1};
    pninv[1]=make_pair(fastpow(p1,md1-2,md1),fastpow(p2,md2-2,md2));
    for(ll i=2;i<asz;i++)
        pninv[i]=make_pair(((pninv[1].first)*(pninv[i-1].first))%md1,((pninv[1].second)*(pninv[i-1].second))%md2);
}

ii hashed_value(ll a, ll b,ll md1,ll md2)
{
    return make_pair(((((hashed[a+1].first)-(hashed[b].first)+md1)%md1)*(pninv[b].first))%md1,((((hashed[a+1].second)-(hashed[b].second)+md2)%md2)*(pninv[b].second))%md2);
}


