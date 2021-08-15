ll st[N << 2];
ll lz[N << 2];
ll ara[N];
ll f(ll l, ll r){
    return l + r;
}
void propagate(int node, int ss, int sf){
    if(lz[node] == 0)return;
    st[node] += (sf - ss + 1) * lz[node];
    if(ss != sf){
        lz[node << 1] += lz[node];
        lz[node << 1 | 1] += lz[node];
    }
    lz[node] = 0;
}
void init(int node, int ss, int sf){
    if(ss == sf){
        st[node] = ara[ss];
        return;
    }
    int mid = ss + sf >> 1;
    init(node << 1, ss, mid);
    init(node << 1 | 1, mid + 1, sf);
    st[node] = f(st[node << 1], st[node << 1 | 1]);
}
void update(int node, int ss, int sf, int qs, int qe, ll val){
    propagate(node, ss, sf);
    if(qs > sf || qe < ss || qe < qs)return;
    if(qs <= ss && qe >= sf){
        lz[node] = val;
        propagate(node, ss, sf);
        return;
    }
    int mid = ss + sf >> 1;
    update(node << 1, ss, mid, qs, qe, val);
    update(node << 1 | 1, mid + 1, sf, qs, qe, val);
    st[node] = f(st[node << 1], st[node << 1 | 1]);
}

ll query(int node, int ss, int sf, int qs, int qe){
    propagate(node, ss, sf);
    if(qs > sf || qe < ss || qe < qs)return 0;
    if(qs <= ss && qe >= sf)return st[node];
    int mid = ss + sf >> 1;
    return f(query(node << 1, ss, mid, qs, qe), query(node << 1 | 1, mid + 1, sf, qs, qe));
}
