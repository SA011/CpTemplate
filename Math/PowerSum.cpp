
namespace PSUM{
	const int N = 5e3 + 2;
	ll bern[N], sum[N];
	ll fac[N], ifac[N];
	ll bigmod(ll a, int n){
		ll ans = 1;
		while(n){
			if(n & 1)ans = ans * a % mod;
			n >>= 1;
			a = a * a % mod;
		}
		return ans;
	}
	void init(){			//call me first
		fac[0] = 1;
		for(int i = 1; i < N; i++)fac[i] = fac[i - 1] * i % mod;
		ifac[N - 1] = bigmod(fac[N - 1], mod - 2);
		for(int i = N - 2; i >= 0; i--)ifac[i] = ifac[i + 1] * (i + 1) % mod;
	
		for(int i = 0; i < N; i++){
			bern[i] = 1;
			for(int j = 0; j < i; j++){
				bern[i] = (bern[i] - fac[i] * ifac[j] % mod * ifac[i - j + 1] % mod * bern[j]) % mod;
				if(bern[i] < 0)bern[i] += mod;
			}
		}
	}
	//sum of i ^ k for 1 <= i <= n
	ll getPowerSum(ll n, int k){
		ll ans = 0;
		ll temp = n;
		for(int i = k; i >= 0; i--, temp = temp * n % mod){
			ans = (ans + bern[i] * ifac[i] % mod * ifac[k - i + 1] % mod * temp) % mod;
		}
		
		return (ll)ans * fac[k] % mod;
	}
	void build(ll n){
		init();
		for(int i = 0; i < N; i++){
			sum[i] = getPowerSum(n, i);
		}
	}
}
