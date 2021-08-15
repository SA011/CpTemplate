struct vert{
    vert *l, *r;
    ll s;
    vert(ll s = 0) : s(s) {l = r = NULL;}
};

ll ara[N];
ll f(ll l, ll r){
    return l + r;
}
void init(vert* rt, int ss, int sf){
    if(ss == sf){
        rt -> s = ara[ss];
        return;
    }
    int mid = ss + sf >> 1;
    rt -> l = new vert;
    rt -> r = new vert;
    init(rt -> l, ss, mid);
    init(rt -> r, mid + 1, sf);
    rt -> s = f(rt -> l -> s, rt -> r -> s);
}
void update(vert* cur, vert* pre, int ss, int sf, int pos, ll val){
    if(ss==sf){
        cur->s = pre->s + val;
        return;
    }
    int mid = ss + sf >> 1;
    if(pos <= mid){
        cur -> r = pre -> r;
        cur -> l = new vert;
        update(cur -> l, pre -> l, ss, mid, pos, val);
    }
    else{
        cur -> l = pre -> l;
        cur -> r = new vert;
        update(cur -> r, pre -> r, mid + 1, sf, pos, val);
    }
    cur -> s = f(cur -> l -> s, cur -> r -> s);
}
//l == NULL will return r -> (qs...qe). Otherwise, returns (r - l) -> (qs...qe)
ll query(vert *r, vert *l, int ss, int sf, int qs, int qe){
    if(qs > sf || qe < ss || qs>qe)return 0;
    if(qs <= ss && qe >= sf)return r -> s - (l ? l -> s : 0);
    int mid = ss + sf >> 1;
    return f(query(r -> l, l -> l, ss, mid, qs, qe), query(r -> r, l -> r, mid + 1, sf, qs, qe));
}


//Without pointer
int pstInd;
struct vert{
    int l,r;
    ll s;
    vert(ll s = 0) : s(s) { l = r = 0;}
};
vert st[N * K]; // K = log2(n) + 4
ll f(ll l, ll r){
    return l + r;
}
ll ara[N];
void init(ll node, int ss, int sf){
    if(ss == sf){
        st[node].s = ara[ss];
        return;
    }
    int mid = ss + sf >> 1;
    st[node].l = ind++;
    st[node].r = ind++;
    init(st[node].l, ss, mid);
    init(st[node].r, mid + 1, sf);
    st[node].s = f(st[st[node].l].s, st[st[node].r].s);
}
void update(int cur, int pre, int ss, int sf, int pos, ll val){
    if(ss == sf){
        st[cur].s = st[pre].s + val;
        return;
    }
    int mid = ss + sf >> 1;
    if(pos <= mid){
        st[cur].r = st[pre].r;
        st[cur].l = ind++;
        update(st[cur].l, st[pre].l, ss, mid, pos, val);
    }
    else{
        st[cur].l = st[pre].l;
        st[cur].r = ind++;
        update(st[cur].r, st[pre].r, mid + 1, sf, pos, val);
    }
    st[cur].s = f(st[st[cur].l].s, st[st[cur].r].s);
}
ll query(int R, int L, int ss, int sf, int qs, int qe){
    if(qs > sf || qe < ss || qs > qe)return 0;
    if(qs <= ss && qe >= sf)return st[R].s - st[L].s;
    int mid = ss + sf >> 1;
    return f(query(st[R].l, st[L].l, ss, mid, qs, qe), query(st[R].r,st[L].r, mid + 1, sf, qs, qe));
}
