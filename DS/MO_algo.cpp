
ll qry[asz];
ll ans[asz];
ll ck[asz];
vector<iii> vs;
const int blk=548;
bool cmp(iii a,iii b)
{
    if(a.fi.fi/blk==b.fi.fi/blk)return a.fi.se<b.fi.se;
    return a.fi.fi/blk<b.fi.fi/blk;
}
void MO()
{
    sort(vs.begin(),vs.end(),cmp);
    ll st=vs[0].fi.fi,en=vs[0].fi.fi;
    ck[qry[st]]=1;
    ll a=1;
    for(auto x:vs)
    {
        ii y=x.fi;
        while(st>y.fi)
        {
            --st;
            if(ck[qry[st]]==0)a++;
            ck[qry[st]]++;
        }
        while(st<y.fi)
        {
            if(ck[qry[st]]==1)a--;
            ck[qry[st]]--;
            st++;
        }
        while(en>y.se)
        {
            if(ck[qry[en]]==1)a--;
            ck[qry[en]]--;
            en--;
        }
        while(en<y.se)
        {
            ++en;
            if(ck[qry[en]]==0)a++;
            ck[qry[en]]++;
        }
        ans[x.se]=max(ans[x.se],a);
    }
}
