#define lastone(n) ((n)&(-(n)))
ll bit[N];
void update(int ind, ll val){
    for(++ind; ind < N; ind += lastone(ind)) 
        bit[ind] += val;
}
ll query(int a){
    ll s = 0;
    for(++a; a > 0; a -= lastone(a))
        s += bit[a];
    return s;
}
ll query(int a, int b){
    return query(b) - query(a - 1);
}
