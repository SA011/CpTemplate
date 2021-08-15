//2D bit

#define lastone(n) ((n)&(-(n)))
ll bit[asz][asz];
void update(ii ind,ll val)
{
    for(++ind.fi,++ind.se;ind.fi<asz;ind.fi+=lastone(ind.fi))
    {
        for(ll x=ind.se;x<asz;x+=lastone(x))
            bit[ind.fi][x]+=val;
    }
}
ll query(ii a)
{
    ll s=0;
    for(++a.fi,++a.se;a.fi>0;a.fi-=lastone(a.fi))
    {
        for(ll x=a.se;x>0;x-=lastone(x))
            s+=bit[a.fi][x];
    }
    return s;
}
ll query(ii a,ii b)
{
    return query(b)-query(ii(b.fi,a.se-1))-query(ii(a.fi-1,b.se))+query(ii(a.fi-1,a.se-1));
}
