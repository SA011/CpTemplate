ll mult(ll x, ll y, ll md) {
    ll ans = 0;
    while(y) {
        if(y & 1)ans = (ans + x) % md;
        x = (x + x) % md;
        y >>= 1;
    }
    return ans;
}

ll f(ll x, ll c, ll md) {
    return (mult(x, x, md) + c) % md;
}

ll binpower(ll base, ll e, ll md) {
    ll result = 1;
    base %= md;
    while (e) {
        if (e & 1)result = mult(result, base, md);
        base =mult(base, base, md);
        e >>= 1;
    }
    return result;
}

bool check_composite(ll n, ll a, ll d, int s) {
    ll x = binpower(a, d, n);
    if (x == 1 || x == n - 1)return false;
    for (int r = 1; r < s; r++) {
        x =mult(x, x, n);
        if (x == n - 1)return false;
    }
    return true;
}

bool MillerRabin(ll n) {
    if (n < 2)return false;
    //if(n < N)return isprime(n);   //sieve
    int r = 0;
    ll d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for(int a: {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (n == a)return true;
        if (check_composite(n, a, d, r))return false;
    }
    return true;
}

ll pollardRho(ll n, ll x0 = 1, ll c = 2) {
    ll x = x0, y = x0, g = 1;
    while(g == 1) {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = __gcd(n, abs(y - x));
    }
    return g;
}

void factorize(ll n, map<ll, ll> &mp) {
    ll c = 2, ans;
    //for(int i = 0; i < prime_ind && prime[i] * prime[i] <= n; i++) //sieve
        //while(n % prime[i] == 0) {
            //mp[prime[i]]++;
            //n /= prime[i];
        //}
    if(n == 1)return;
    if(MillerRabin(n)) {
        mp[n]++;
        return;
    }
    while((ans = pollard_rho(n, 1, c)) == n)c++;
    factorize(ans, mp);
    factorize(n / ans, mp);
}

//////////////////////////////////////////////////////////////


// Brent

long long brent(long long n, long long x0 = 2, long long c = 1) {
    long long x = x0;
    long long g = 1;
    long long q = 1;
    long long xs, y;

    int m = 128;
    int l = 1;
    while (g == 1) {
        y = x;
        for (int i = 1; i < l; i++)
            x = f(x, c, n);
        int k = 0;
        while (k < l && g == 1) {
            xs = x;
            for (int i = 0; i < m && i < l - k; i++) {
                x = f(x, c, n);
                q = mult(q, abs(y - x), n);
            }
            g = __gcd(q, n);
            k += m;
        }
        l *= 2;
    }
    if (g == n) {
        do {
            xs = f(xs, c, n);
            g = __gcd(abs(xs - y), n);
        } while (g == 1);
    }
    return g;
}


///////////////////////////////////////////////////////////////

//MillerRabbin
long long mult(long long a, long long b, long long mod) {
    long long result = 0;
    while (b) {
        if (b & 1)
            result = (result + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return result;
}

ll binpower(ll base, ll e, ll md) {
    ll result = 1;
    base %= md;
    while (e) {
        if (e & 1)
            result = mult(result, base, md);
        base = mult(base, base, md);
        e >>= 1;
    }
    return result;
}

bool check_composite(ll n, ll a, ll d, int s) {
    ll x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = mult(x, x, n);
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(ll n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    ll d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////

//Fermat

ll bigmod(ll a, ll p, ll m){
    ll res = 1, x = a;
    while(p){
        if(p & 1) res = (res * x) % m;
        x = (x * x) % m;
        p >>= 1;
    }
    return res;
}

bool probablyPrimeFermat(ll n, int iter = 10) {
    if (n < 4)
        return n == 2 || n == 3;

    for (int i = 0; i < iter; i++) {
        int a = 2 + rng() % (n - 3);
        if (bigmod(a, n - 1, n) != 1)
            return false;
    }
    return true;
}
