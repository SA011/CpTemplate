//Range Updates like A[i] = min(A[i], x)
struct vert{
    int mx, mx2, num;
    ll sum=0;
};
vert st[N << 2];
ll ara[N];
int lz[N << 2];
const ll invalid = 2e9;
void propagate(int node){
    if(lz[node] == invalid)return;
    if(st[node].mx > lz[node]){
        lz[node << 1] = min(lz[node], lz[node << 1]);
        lz[node << 1 | 1] = min(lz[node], lz[node << 1 | 1]);
        
        st[node].sum -= st[node].num * (st[node].mx - lz[node]);
        st[node].mx = lz[node];
    }
    lz[node] = invalid;
}
void f(vert &a, vert &b, vert &c){
    a.mx = max(b.mx, c.mx);
    if(a.mx != c.mx)a.mx2 = max(c.mx, b.mx2), a.num = b.num;
    else if(a.mx != b.mx)a.mx2 = max(c.mx2, b.mx), a.num = c.num;
    else a.mx2 = max(b.mx2, c.mx2), a.num = b.num + c.num;
    a.sum = b.sum + c.sum;
}
void init(int node, int ss, int sf){
    lz[node] = -1;
    if(ss == sf){
        st[node].mx = ara[ss];
        st[node].sum = ara[ss];
        st[node].mx2 = -invalid;
        st[node].num = 1;
        return;
    }
    ll mid = ss + sf >> 1;
    init(node << 1, ss, mid);
    init(node << 1 | 1, mid + 1, sf);
    f(st[node], st[node << 1], st[node << 1 | 1]);
}
void update(int node, int ss, int sf, int qs, int qe, int t){
    propagate(node);
    if(st[node].mx <= t)return;
    if(qs > sf || qe < ss || qs>qe)return;
    if(qs <= ss && qe >= sf && st[node].mx2 < t){
        lz[node] = t;
        propagate(node);
        return;
    }
    int mid = ss + sf >> 1;
    update(node << 1, ss, mid, qs, qe, t);
    update(node << 1 | 1, mid + 1, sf, qs, qe, t);
    f(st[node], st[node << 1], st[node << 1 | 1]);
}
ii query(int node, int ss, int sf, int qs, int qe){
    propagate(node);
    if(qs>sf || qe<ss || qs>qe)return ii(0,0);
    if(qs <= ss && qe>=sf)return ii(st[node].sum, st[node].mx);
    ii a = query(node << 1, ss, mid, qs, qe);
    ii b = query(node << 1 | 1, mid + 1, sf, qs, qe);
    return ii(a.fi + b.fi, max(a.se, b.se));
}
