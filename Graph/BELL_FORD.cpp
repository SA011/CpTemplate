vector<pair<int,int>> adj[200005];
bool spfa(int s,int n,vector<int> &dis)
{
    dis.assign(n+1,1000000000);
    dis[s]=0;
    queue<int> q;
    q.push(s);
    vector<bool> taken(n+1,0);
    vector<int> cnt(n+1,0);
    taken[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        taken[u]=0;
        for(auto x:adj[u])
        {
            if(dis[u]+x.second<dis[x.first])
            {
                dis[x.first]=dis[u]+x.second;
                if(!taken[x.first])
                {
                    q.push(x.first);
                    taken[x.first]=1;
                    cnt[x.first]++;
                    if(cnt[x.first]>n)
                        return true;
                }
            }
        }
    }
    return false;
}



//To retrieve the neg cycle
vector<int> bellman(int s,int n,vector<int> &dis)
{
    dis.assign(n,INF);
    dis[s] = 0;
    vector<int> p (n ,- 1);
    int c;
    for (int i=0; i<n; ++i)
    {
        c = -1;
        for(int j=0;j<n;j++){
            if(dis[j]==INF)continue;
            for(auto x:adj[j]){
                if(dis[x.fi]>dis[j]+x.se){
                    c=j;
                    p[x.fi]=j;
                    dis[x.fi]=dis[j]+x.se;
                }
            }
        }
    }

    if (c == -1)return vector<int>(0);
    int x = c;
    for (int i=0; i<n; ++i)
        x = p[x];
    vector<int> path;
    for (int i=x; ; i=p[i])
    {
        if (i == x && path.size())
            break;
        path.push_back (i);
    }
    reverse (path.begin(), path.end());
    return path;
}
