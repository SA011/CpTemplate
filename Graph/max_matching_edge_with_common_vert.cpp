#solution to [this](https://codeforces.com/contest/1519/problem/E) problem

//finds maximum pairing of edge where they have atleast one common vertex

#include <bits/stdc++.h>
using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define INF 2000000000
#define INFL 200000000000000000LL

typedef long long int ll;
typedef pair<ll,ll> ii;
typedef pair<ii,ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;

#define getbit(n,i) (((n)&(1LL<<(i)))!=0)
#define setbit0(n,i) ((n)&(~(1LL<<(i))))
#define setbit1(n,i) ((n)|(1LL<<(i)))
#define lastone(n) ((n)&(-(n)))

#define fi first
#define se second
#define PI (acos(-1))
#define mod (1000000007)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T,class V> ostream& operator<<(ostream &s,pair<T,V> a)
{
    s<<a.fi<<' '<<a.se;
    return s;
}

const int N = 4e5+3, K = 26;

vi adj[N];
int dis[N];
ii edge[N];
int unpaired[N];
vii ans;

void dfs(int ind,int d = 0){
	dis[ind] = d;
	vi bckeg;
	for(auto x:adj[ind]){
		int u = edge[x].fi;
		if(u==ind)u = edge[x].se;
		if(dis[u]==-1){
			dfs(u,d+1);
			if(unpaired[u]){
				ans.push_back(ii(unpaired[u],x+1));
				unpaired[u] = 0;
			}
			else if(unpaired[ind]){
				ans.push_back(ii(unpaired[ind],x+1));
				unpaired[ind] = 0;
			}
			else unpaired[ind] = x+1;
		}
		else if(dis[u]>dis[ind])bckeg.push_back(x);
	}
	
	for(auto x:bckeg){
		int u = edge[x].fi;
		if(u==ind)u = edge[x].se;
		
		if(unpaired[u]){
			ans.push_back(ii(unpaired[u],x+1));
			unpaired[u] = 0;
		}
		else if(unpaired[ind]){
			ans.push_back(ii(unpaired[ind],x+1));
			unpaired[ind] = 0;
		}
		else unpaired[ind] = x+1;
	}
}
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(NULL);
    
    int T=1;
    //scanf("%d",&T);
    
    for(int qq=1; qq<=T; qq++)
    {
		int n;
		scanf("%d",&n);
		memset(dis,-1,sizeof dis);
		vector<ii> all;
		vector<pair<ii,ii>> p(n);
		
		for(auto &x:p){
			ll a,b,c,d;
			scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
			x.fi.fi = b*c+b*d;
			x.fi.se = a*d;
			x.se.fi = b*c;
			x.se.se = a*d+b*d;
			
			ll g = __gcd(x.fi.fi,x.fi.se);
			x.fi.fi/=g;
			x.fi.se/=g;
			
			g = __gcd(x.se.fi,x.se.se);
			x.se.fi/=g;
			x.se.se/=g;
			
			all.push_back(x.fi);
			all.push_back(x.se);
		}
		
		sort(all.begin(),all.end());
		all.resize(unique(all.begin(),all.end())-all.begin());
		
		for(int i=0;i<n;i++){
			int a = lower_bound(all.begin(),all.end(),p[i].fi)-all.begin();
			int b = lower_bound(all.begin(),all.end(),p[i].se)-all.begin();
			assert(a!=b);
			edge[i] = ii(a,b);
			adj[a].push_back(i);
			adj[b].push_back(i);
		}
		
		for(int i=0;i<all.size();i++)if(dis[i]==-1)dfs(i);
		
		printf("%d\n",(int)ans.size());
		for(auto x:ans)printf("%lld %lld\n",x.fi,x.se);
    }
}
