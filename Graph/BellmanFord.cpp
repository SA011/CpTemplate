vector<pair<int, int>> adj[N];
vector<int> path;
bool spfa(int s, int n, vector<int> &dis){
    dis.assign(n + 1, INF);
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    vector<bool> taken(n + 1, 0);
    vector<int> cnt(n + 1, 0);
    vector<int> p(n + 1, -1);
    bool negCycle = false;
    taken[s] = 1;
    int last;
    while(!q.empty() && !negCycle){
        int u = q.front();
        q.pop();
        taken[u] = 0;
        for(auto& [x, y] : adj[u]){
            if(dis[u] + y < dis[x]){
                dis[x] = dis[u] + y;
                p[x] = u;
                if(!taken[x]){
                    q.push(x);
                    taken[x] = 1;
                    cnt[x]++;
                    if(cnt[x] > n){
                        last = x;
                        negCycle = true;
                        break;
                    }
                }
            }
        }
    }
    path.clear();
    if(negCycle){
        for(int i = 0; i < n; i++)last = p[last];
        do{
            path.push_back(last);
            last = p[last];
        }while(last != path[0]);
    }
    return negCycle;
}




vector<int> BellmanFord(int s, int n, vector<int> &dis){
    dis.assign(n + 1, INF);
    dis[s] = 0;
    vector<int> p (n, -1);
    int c;
    for (int i = 0; i < n; ++i){
        c = -1;
        for(int j = 0; j < n; j++){
            if(dis[j] == INF)continue;
            for(auto& [x, y] : adj[j]){
                if(dis[x] > dis[j] + y){
                    c = j;
                    p[x] = j;
                    dis[x] = dis[j] + y;
                }
            }
        }
    }

    if (c == -1)return vector<int>(0);
    int x = c;
    for (int i = 0; i < n; ++i)
        x = p[x];
    vector<int> path;
    for (int i = x; ; i = p[i]){
        if (i == x && path.size())
            break;
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    return path;
}
