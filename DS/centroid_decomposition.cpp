
vector<int> adj[asz],cen_tree[asz];
bool cent_mark[asz];
int sub[asz];
void dfs(int ind,int &n,int par=-1)
{
    n++;
    sub[ind]=1;
    for(auto x:adj[ind])
    {
        if(x!=par&&!cent_mark[x])
            dfs(x,n,ind),sub[ind]+=sub[x];
    }
}
int get_centroid(int ind,int n,int par=-1)
{
    bool cen=true;
    int heavy=-1;
    for(auto x:adj[ind])
    {
        if(x!=par&&!cent_mark[x])
        {
            if(sub[x]>n/2)cen=false;
            if(heavy==-1||sub[heavy]<sub[x])heavy=x;
        }
    }
    if(cen&&n-sub[ind]<=n/2)return ind;
    return get_centroid(heavy,n,ind);
}
int decompose(int ind)
{
    int n=0;
    dfs(ind,n);
    int cn=get_centroid(ind,n);
    cent_mark[cn]=1;
    for(auto x:adj[cn])
    {
        if(!cent_mark[x])
        {
            int y=decompose(x);
            cen_tree[cn].push_back(y);
            cen_tree[y].push_back(cn);
        }
    }
    return cn;
}