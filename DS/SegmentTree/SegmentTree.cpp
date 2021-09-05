ll st[N << 2];
ll ara[N];
ll f(ll l,ll r){
    return l + r;
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
void update(int node, int ss, int sf, int pos, ll val){
    if(ss == sf){
        st[node] += val;
        return;
    }
    int mid = ss + sf >> 1;
    if(pos <= mid) update(node << 1, ss, mid, pos, val);
    else update(node << 1 | 1, mid + 1, sf, pos, val);
    st[node] = f(st[node << 1], st[node << 1 | 1]);
}
ll query(int node, int ss, int sf, int qs, int qe){
    if(qs > sf || qe < ss || qe < qs)return 0;
    if(qs <= ss && qe >= sf)return st[node];
    int mid = ss + sf >> 1;
    return f(query(node << 1, ss, mid, qs, qe), query(node << 1 | 1, mid + 1, sf, qs, qe));
}
///////////////////////////////////////////////////

//Iterative
ll st[N << 2];
void update(int k, int val, int n){
    k += n;
    st[k] = val;
    while(k > 1){
        st[k >> 1] = max(st[k], st[k ^ 1]);
        k >>= 1;
    }
}
ll query(int l, int r, int n){
    l += n, r += n + 1;
    ll ans = 0;
    while(l < r){
        if(l & 1)ans = max(ans, st[l++]);
        if(r & 1)ans = max(ans, st[--r]);
        l >>= 1;
        r >>= 1;
    }
    return ans;
}
///////////////////////////////////////////////////

struct SegmentTree{
    using T = int;
    struct Node{
        T res;
        Node(T _a = T()) : res(_a) {}
    };
    
    Node merge(Node a, Node b){
        return Node(a.res + b.res);
    }
    
    vector<Node> st;
    int n;
    
    void init(int _n){
        if(_n <= 0)return;
        n = _n;
        int m = ceil(log2(n)) + 1;
        st.resize((1 << m) + 5);
    }
    SegmentTree(int _n = 0){
        init(_n);
    }
    
    void build(int x, int l, int r, vector<T> &v){
        if(l == r){
            st[x].res = v[l];
            return;
        }
        int m = l + r >> 1;
        build(x << 1, l, m, v);
        build(x << 1 | 1, m + 1, r, v);
        st[x] = merge(st[x << 1], st[x << 1 | 1]);
    }
    void build(vector<T> &v){ build(1, 0, n - 1, v);}
    void build(T x){ vector<T> v(n, x); build(1, 0, n - 1, v);}
    
    
    void update(int x, int l, int r, int p, T v){
        if(l == r){
            st[x].res += v;
            return;
        }
        int m = l + r >> 1;
        if(p <= m) update(x << 1, l, m, p, v);
        else update(x << 1 | 1, m + 1, r, p, v);
        st[x] = merge(st[x << 1], st[x << 1 | 1]);
    }
    void update(int p, T v){ update(1, 0, n - 1, p, v);}
    
    
    
    Node query(int x, int sl, int sr, int l, int r){
        if(sr < l || sl > r)return T();
        if(sl >= l && sr <= r)return st[x].res;
        int m = sl + sr >> 1;
        return merge(query(x << 1, sl, m, l, r), query(x << 1 | 1, m + 1, sr, l, r));
    }
    Node query(int l, int r){
        if(l > r)return Node();
        return query(1, 0, n - 1, l, r);
    }
};
