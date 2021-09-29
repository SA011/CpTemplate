
// number of co-prime of n less than n
ll phi(ll n){
    ll ans = n;
    for(ll i = 2; i * i <= n; i++){
        if(n % i == 0)ans -= ans / i;
        while(n % i == 0)n /= i;
    }
    return ans;
}
ll eulerPhi(ll n){
    ll ans = n;
    for(int i = 0; i < primeInd && (ll) prime[i] * prime[i] <= n; i++){
        if(n % prime[i] == 0)ans -= ans / prime[i];
        while(n % prime[i] == 0)n /= prime[i];
    }
    if(n != 1)ans -= ans / n;
    return ans;
}

//generating all phi(1..n)
int phl[N];

void phiAll(){
    for(int i = 2; i < N; i++)phl[i] = i;
    phl[0] = 0;
    phl[1] = 1;
    for(int i = 2; i < N; i++){
        if(phl[i] == i){
            phl[i] = i - 1;
            for(int j = 2; j * i < N; j++)
                phl[i * j] = (phl[i * j] / i) * (i - 1);
        }
    }
}
