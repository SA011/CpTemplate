struct NTT{
    ll MD, M = 1, R;
    vector<int> r;
    vector<ll> w[2];
    ll bigmod(ll a, ll p, ll m){
        ll res = 1, x = a;
        while(p){
            if(p & 1)res = (res * x) % m;
            x = (x * x) % m;
            p >>= 1;
        }
        return res;
    }
    ll primitive_root(int n){
        //Try using 3/5
        return 3;
        int p = n - 1;
        vector<int> d;
        for(int i = 2; i * i <= p; i++){
            if(p % i == 0){
                d.push_back(i);
                while(p % i == 0)p /= i;
            }
        }
        if(p > 1)d.push_back(p);
        for(int i = 2; i <= n; i++){
            bool ok = true;
            for(auto x : d)ok &= (bigmod(i, (n - 1) / x, n) != 1);
            if(ok)return i;
        }
        assert(false);
    }
    void pre(int n, int md){
        int u = 0;
        M = 1, MD = md;
        while(M < n)M <<= 1,u++;
        r.resize(M);
        w[0].resize(M, 1);
        w[1].resize(M, 1);
        R = primitive_root(MD);
        w[0][1] = bigmod(R, (MD - 1) / M, MD);
        w[1][1] = bigmod(w[0][1], MD - 2, MD);
        for(int i = 1; i < M; i++){
            int l = __builtin_ctz(i);
            r[i] = r[i ^ (1 << l)] | (1 << (u - l - 1));
            w[0][i] = w[0][i-1] * w[0][1] % MD;
            w[1][i] = w[1][i-1] * w[1][1] % MD;
        }
    }
    void fft(vector<ll> &a, bool inv = false){
        for(int i = 0; i < M; i++)if(i < r[i]) swap(a[i], a[r[i]]);
        for(int len = 2; len <= M; len <<= 1){
            for(int i = 0, inc = M / len; i < M; i += len){
                for(int j = 0, l = 0; j < (len >> 1); j++, l += inc){
                    ll u = a[i + j], v = a[i + j + (len >> 1)] * w[inv][l] % MD;
                    a[i + j] = (u + v >= MD ? u + v - MD : u + v);
                    a[i + j + (len >> 1)] = (u < v ? u - v + MD : u - v);
                }
            }
        }
        if(inv){
            ll r = bigmod(M, MD - 2, MD);
            for(auto &x : a)x = x * r % MD;
        }
    }
    void fft2D(vector<vector<ll>> &v, bool inv = false){
        pre(v[0].size(), MD);
        for(auto &x : v)fft(x, inv);
        pre(v.size(), MD);
        for(int i = 0; i < v[0].size(); i++){
            vector<ll> temp(v.size());
            for(int j = 0; j < v.size(); j++)temp[j] = v[j][i];
            fft(temp, inv);
            for(int j = 0; j < v.size(); j++)v[j][i] = temp[j];
        }
    }
    void multiply(vector<ll> &a, vector<ll> &b, vector<ll> &v1, ll md){
        pre(a.size() + b.size(), md);
//        assert(a.size()+b.size()<=M);
        v1.resize(M);
        vector<ll> v2(M);
        for(int i = 0; i < a.size(); i++) v1[i] = a[i];
        for(int i = 0; i < b.size(); i++) v2[i] = b[i];
        fft(v1);
        fft(v2);
        for(int i = 0; i < M; i++)v1[i] = v1[i] * v2[i] % MD;
        fft(v1, 1);
    }
    void multiply2D(vector<vector<ll>> &a, vector<vector<ll>> &b, vector<vector<ll>> &v1, ll md){
        MD = md;
        int n = max(a.size(), b.size());
        int m = max(a[0].size(), b[0].size());
        int Mxn = 1, Mxm = 1;
        while(Mxn < n)Mxn <<= 1;
        Mxn <<= 1;
        while(Mxm < m)Mxm <<= 1;
        Mxm <<= 1;
        v1.resize(Mxn, vector<ll>(Mxm));
        vector<vector<ll>> v2(Mxn, vector<ll>(Mxm));
        for(int i = 0; i < a.size(); i++){
            for(int j = 0; j < a[i].size(); j++)v1[i][j] = a[i][j];
        }
        for(int i = 0; i < b.size(); i++){
            for(int j = 0; j < b[i].size(); j++)v2[i][j] = b[i][j];
        }
        fft2D(v1);
        fft2D(v2);
        for(int i = 0; i < Mxn; i++)
            for(int j = 0; j < Mxm; j++)
                v1[i][j] = v1[i][j] * v2[i][j] % MD;
        fft2D(v1, 1);
    }
    void POWER(vector<ll> &a, ll n, vector<ll> &v1, ll md){
        // call pre(possible maximum length, md) before this
        v1.resize(M);
        for(int i = 0; i < a.size(); i++) v1[i] = a[i];
        fft(v1);
        for(int i = 0; i < M; i++) v1[i] = bigmod(v1[i], n, MD);
        fft(v1, 1);
    }
};
