int mu[N];
void mobius(){
    memset(mu, -1, sizeof mu);
    mu[1] = 1;
    for(int i = 2; i < N; i++)
        for(int j = (i << 1) ; j < N; j += i)mu[j] -= mu[i];
}

//counts number of coprime of A in an array
//divs = divisors of A
//cnt = frequency count of the divisors of array elements
int numberOfCoprime(vector<ll> &cnt, vector<ll> &divs){
    int a = 0;
    for(auto x : divs) a += cnt[x] * mu[x];
    return a;
}

vector<ll> dv[N];
ll largestCoprimeProduct(vector<ll> &v, vector<ll> &cnt){
    ll ans = 0;
    vector<ll> a;
    //sort(v.begin(), v.end()) 
    for(int i = (int)v.size() - 1; i >= 0; i--){
        int x = numberOfCoprime(cnt, dv[v[i]]);
        while(x--){
            while(1){
                for(auto y : dv[a.back()])cnt[y]--;
                if(__gcd(a.back(), v[i]) == 1)break;
                a.pop_back();
            }
            ans = max(ans, a.back() * v[i]);
            a.pop_back();
        }
        a.push_back(v[i]);
        for(auto y : dv[v[i]])cnt[y]++;
    }
    while(!a.empty()){
        for(auto y : dv[a.back()])cnt[y]--;
        a.pop_back();
    }
    return ans;
}
