struct vertex{
	int link, len;
	int next[26];
	vertex(){
		link = -1;
		len = 0;
		memset(next, -1, sizeof next);
	}
};

vertex sa[N << 1];
int last = 0, sz = 1;
void addChar(char c){
	c -= 'a';
	int cur = sz++;
	sa[cur].len = sa[last].len + 1;
	int u = last;
	while(u != -1 && sa[u].next[c] == -1) 
        sa[u].next[c] = cur, u = sa[u].link;
	if(u == -1)
		sa[cur].link = 0;
	else{
		int v = sa[u].next[c];
		if(sa[u].len + 1 == sa[v].len)
			sa[cur].link = v;
		else{
			int nw = sz++;
			sa[nw].link = sa[v].link;
			sa[nw].len = sa[u].len + 1;
			memcpy(sa[nw].next, sa[v].next, sizeof sa[v].next);
			while(u != -1 && sa[u].next[c] == v)
				sa[u].next[c] = nw, u = sa[u].link;
			sa[cur].link = sa[v].link = nw;
		}
	}
	last = cur;
}


//cnt is the number of instances of an equivalence class 
//init cnt with 1 except for clones and starting node
//d is the number of instances of an equivalence class being a prefix 
//to count distinct replace cnt with 1
void pre(){
    vector<vector<int>> v(sz + 1);
    for(int i = 0; i < sz; i++)v[sa[i].len].push_back(i);
    for(int i = sz; i >= 0; i--)
        for(auto x : v[i])
        if(x)sa[sa[x].link].cnt += sa[x].cnt;
    sa[0].cnt=0; //ignoring empty substring
    
    for(int i = sz; i >= 0; i--){
        for(auto x : v[i]){
            sa[x].d = sa[x].cnt;
            for(int j = 0; j < 26; j++)
                if(sa[x].next[j] != -1)sa[x].d += sa[sa[x].next[j]].d;
        }
    }
}






















///////LCS with Automata
#include <bits/stdc++.h>
using namespace std;

using ll = long long int;
using ull = unsigned long long int;
using vi = vector<ll>;
using ii = pair<ll,ll>;
using iii = pair<ii,ll>;
using vii = vector<ii>;
using ld = long double;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef
tree < ll, null_type, less<ll>,
rb_tree_tag,
tree_order_statistics_node_update > ordered_set;

template <class T>
void print(T a) {cerr << a << endl;}
template <class T, class... V> 
void print(T a, V... b) {cerr << a << ", "; print(b...);}
#define dbg(...) cerr << "[" << __LINE__ << "] " << #__VA_ARGS__ << " :: ", print(__VA_ARGS__)
#define getbit(n, i) (((n) >> (i)) & 1)
#define lastone(n) ((n) & (-(n)))
#define eb emplace_back
#define mk make_pair
#define fi first
#define se second

const ll INFL = 2e18;
const int INF = 1e9;
const double PI = acos(-1);
const ll mod = 1e9+7;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T, class V> 
ostream& operator << (ostream &s, pair<T, V> a){
    s << a.fi << ' ' << a.se;
    return s;
}

//const int N = 1e6+3, K = 26;

namespace Automata {
const int N = 1e6+7, K = 26;
int tot;
int len[2*N], link[2*N], sz, last;
int prv;
vector<int> nxt [2 * N];
vector<int> reach[2 * N];
void init(int n, int k) {
  for (int i=0; i<=2*n; i++)
    nxt[i].assign(K + k, -1);
  len[0] = 0; link[0] = -1; sz = 1; last = 0;
  reach[0].assign(tot = k, 0);
}
void add(char ch) {
  int c = ch-'a', cur = sz++; //create new node
  if(c >= 26)prv = c - 26;
  len[cur] = len[last]+1;
  reach[cur].assign(tot, 0);
  reach[cur][prv] = 1;
  int u = last;
  while (u != -1 && nxt[u][c] == -1) {
    nxt[u][c] = cur; u = link[u]; }

  if (u == -1) { link[cur] = 0; }
  else {
    int v = nxt[u][c];
    if (len[v] == len[u]+1) { link[cur] = v; }
    else {
      int clone = sz++;  //create node by cloning
      len[clone] = 1+len[u]; link[clone]=link[v];
      reach[clone] = reach[v];
      for (int i=0; i<K; i++)
        nxt[clone][i] = nxt[v][i];
      while (u != -1 && nxt[u][c] == v) {
        nxt[u][c] = clone; u = link[u];
      }
      link[v] = link[cur] = clone;
    }
  } last = cur;
}
vector<int> edge[2*N];
void makeEdge() { ///Make Suffix Link Tree edges
  for (int i=0; i<sz; i++) {
    edge[i].clear();
    for (int j=0; j<K + tot; j++)
      if (nxt[i][j]!=-1)    edge[i].push_back(j);
  }
  
} 

void pre(){
    makeEdge();
    
    vector<vector<int>> l(sz);
    for(int i = 0; i < sz; i++)l[len[i]].push_back(i);
    
    for(int i = sz - 1; i >= 0; i--){
        for(auto x : l[i]){
            if(link[x] == -1)continue;
            for(int j = 0; j < tot; j++)reach[link[x]][j] |= reach[x][j];
            
        }
        
    }
}

}

using namespace Automata;
string ans;
string cur;
void dfs(int ind){
    if(accumulate(reach[ind].begin(), reach[ind].end(), 0) == tot){
        if(cur.size() > ans.size())ans = cur;
    }
    for(auto x : edge[ind]){
        cur.push_back((char)(x + 'a'));
        dfs(nxt[ind][x]);
        cur.pop_back();
    }
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T = 1;
    //cin >> T;
    
    for(int qq = 1; qq <= T; qq++){
        int n;
        cin >> n;
        init(N, n);
        
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            add(i + 26 + 'a');
            for(auto x : s)add(x);
        }
        
        pre();
        
        dfs(0);
        
        cout << ans << "\n";
        
        
        
        
    }
}
