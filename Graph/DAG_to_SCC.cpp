int indeg[N],vis[N];
vi adj[N];
int try_matching(int ind){
    if(vis[ind])return -1;
    vis[ind] = 1;
    if(adj[ind].empty())return ind;
    for(auto x:adj[ind]){
        int u = try_matching(x);
        if(u != -1)return u;
    }
    return -1;
}
vii dag_to_scc(int n){
    
    for(int i=0;i<n;i++){
        for(auto x:adj[i])indeg[x]++;
    }
    vii matched;
    vi usource,usink;
    for(int i=0;i<n;i++){
        if(indeg[i] == 0){
            int u = try_matching(i);
            if(u != -1)matched.emplace_back(i,u);
            else usource.push_back(i);
        }
    }
    for(int i=0;i<n;i++){
        if(adj[i].empty() && vis[i] == 0)usink.push_back(i);
    }
    vii edge;
    
    if(matched.empty() || n <= 1)return edge;
    for(int i=0;i+1<matched.size();i++){
        edge.emplace_back(matched[i].se,matched[i+1].fi);
    }
    edge.emplace_back(matched.back().se,matched[0].fi);
    
    while(!usource.empty() && !usink.empty()){
        edge.emplace_back(usink.back(),usource.back());
        usink.pop_back();
        usource.pop_back();
    }
    
    while(!usource.empty())edge.emplace_back(matched[0].se,usource.back()),usource.pop_back();
    while(!usink.empty())edge.emplace_back(usink.back(),matched[0].fi),usink.pop_back();
    return edge;
}
