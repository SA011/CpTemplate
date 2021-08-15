ll st[N << 2][N << 2];
ll ara[N][N];
ll f(ll l, ll r){
    return l + r;
}
void initCol(int C, int R, int sc, int ec, int sr, int er){
    if(sc == ec){
        if(sr == er)
            st[R][C] = ara[sr][sc];
        else
            st[R][C] = f(st[R << 1][C], st[R << 1 | 1][C]);
        return;
    }
    int mid = sc + ec >> 1;
    initCol(C << 1, R, sc, mid, sr, er);
    initCol(C << 1 | 1, R, mid + 1, ec, sr, er);
    st[R][C] = f(st[R][C << 1], st[R][C << 1 | 1]);
}
void init(int R, int sr, int er, int m){
    if(sr == er){
        initCol(1, R, 0, m - 1, sr, er);
        return;
    }
    int mid = sr + er >> 1;
    init(R << 1, sr, mid, m);
    init(R << 1 | 1, mid + 1, er, m);
    initCol(1, R, 0, m - 1, sr, er);
}
void updateCol(int C, int R, int sc, int ec, int sr, int er, int posC, ll val){
    if(sc == ec){
        if(sr == er)
            st[R][C] += val;
        else
            st[R][C] = f(st[R << 1][C], st[R << 1 | 1][C]);
        return;
    }
    int mid = sc + ec >> 1;
    if(posC <= mid) updateCol(C << 1, R, sc, mid, sr, er, posC, val);
    else updateCol(C << 1 | 1, R, mid + 1, ec, sr, er, posC, val);
    st[R][C] = f(st[R][C << 1], st[R][C << 1 | 1]);
}
void update(int R, int sr, int er, int posR, int posC, ll val, int m){
    if(sr == er){
        updateCol(1, R, 0, m - 1, sr, er, posC, val);
        return;
    }
    int mid = sr + er >> 1;
    if(posR <= mid) update(R << 1, sr, mid, posR, posC, val, m);
    else update(R << 1 | 1, mid + 1, er, posR, posC, val, m);
    updateCol(1, R, 0, m - 1, sr, er, posC, val);
}
ll queryCol(int C, int R, int sc, int ec, int lc, int rc){
    if(sc > rc || ec < lc)return 0;
    if(sc >= lc && ec <= rc)return st[R][C];
    int mid = sc + ec >> 1;
    return f(queryCol(C << 1, R, sc, mid, lc, rc), queryCol(C << 1 | 1, R, mid + 1, ec, lc, rc));
}
ll query(int R, int sr, int er, int lr, int lc, int rr, int rc, int m){
    if(sr > rr || er < lr)return 0;
    if(sr >= lr && er <= rr) return queryCol(1, R, 0, m-1, lc, rc);
    int mid = sr + er >> 1;
    return f(query(R << 1, sr, mid, lr, lc, rr, rc, m), query(R << 1 | 1, mid + 1, er, lr, lc, rr, rc, m));
}

