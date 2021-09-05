vector<int> adj[N];
int num[N], low[N];
int timer;
int art[N];
vector<pair<int, int>> bridge;
//set all num to -1
//count root children to make sure its articulation vertex
void dfs(int ind, int par = -1){
    num[ind] = low[ind] = timer++;
    int child = 0;
    for(auto &x:adj[ind]){
        if(x == par)continue;
        if(num[x] != -1) low[ind] = min(low[ind], num[x]);
        else{
            child++;
            dfs(x, ind);
            if(low[x] > num[ind]){
                cout << "BRIDGE: " << ind << " -> " << x << endl;
                bridge.emplace_back(ind, x);
            }
            if(par != -1 && !art[ind] && low[x] >= num[ind]){
                art[ind] = 1;
                cout << "NODE: " << ind << endl;
            }
            low[ind] = min(low[ind], low[x]);
        }
    }
    if(par == -1 && child > 1){
        art[ind] = 1;
        cout << "NODE: " << ind << endl;
    }
}
