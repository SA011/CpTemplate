//Call with root,root
ll tin[asz],tout[asz],timer;
ll up[asz][25],wg[asz][25];
void dfs(ll ind,ll par,ll weight=0)
{
    tin[ind]=timer++;
    up[ind][0]=par;
    wg[ind][0]=weight;
    for(ll i=1;i<25;i++)
        up[ind][i]=up[up[ind][i-1]][i-1];
    for(ll i=1;i<25;i++)
        wg[ind][i]=max(wg[up[ind][i-1]][i-1],wg[ind][i-1]);
    for(ii x:adj[ind])
    {
        if(x.fi!=par)dfs(x.fi,ind,x.se);
    }
    tout[ind]=timer++;
}
bool isancestor(ll a,ll b)
{
    return tin[a]<=tin[b]&&tout[a]>=tout[b];
}
ll LCA(ll a,ll b)
{
    ll ans=0;
    if(isancestor(a,b))
    {
        for(int i=24;i>=0;i--)
        {
            if(!isancestor(up[b][i],a))
                ans=max(ans,wg[b][i]),b=up[b][i];
        }
        ans=max(ans,wg[b][0]);
        return ans;
    }
    if(isancestor(b,a))
    {
        for(int i=24;i>=0;i--)
        {
            if(!isancestor(up[a][i],b))
                ans=max(ans,wg[a][i]),a=up[a][i];
        }
        ans=max(ans,wg[a][0]);
        return ans;
    }
    for(int i=24;i>=0;i--)
    {
        if(!isancestor(up[a][i],b))
            ans=max(ans,wg[a][i]),a=up[a][i];
    }
    ans=max(ans,wg[a][0]);
    a=up[a][0];
    for(int i=24;i>=0;i--)
    {
        if(!isancestor(up[b][i],a))
            ans=max(ans,wg[b][i]),b=up[b][i];
    }
    ans=max(ans,wg[b][0]);
    return ans;
}
