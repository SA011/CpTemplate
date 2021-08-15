
//Strongly Connected component
set<ll> adj[2][asz],adj2[asz],scc[asz]; //adj[0] -> original graph//adj[1] -> reversed original graph//adj2 -> compressed graph (DAG)//scc -> nodes in a component
ll num[asz];
ll com,n;
vector<ll> ts;
void dfs(ll ind,vector<bool> &vis,bool topo)
{
    vis[ind]=true;
    for(auto x:adj[!topo][ind])
        if(!vis[x])
            dfs(x,vis,topo);
    if(topo)ts.push_back(ind);
    else scc[com].insert(ind),num[ind]=com;
}
void strong()
{
    vector<bool> vis(n+1,false);
    for(int i=1;i<=n;i++)
        if(!vis[i])
            dfs(i,vis,true);
    vis.assign(n+1,false);
    for(int i=0;i<n;i++)
    {
        ll ind=ts[n-i-1];
        if(!vis[ind])
            dfs(ind,vis,false),com++;
    }
    for(int i=0;i<com;i++)
    {
        for(auto x:scc[i])
        {
            for(auto y:adj[0][x])
            {
                if(num[y]!=i)adj2[i].insert(num[y]);
            }
        }
    }
}
