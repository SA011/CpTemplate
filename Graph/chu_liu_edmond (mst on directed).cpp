const int N = 61,M = 10005;
iii edge[M];
int par[N],id[N],val[N],comp[N];
ll chu_liu_edmond(int n,int m,int root){
    ll ans = 0;
    while(true){
        for(int i=0;i<n;i++)par[i] = -1, val[i] = INF, id[i] = -1, comp[i] = -1;
        val[root] = 0;
        for(int i=0;i<m;i++){
            int u = edge[i].fi.fi,v = edge[i].fi.se;
            if(edge[i].se<val[v])
                val[v] = edge[i].se, par[v] = u;
        }
        for(int i=0;i<n;i++)
            if(val[i] == INF)return INF;
        int n_id = 0;
        for(int i=0;i<n;i++){
            if(i == root)continue;
            ans += val[i];
            int p = i;
            while(comp[p] == -1){
                comp[p] = i;
                p = par[p];
            }
            if(comp[p] == i){
                for(int k = par[p]; k!=p ;k = par[k])
                    id[k] = n_id;
                id[p] = n_id++;
            }
        }
        if(n_id == 0)break;
        for(int i=0;i<n;i++)if(id[i] == -1)id[i] = n_id++;
        int n_m = 0;
        for(int i=0;i<m;i++){
            int u = edge[i].fi.fi,v = edge[i].fi.se;
            if(id[u] != id[v])
                edge[n_m++] = iii({id[u],id[v]},edge[i].se - val[v]);
        }
        m = n_m, n = n_id, root = id[root];
    }
    return ans;
}
