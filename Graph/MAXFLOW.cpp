
class edge
{
public:
    ll u,v,flow,cap;
    edge(ll u,ll v,ll cap):u(u),v(v),cap(cap),flow(0){}
};
class dinic
{
public:
    vector<edge> ed;
    vector<vector<ll>> adj;
    vector<ll> lvl,ptr;
    queue<ll> q;
    ll s,t,n,m=0,inf=1e18;
    dinic(ll n,ll s,ll t):s(s),t(t),n(n){
        lvl.resize(n,0);
        ptr.resize(n,0);
        adj.resize(n);
    }
    void add_edge(ll u,ll v,ll cap)
    {
        ed.emplace_back(u,v,cap);
        ed.emplace_back(v,u,0);
        adj[u].push_back(m);
        adj[v].push_back(m+1);
        m+=2;
    }
    bool bfs()
    {
        while(!q.empty())
        {
            ll u=q.front();
            q.pop();
            for(auto x:adj[u])
            {
                ll v=ed[x].v;
                if(lvl[v]==-1&&ed[x].cap-ed[x].flow>0)lvl[v]=lvl[u]+1,q.push(v);
            }
        }
        return lvl[t]!=-1;
    }
    ll dfs(ll u,ll flow)
    {
        if(!flow)return 0;
        if(u==t)return flow;
        for(ll &id=ptr[u];id<adj[u].size();id++)
        {
            ll x=adj[u][id];
            ll v=ed[x].v;
            if(lvl[v]==lvl[u]+1&&ed[x].cap-ed[x].flow>0)
            {
                ll temp=dfs(v,min(flow,ed[x].cap-ed[x].flow));
                if(temp)
                {
                    ed[x].flow+=temp;
                    ed[x^1].flow-=temp;
                    return temp;
                }
            }
        }
        return 0;
    }
    ll maxflow()
    {
        ll mf=0;
        while(1)
        {
            fill(lvl.begin(),lvl.end(),-1);
            lvl[s]=0,q.push(s);
            if(!bfs())break;
            fill(ptr.begin(),ptr.end(),0);
            while(ll f=dfs(s,inf))mf+=f;
        }
        return mf;
    }
};


//push-relabel
//Maxflow_complexity(ev+v^2e^0.5)
const int inf = 1000000000;

int n;
vector<vector<int>> capacity, flow;
vector<int> height, excess;

void push(int u, int v)
{
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
}

void relabel(int u)
{
    int d = inf;
    for (int i = 0; i < n; i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    if (d < inf)
        height[u] = d + 1;
}

vector<int> find_max_height_vertices(int s, int t) {
    vector<int> max_height;
    for (int i = 0; i < n; i++) {
        if (i != s && i != t && excess[i] > 0) {
            if (!max_height.empty() && height[i] > height[max_height[0]])
                max_height.clear();
            if (max_height.empty() || height[i] == height[max_height[0]])
                max_height.push_back(i);
        }
    }
    return max_height;
}

int max_flow(int s, int t)
{
    height.assign(n, 0);
    height[s] = n;
    flow.assign(n, vector<int>(n, 0));
    excess.assign(n, 0);
    excess[s] = inf;
    for (int i = 0; i < n; i++) {
        if (i != s)
            push(s, i);
    }

    vector<int> current;
    while (!(current = find_max_height_vertices(s, t)).empty()) {
        for (int i : current) {
            bool pushed = false;
            for (int j = 0; j < n && excess[i]; j++) {
                if (capacity[i][j] - flow[i][j] > 0 && height[i] == height[j] + 1) {
                    push(i, j);
                    pushed = true;
                }
            }
            if (!pushed) {
                relabel(i);
                break;
            }
        }
    }

    int max_flow = 0;
    for (int i = 0; i < n; i++)
        max_flow += flow[0][i];
    return max_flow;
}




//Edmond-Karp
ll res[asz][asz];
ll par[asz];
ll f,s,t,n;
void augment(ll ind,ll minf)
{
    if(ind==s)f=minf;
    else if(par[ind]!=-1)
    {
        augment(par[ind],min(res[par[ind]][ind],minf));
        res[par[ind]][ind]-=f,res[ind][par[ind]]+=f;
    }
}
ll maxflow()
{
    ll maxf=0;
    while(1)
    {
        f=0;
        vi dis(n,INF);
        dis[s]=0;
        memset(par,-1,sizeof par);
        queue<ll> q;
        q.push(s);
        while(!q.empty())
        {
            ll u=q.front();
            q.pop();
            if(u==t)break;
            for(int i=0;i<n;i++)
            {
                if(res[u][i]>0&&dis[i]==INF)dis[i]=dis[u]+1,par[i]=u,q.push(i);
            }
        }
        augment(t,INF);
        if(f==0)break;
        mf+=f;
    }
    return mf;
}




//MODIFIED
unordered_map<ll,ll> adj[asz];
ll p[asz];
ll f,s,t;
void augment(ll ind,ll minf)
{
    if(ind==s)f=minf;
    else if(p[ind]!=-1)
    {
        augment(p[ind],min(adj[p[ind]][ind],minf));
        adj[p[ind]][ind]-=f,adj[ind][p[ind]]+=f;
        if(!adj[p[ind]][ind])adj[p[ind]].erase(adj[p[ind]].find(ind));
    }
}
ll maxflow()
{
    ll mf=0;
    while(1)
    {
        f=0;
        bitset<asz> vis(0);
        vis[s]=1;
        memset(p,-1,sizeof p);
        queue<ll> q;
        q.push(s);
        while(!q.empty())
        {
            ll u=q.front();
            q.pop();
            if(u==t)break;
            for(auto x:adj[u])
            {
                if(x.se>0&&vis[x.fi]==0)
                {
                    vis[x.fi]=1;
                    p[x.fi]=u;
                    q.push(x.fi);
                }
            }
        }
        augment(t,INF);
        if(f==0)break;
        mf+=f;
    }
    return mf;
}
//To find mincut run dfs/bfs on res graph from s. take every reachable vertex to set s.



//MINMOST MAXFLOW
unordered_map<ll,ii> adj[asz];
ll p[asz];
ll f,s,t;
void augment(ll ind,ll minf)
{
    if(ind==s)f=minf;
    else if(p[ind]!=-1)
    {
        augment(p[ind],min(adj[p[ind]][ind].fi,minf));
        adj[p[ind]][ind].fi-=f,adj[ind][p[ind]].fi+=f;
//        if(!adj[p[ind]][ind].fi)adj[p[ind]].erase(adj[p[ind]].find(ind));
    }
}
ii maxflow()
{
    ll mf=0,mincost=0;
    while(1)
    {
        f=0;
        vi dis(asz,INF);
        dis[s]=0;
        memset(p,-1,sizeof p);
        priority_queue<ii,vector<ii>,greater<ii>> q;
        q.push(ii(0,s));
        while(!q.empty())
        {
            ii u=q.top();
            q.pop();
            if(dis[u.se]<u.fi)continue;
            for(auto x:adj[u.se])
            {
                if(x.se.fi>0&&dis[x.fi]>u.fi+x.se.se)
                {
                    dis[x.fi]=u.fi+x.se.se;
                    p[x.fi]=u.se;
                    q.push(ii(dis[x.fi],x.fi));
                }
            }
        }
        augment(t,INF);
        if(f==0)break;
        mf+=f;
        mincost+=dis[t]*f;
    }
    return ii(mf,mincost);
}
//BETTER

struct mcmf{
    vector<unordered_map<ll,ii>> adj;
    vector<ll> p;
    ll n,f,s,t;
    mcmf(ll _n,ll _s,ll _t):n(_n),s(_s),t(_t){
        adj.resize(n);
    }
    void augment(ll ind,ll minf)
    {
        if(ind==s)f=minf;
        else if(p[ind]!=-1)
        {
            augment(p[ind],min(adj[p[ind]][ind].fi,minf));
            adj[p[ind]][ind].fi-=f,adj[ind][p[ind]].fi+=f;
//        if(!adj[p[ind]][ind].fi)adj[p[ind]].erase(adj[p[ind]].find(ind));
        }
    }
    void addedge(ll u,ll v,ll cap,ll cost)
    {
        adj[u][v]=ii(cap,cost);
        adj[v][u]=ii(0,-cost);
    }
    ii maxflow()
    {
        ll mf=0,mincost=0;
        while(1)
        {
            f=0;
            vi dis(asz,INF);
            dis[s]=0;
            p.assign(n,-1);
            queue<ll> q;
            q.push(s);
            vi d(asz,0);
            while(!q.empty())
            {
                ll u=q.front();
                q.pop();
                d[u]=0;
                for(auto x:adj[u])
                {
                    if(x.se.fi>0&&dis[x.fi]>dis[u]+x.se.se)
                    {
                        dis[x.fi]=dis[u]+x.se.se;
                        p[x.fi]=u;
                        if(d[x.fi]==0)q.push(x.fi);
                        d[x.fi]=1;
                    }
                }
            }
            augment(t,INF);
            if(f==0)break;
            mf+=f;
            mincost+=dis[t]*f;
        }
        return ii(mf,mincost);
    }
};
// Min-cost Max-flow using SPFA ( by Sabit Zahin )
// - 0 Based indexed for directed weighted graphs
// - for undirected graphs, add two directed edges

namespace mcmf{
    const int MAX = 1000010;
    const long long INF = 1LL << 60;

    long long cap[MAX], flow[MAX], cost[MAX], dis[MAX];
    int n, m, s, t, Q[10000010], adj[MAX], link[MAX], last[MAX], from[MAX], visited[MAX];

    void init(int nodes, int source, int sink){
        m = 0, n = nodes, s = source, t = sink;
        for (int i = 0; i <= n; i++) last[i] = -1;
    }

    void addEdge(int u, int v, long long c, long long w){
        adj[m] = v, cap[m] = c, flow[m] = 0, cost[m] = +w, link[m] = last[u], last[u] = m++;
        adj[m] = u, cap[m] = 0, flow[m] = 0, cost[m] = -w, link[m] = last[v], last[v] = m++;
    }

    bool spfa(){
        int i, j, x, f = 0, l = 0;
        for (i = 0; i <= n; i++) visited[i] = 0, dis[i] = INF;

        dis[s] = 0, Q[l++] = s;
        while (f < l){
            i = Q[f++];
            for (j = last[i]; j != -1; j = link[j]){
                if (flow[j] < cap[j]){
                    x = adj[j];
                    if (dis[x] > dis[i] + cost[j]){
                        dis[x] = dis[i] + cost[j], from[x] = j;
                        if (!visited[x]){
                            visited[x] = 1;
                            if (f && rand() & 7) Q[--f] = x;
                            else Q[l++] = x;
                        }
                    }
                }
            }
            visited[i] = 0;
        }
        return (dis[t] != INF);
    }

    pair <long long, long long> maxFlow(){
        int i, j;
        long long mincost = 0, maxflow = 0;

        while (spfa()){
            long long aug = INF;
            for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i]){
                aug = min(aug, cap[j] - flow[j]);
            }
            for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i]){
                flow[j] += aug, flow[j ^ 1] -= aug;
            }
            maxflow += aug, mincost += aug * dis[t];
        }
        return make_pair(maxflow, mincost);
    }
}
