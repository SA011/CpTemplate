//sieve needed
ll mult(ll x,ll y,ll md){
  ll ans=0;
  while(y){
    if(y&1)ans=(ans+x)%md;
    x=(x+x)%md;     y>>=1;
  }
  return ans;
}
ll f(ll x,ll c,ll md){
    return (mult(x,x,md)+c)%md;
}
ll binpower(ll base, ll e, ll md) {
  ll result = 1;    base %= md;
  while (e) {
    if (e & 1)result =mult(result,base,md);
    base =mult(base,base,md);    e >>= 1;
  }
  return result;
}
bool check_composite(ll n, ll a, ll d, int s){
  ll x = binpower(a, d, n);
  if (x == 1 || x == n - 1)return false;
  for (int r = 1; r < s; r++) {
    x =mult(x,x,n);
    if (x == n - 1)return false;
  }
  return true;
};
bool MillerRabin(ll n) {
  if (n < 2)return false;
  if(n<asz)return isprime(n);
  int r = 0;      ll d = n - 1;
  while ((d & 1) == 0) {
    d >>= 1;     r++;
  }
 for(int a:{2,3,5,7,11,13,17,19,23,29,31,37}){
   if (n == a)return true;
   if (check_composite(n,a,d,r))return false;
 }
  return true;
}
ll pollard_rho(ll n,ll x0=1,ll c=2){
  ll x=x0,y=x0,g=1;
  while(g==1){
    x=f(x,c,n);  y=f(y,c,n);   y=f(y,c,n);
    g=__gcd(n,abs(y-x));
  }
  return g;
}
void factorize(ll n,map<ll,ll> &mp){
  ll i=0,c=2,ans;
  for(;i<prime_ind&&prime[i]*prime[i]<=n;i++)
    while(n%prime[i]==0){
      mp[prime[i]]++;   n/=prime[i];
    }
  if(n==1)return;
  if(MillerRabin(n)){
    mp[n]++;return;
  }
  while((ans=pollard_rho(n,1,c))==n)c++;
  factorize(ans,mp);  factorize(n/ans,mp);
}
