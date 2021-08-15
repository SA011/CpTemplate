typedef pair<ll,ll> ii;
void dijkstra(vi &dis,ll ind)
{
    dis[ind]=0;
    priority_queue<ii,vector<ii>,greater<ii>> pq;
    pq.push(ii(0,ind));
    while(!pq.empty())
    {
        ii u=pq.top();
        pq.pop();
        if(dis[u.se]<u.fi)continue;
        for(ii x:adj[u.se])
        {
            if(dis[x.fi]<u.fi+x.se)continue;
            dis[x.fi]=u.fi+x.se;
            pq.push(ii(dis[x.fi],x.fi));
        }
    }
}
