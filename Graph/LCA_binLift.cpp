//Call with (root,root)
ll tin[asz],tout[asz],timer;
ll up[asz][25];
void dfs(ll ind,ll par)
{
    tin[ind]=timer++;
    up[ind][0]=par;
    for(ll i=1;i<25;i++)
        up[ind][i]=up[up[ind][i-1]][i-1];
    for(auto x:adj[ind])
    {
        if(x!=par)dfs(x,ind);
    }
    tout[ind]=timer++;
}
bool isancestor(ll a,ll b)
{
    return tin[a]<=tin[b]&&tout[a]>=tout[b];
}
ll LCA(ll a,ll b)
{
    if(isancestor(a,b))return a;
    if(isancestor(b,a))return b;
    for(int i=24;i>=0;i--)
    {
        if(!isancestor(up[a][i],b))
            a=up[a][i];
    }
    return up[a][0];
}
