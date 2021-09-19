class Unionfind{
public:
    vector<int> p, rnk;
    int n;
    Unionfind(int _n) : n(_n) { 
        p.assign(n, 0), rnk.assign(n, 1); 
        for(int i = 0; i < n; i++)p[i] = i;
    }
    int findset(int i){return p[i] = (p[i] == i) ? i : findset(p[i]);}
    bool sameset(int i,int j) { return findset(i) == findset(j);}
    void unionset(int i,int j) {
        int x = findset(i), y = findset(j);
        if(x != y){
            if(rnk[x] > rnk[y]) p[y] = x;
            else p[x] = y, rnk[y] += (rnk[x] == rnk[y]);
        }
    }
};


//with rollback

struct dsu_save {
    int v, rnkv, u, rnku, united;
    dsu_save() {}
    dsu_save(int _v, int _rnkv, int _u, int _rnku, int united)
        : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku), united(united) {}
};
class Unionfind{
public:
    vector<int> p, rnk;
    int ans, n;   //CC
    vector<dsu_save> lastadded;
    Unionfind(int _n) : n(_n) { 
        ans = n, p.assign(n, 0), rnk.assign(n, 1);
        for(int i = 0; i < n; i++) p[i] = i;
    }
    int findset(int i){return (p[i] == i) ? i : findset(p[i]);}
    bool sameset(int i,int j){return findset(i) == findset(j);}
    void unionset(int i,int j){
        int x=findset(i), y=findset(j);
        if(x!=y){
            ans--;
            if(rnk[x] > rnk[y]) lastadded.emplace_back(y, rnk[y], x, rnk[x], 1), p[y] = x;
            else lastadded.emplace_back(x, rnk[x], y, rnk[y], 1), p[x] = y, rnk[y] += (rnk[x] == rnk[y]);
        }
        else lastadded.emplace_back(x, rnk[x], y, rnk[y], 0);
    }
    void rollback(){
        if(lastadded.empty())return;
        auto x = lastadded.back();
        lastadded.pop_back();
        if(!x.united)return;
        ans++;
        p[x.v] = x.v, p[x.u] = x.u;
        rnk[x.v] = x.rnkv, rnk[x.u] = x.rnku;
    }
};


//online bipartite check with rollback
struct dsu_save {
    int v, rnkv, u, rnku, united, valv, valu;
    dsu_save() {}
    dsu_save(int _v, int _rnkv, int _u, int _rnku, int united, int _vv, int _vu)
        : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku), united(united), valv(_vv), valu(_vu) {}
};
class Unionfind{
public:
    vector<int> p, rnk, val;
    vector<dsu_save> lastadded;
    int n;
    Unionfind(int _n) : n(_n) {
        val.assign(n, 0), p.assign(n,0), rnk.assign(n, 1);
        for(int i = 0; i < n; i++) p[i] = i;
    }
    int findset(int i,int &t){
        return t += val[i], (p[i] == i) ? i : findset(p[i], t);
    }
    bool unionset(int i,int j){
        int a = 0, b = 0;
        int x = findset(i,a), y = findset(j,b);
        if(x != y){
            if(rnk[x] > rnk[y])
                lastadded.emplace_back(y, rnk[y], x, rnk[x], 1, val[y], val[x]), p[y] = x, val[y] = 1 + ((a ^ b) & 1);
            else 
                lastadded.emplace_back(x, rnk[x], y, rnk[y], 1, val[x], val[y]), p[x] = y, rnk[y] += (rnk[x]==rnk[y]), val[x] = 1 + ((a ^ b) & 1);}
        }
        else return lastadded.emplace_back(x, rnk[x], y, rnk[y], 0, val[x], val[y]), (a ^ b) & 1;
        return true;
    }
    void rollback(){
        if(lastadded.empty())return;
        auto x = lastadded.back();
        lastadded.pop_back();
        if(!x.united)return;
        p[x.v] = x.v, p[x.u] = x.u;
        rnk[x.v] = x.rnkv, rnk[x.u] = x.rnku;
        val[x.v] = x.valv, val[x.u] = x.valu;
    }
};
