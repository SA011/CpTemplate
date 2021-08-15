
//MCBM=MVC, MIS=V-MCBM
//MVC=MIN VERTEX COVER(every edge must incident to one of them)
//MIS=MAX INDEPENDENT SET (No vertex has an edge)
//MCBM=MAX CARDINALITY BIPARTITE MATCHING (number of pair without using a vertex more than once and pair must have an edge)
int vis[asz],mtch[asz];
vi adj[asz];
int augment(int l)
{
    if(vis[l])return 0;
    vis[l]=1;
    for(auto x:adj[l])
    {
        if(mtch[x]==-1||augment(mtch[x]))
        {
            mtch[x]=l;
            return 1;
        }
    }
    return 0;
}
int MCBM(int n)
{
    memset(mtch,-1,sizeof mtch);
    int ans=0;
    for(int i=0;i<n;i++)memset(vis,0,sizeof vis),ans+=augment(i);
    return ans;
}


