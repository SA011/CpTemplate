namespace COMB{
	const int nmax = 2e7 + 5;
	int fac[nmax], ifac[nmax];
	int m = 1e9 + 7;

	int bigmod(int a, int p){
		int res = 1;
		while(p){
			if(p & 1) res = ((long long)res * a) % m;
			a = ((long long)a * a) % m;
			p >>= 1;
		}
		return res;
	}	
	void pre(int MOD){
		fac[0] = 1;
		m = MOD;
		for(int i = 1; i < nmax; i++)fac[i] = (long long)fac[i - 1] * i % m;
		
		ifac[nmax - 1] = bigmod(fac[nmax - 1], m - 2);
		for(int i = nmax - 2; i >= 0; i--)ifac[i] = (long long)ifac[i + 1] * (i + 1) % m;
	}
	
	int C(int n, int k){
		if(n < k || k < 0)return 0;
		return (long long) fac[n] * ifac[k] % m * ifac[n - k] % m;
	}
}
