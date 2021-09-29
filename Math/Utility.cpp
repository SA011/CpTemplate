/* 
    * Fib(n - 1) * Fib(n + 1) - Fib(n) * Fib(n) = (-1)^n
    * Fib(n + k) = Fib(k)Fib(n + 1) + Fib(k - 1)Fib(n)
    * GCD(Fib(n), Fib(m)) = Fib(GCD(n, m))
    * Fib(2k) = Fib(k)(2 * Fib(k + 1) - Fib(k))
    * Fib(2k + 1) = Fib(k)^2 + Fib(k + 1)^2
    * Fibsum(n) = 2Fibsum(n - 1) - Fibsum(n - 3)
    * Catalan(n) = (4n - 2) * Catalan(n - 1) / (n + 1)
    * Catalan(n) = (2nCn) / (n + 1)
    * [Sum of (i^k) for(i = 1....n)] = Sum of(j! * s2(k, j) * ((n + 1)C(j + 1))) for (j = 1...k)
    * Stirling2(n, k) =  Sum((-1)^(k - j) * (kCj) * j^n) / (k!)  for(j = 0...k)
    * S2(i, j) = S2(i - 1, j - 1) + S2(i - 1, j) * j;
*/

//returns {f(n), f(n+1)}
pair<ll, ll> fib(ll n, ll md){
    if(n == 0)return {0, 1};
    auto p = fib(n >> 1, md);
    ll c = ((p.first * p.first) + (p.second * p.second)) % md;
    ll d = p.first * (2 * p.second + md - p.first) % md;
    if(n & 1) return {c, (c + d) %md};
    return {d, c};
}


//Stirling number of 2nd kind
ll s2[105][105];
void Stirling2(int mxn, int mxk, ll md){
    memset(s2, 0, sizeof s2);
    s2[0][0] = 1;
    for(int i = 1; i < mxn; i++){
        for(int j = 1; j < mxk; j++){
            s2[i][j] = (s2[i - 1][j - 1] + s2[i - 1][j] * j) % md;
        }
    }
}


//Josehpus

int joseph(int n, int k) {
    int res = 0;
    for (int i = 1; i <= n; ++i)
      res = (res + k) % i;
    return res + 1;
}
int josephus(int n, int k) {
    if (n == 1)
        return 0;
    if (k == 1)
        return n - 1;
    if (k > n)
        return (joseph(n - 1, k) + k) % n;
    int cnt = n / k;
    int res = josephus(n - cnt, k);
    res -= n % k;
    if (res < 0)
        res += n;
    else
        res += res / (k - 1);
    return res;
}
