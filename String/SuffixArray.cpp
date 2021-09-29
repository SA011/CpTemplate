struct SA{
	int *sa, *ra, *cnt, *pos, *lcp, *lg;
	int **st;
	int n, A;
	string s;
	void srt(int mx, int k){
		for(int i = 0; i < mx; i++)cnt[i] = 0;
		for(int i = 0; i < n; i++)cnt[(i + k >= n ? 0 : ra[i + k])]++;
		for(int i = 1; i < mx; i++)cnt[i] += cnt[i - 1];
		for(int i = mx - 1; i > 0; i--)cnt[i] = cnt[i - 1];
		cnt[0] = 0;
		for(int i = 0; i < n; i++)pos[cnt[(sa[i] + k >= n ? 0 : ra[sa[i] + k])]++] = sa[i];
		for(int i = 0; i < n; i++)sa[i] = pos[i];
	}
	void create_sa(){
		cnt = (int*)malloc(max(A, n + 5) * sizeof(int));
		pos = (int*)malloc((n + 5) * sizeof(int));
		
		int mx = A;
		
		for(int k = 1; k < n; k <<= 1){
			srt(mx, k);
			srt(mx, 0);
			
			int r = 1;
			pos[sa[0]] = r;
			for(int i = 1; i < n; i++){
				pos[sa[i]] = (ra[sa[i]] == ra[sa[i - 1]] && 
                    (sa[i - 1] + k >= n ? 1 : ra[sa[i - 1] + k] == (sa[i] + k >= n ? 1 : ra[sa[i] + k])) ? r : ++r);
			}
			for(int i = 0; i < n; i++)ra[i] = pos[i];
			
			mx = r + 1;
		}
	}
	
	SA(string &str, char garb = '$', int a = 128){
		sa = ra = cnt = pos = lcp = lg = NULL;
		st = NULL;
		s = str;
		s.push_back(garb);
		n = s.size();
		A = a;
		sa = (int*)malloc(n * sizeof(int));
		ra = (int*)malloc(n * (sizeof(int)));
		for(int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
		create_sa();
	}
	
	//lcp[i] = lcp of sa[i] and sa[i-1]
	void compute_lcp(){
		pos[sa[0]] = -1;
		lcp = (int*)malloc((n + 5) * sizeof(int));
		for(int i = 1; i < s.size(); i++)pos[sa[i]] = sa[i - 1];
		for(int i = 0, l = 0; i < s.size(); i++){
			if(pos[i] == -1){
				//lcp of sa[0] = 0
				ra[i] = 0;
				continue;
			}
			while(s[l + i] == s[pos[i] + l])l++;
			ra[i] = l--;
			if(l < 0)l = 0;
		}
		for(int i = 0; i < s.size(); i++)lcp[i] = ra[sa[i]];
	}
	
	//sparse table for lcp
	//call compute_lcp before it
	void create_sparse(){
		const int K = ceil(log2(n)) + 2;
		st = (int**)malloc(sizeof(int*) * (n + 5));
		lg = (int*)malloc(sizeof(int) * (n + 5));
		for(int i = 0; i < n; i++){
			st[i] = (int*)malloc(K * sizeof(int));
			st[i][0] = lcp[i];
		}
		lg[1] = 0;
		for(int i = 2; i <= n; i++)lg[i] = lg[i >> 1] + 1;
		for(int i = 1; i < K; i++){
			for(int j=0;j+(1<<i)<=n;j++)
				st[j][i] = min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
		}
	}
	
	//lcp of sa[l] and sa[r]
	int query(int l, int r){
		if(l > r)swap(l, r);
		if(l == r)return n - sa[l] - 1;
		l++;
		int x = lg[r - l + 1];
		return min(st[l][x], st[r - (1 << x) + 1][x]);
	}
	~SA(){
		if(sa != NULL)free(sa);
		if(ra != NULL)free(ra);
		if(cnt != NULL)free(cnt);
		if(pos != NULL)free(pos);
		if(lcp != NULL)free(lcp);
		if(lg != NULL)free(lg);
		if(st != NULL){
			for(int i = 0; i < n; i++)free(st[i]);
			free(st);
		}
	}
}; 


//SA using DA
namespace SA{
    const int N = 1e5+5;
    const int log_N = 20;
    const int ALPHA = 155;
    int sa[N], ra[N], rnk[N], hg[N], n;
    int wa[N], wb[N], wws[N], wv[N];
    int lg[N], st[N][log_N];
    int cmp(int *r, int a, int b, int l){
        return (r[a] == r[b]) && (r[a + l] == r[b + l]);
    }
    void DA(int *r, int *sa, int n, int m){
        int i, j, p, *x=wa, *y=wb, *t;
        for(i = 0; i < m; i++) wws[i] = 0;
        for(i = 0; i < n; i++) wws[x[i] = r[i]]++;
        for(i = 1; i < m; i++) wws[i] += wws[i - 1];
        for(i = n - 1; i >= 0; i--) sa[--wws[x[i]]] = i;
        for(j = 1, p = 1; p < n; j <<= 1, m = p) {
            for(p = 0, i = n - j; i < n; i++) y[p++] = i;
            for(i = 0; i < n; i++) if(sa[i] >= j) y[p++] = sa[i] - j;
            for(i = 0; i < n; i++) wv[i] = x[y[i]];
            for(i = 0; i < m; i++) wws[i] = 0;
            for(i = 0; i < n; i++) wws[wv[i]]++;
            for(i = 1; i < m; i++) wws[i] += wws[i - 1];
            for(i = n - 1; i >= 0;i--) sa[--wws[wv[i]]] = y[i];
            for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
                x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
        }
    }
    void init() {
        for(int i = 0; i <= n; i++) st[i][0] = hg[i];
        for(int j = 1; j < log_N; j++) {
            for(int i = 0; i <= n; i++) {
                if (i + (1 << j) - 1 <= n) st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
                else break;
            }
        }
        lg[0] = lg[1] = 0;
        for(int i = 2; i <= n; i++)
            lg[i] = lg[i >> 1] + 1;
    }
    void calheight(int *r, int *sa, int n){
        int i, j, k = 0;
        for(i = 1; i <= n; i++) rnk[sa[i]] = i;
        for(i = 0; i < n; hg[rnk[i++]] = k)
            for(k ? k-- : 0, j = sa[rnk[i] - 1]; r[i + k] == r[j + k]; k++);
    }
    void create_sa(string  &s) {
        n = s.size();
        for(int i = 0; i < max(n + 1, ALPHA); i++) sa[i] = ra[i] = rnk[i] = hg[i] = wa[i] = wb[i] = wws[i] = wv[i] = 0;
        for (int i = 0; i < n; i++) ra[i] = s[i];
        DA(ra, sa, n + 1, ALPHA);
        calheight(ra, sa, n);
        init();
    }
    //1 indexed
    int query(int l, int r) {
        if(l == r) return n - sa[l];
        l++;
        int k = lg[r - l + 1];
        return min(st[l][k], st[r - (1 << k) + 1][k]);
    }
}
