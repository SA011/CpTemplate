ll heavy[asz],head[asz],dis[asz],pos[asz],parent[asz];
vector<ll> adj[asz];
ll cur_pos=0;
ll dfs(ll ind,ll d=0)
{
    dis[ind]=d;
    ll sz=1,mx=0;
    for(ll x:adj[ind])
    {
        if(x!=parent[ind])
        {
            parent[x]=ind;
            ll y=dfs(x,d+1);
            sz+=y;
            if(y>mx)mx=y,heavy[ind]=x;
        }
    }
    return sz;
}


void decompose(ll ind,ll hd=0)
{
    head[ind]=hd,pos[ind]=cur_pos++;
    if(heavy[ind]!=-1)decompose(heavy[ind],hd);
    for(ll x:adj[ind])
    {
        if(x!=parent[ind]&&x!=heavy[ind])decompose(x,x);
    }
}

ll query_heavylight(ll a,ll b)
{
    ll ans=0;
    for(;head[a]!=head[b];b=parent[head[b]])
    {
        if(dis[head[a]]>dis[head[b]])swap(a,b);
        ll a=query(pos[head[b]],pos[b]);
        ans=func(ans,a);
    }
    if(dis[a]>dis[b])swap(a,b);
    ll a=query(pos[a],pos[b]);
    return ans=func(ans,a);
}
