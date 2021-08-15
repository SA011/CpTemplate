vi adj[2][N];
int vis[N],comp[N],sat[N];
vi ts;
void init(int n){
    for(int i = 0; i < n; i++)
        adj[0][i].clear(), adj[1][i].clear(), vis[i] = 0;
    ts.clear();
}
//a -> b (== !b -> !a) [use 2*a for a and 2*a + 1 for !a]
void add(int a, int b){
    adj[0][a].eb(b);
    adj[0][b ^ 1].eb(a ^ 1);
    adj[1][b].eb(a);
    adj[1][a ^ 1].eb(b ^ 1);
}
void dfs(int ind, int r, int d = -1){
    vis[ind] = 1;
    if(r) comp[ind] = d;
    for(auto x:adj[r][ind])
        if(vis[x] == 0) dfs(x,r,d);
    if(!r) ts.push_back(ind);
}
bool solve2sat(int n){
    for(int i = 0; i < n; i++)if(vis[i] == 0) dfs(i, 0);
    for(int i = 0; i < n; i++)vis[i] = 0;
    int com = 0;
    while(!ts.empty()){
        if(vis[ts.back()] == 0)
            dfs(ts.back(), 1, com++);
        ts.pop_back();
    }
    
    for(int i = 0; i < n; i += 2){
        if(comp[i] == comp[i|1])return false;
        sat[i >> 1] = comp[i] > comp[i|1];
    }
    return true;
}
