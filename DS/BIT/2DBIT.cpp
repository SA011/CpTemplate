ll bit[N][N];
void update(int r, int c, ll val){
    for(++r, ++c; r < N; r += r & -r){
        for(int i = c; i < N; i += i & -i)
            bit[r][i] += val;
    }
}
ll query(int r, int c){
    ll s = 0;
    for(++r, ++c; r > 0; r -= r & -r){
        for(int i = c; i > 0; i -= i & -i)
            s += bit[r][i];
    }
    return s;
}
ll query(int lr, int lc, int rr, int rc){
    return query(rr, rc) - query(rr, lc - 1) - query(lr - 1, rc) + query(lr - 1, lc - 1);
}
/////////////////////////////////////////////

// Range Update
ll bit[4][N][N];
void update1(int r, int c, ll val){
    ll a = val * (r - 1), b = val * (c - 1), d = val * (r - 1) * (c - 1);
    for(++r, ++c; r < N; r += r & -r){
        for(int i = c; i < N; i += i & -i)
            bit[0][r][i] += val, bit[1][r][i] += a, bit[2][r][i] += b, bit[3][r][i] += d;
    }
}

void update(int lr, int lc, int rr, int rc, ll val){
    update1(lr, lc, val);
    update1(lr, rc + 1, -val);
    update1(rr + 1, lc, -val);
    update1(rr + 1, rc + 1, val);
}
ll query(int r, int c){
    ll s = 0, b = r, a = c, k = r * c;
    for(++r, ++c; r > 0; r -= r & -r){
        for(int i = c; i > 0; i -= i & -i)
            s += bit[0][r][i] * k - bit[1][r][i] * a - bit[2][r][i] * b + bit[3][r][i];
    }
    return s;
}

ll query(int lr, int lc, int rr, int rc){
    return query(rr, rc) - query(rr, lc - 1) - query(lr - 1, rc) + query(lr - 1, lc - 1);
}
