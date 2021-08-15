
vi adj[asz],adj2[asz],scc[asz];
ll vis[asz],num[asz],low[asz],timer,cc,cc_ind[asz];
vi ts;
void tarjan(ll ind)
{
    num[ind]=low[ind]=++timer;
    ts.push_back(ind);
    vis[ind]=1;
    for(auto x:adj[ind])
    {
        if(num[x]==-1)tarjan(x);
        if(vis[x])
            low[ind]=min(low[ind],low[x]);
    }
    if(low[ind]==num[ind])
    {
        ll x;
        do
        {
            x=ts.back();
            ts.pop_back(),vis[x]=0;
            scc[cc].push_back(x);
            cc_ind[x]=cc;
            if(x==ind)break;
        }while(x!=ind);
        cc++;
    }
}
void create_scc(ll n)
{
    memset(vis,0,sizeof vis);
    memset(num,-1,sizeof num);
    for(int i=0;i<n;i++)scc[i].clear(),adj2[i].clear();
    timer=0;
    cc=0;
    for(int i=0;i<n;i++)
    {
        if(num[i]==-1)
        {
            tarjan(i);
            ts.clear();
        }
    }
    for(int i=0;i<cc;i++)
    {
        for(auto x:scc[i])
        {
            for(auto y:adj[x])
            {
                if(cc_ind[y]!=i)adj2[i].push_back(cc_ind[y]);
            }
        }
    }
}
