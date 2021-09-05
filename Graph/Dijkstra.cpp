void dijkstra(vector<ll> &dis, int s){
    dis[s] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.push(pair<ll, ll>(0, s));
    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();
        if(dis[u] < d)continue;
        for(auto& [x, y] : adj[u]){
            if(dis[x] < d + y)continue;
            dis[x] = d + y;
            pq.push(pair<ll, ll>(dis[x], x));
        }
    }
}
