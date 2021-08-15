namespace SparseTable {
    ll st[N][K];
    int lg[N];
    ll ara[N];
    void init(int n) {
        for(int i = 0; i < n; i++)st[i][0] = ara[i];
        lg[1] = 0;
        for(int i = 2; i <= n; i++)lg[i] = lg[i >> 1] + 1;
        for(int i = 1; i < K; i++) {
            for(int j = 0; j + (1 << i) <= n; j++)
                st[j][i] = max(st[j][i - 1], st[j + (1 << i - 1)][i - 1]);
        }
    }
    ll query(ll l,ll r) {
        int x = lg[r - l + 1];
        return max(st[l][x], st[r - (1 << x) + 1][x]);
    }
};
