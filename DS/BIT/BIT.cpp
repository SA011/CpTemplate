ll bit[N];
void update(int ind, ll val){
    for(++ind; ind < N; ind += ind & -ind) 
        bit[ind] += val;
}
ll query(int a){
    ll s = 0;
    for(++a; a > 0; a -= a & -a)
        s += bit[a];
    return s;
}
ll query(int l, int r){
    return query(r) - query(l - 1);
}
///////////////////////////////////////////////

//Range Update
ll bit[2][N];
void update1(int ind, ll val, ll val2){
    for(++ind; ind < N; ind += ind & -ind)
        bit[0][ind] += val, bit[1][ind] += val2;
}
void update(int l, int r, ll val){
    update1(l, val, (l - 1) * val);
    update1(r + 1, -val, -r * val);
}
ll query(int l){
    ll s = 0, u = l;
    for(++l; l > 0; l -= l & -l)s += u * bit[0][l] - bit[1][l];
    return s;
}
ll query(int l, int r){
    return query(r) - query(l-1);
}
