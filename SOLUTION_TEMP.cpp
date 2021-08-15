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
#define getbit(n,i) (((n)&(1LL<<(i)))!=0)
#define lastone(n) ((n)&(-(n)))
#define eb emplace_back
#define mk make_pair
#define fi first
#define se second

const ll INFL = 2e18;
const int INF = 1e9;
const double PI = acos(-1);
const ll mod = 1e9+7;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T,class V> 
ostream& operator<<(ostream &s,pair<T,V> a){
    s << a.fi << ' ' << a.se;
    return s;
}

const int N = 1e6+3, K = 26;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T=1;
    //cin>>T;
    
    for(int qq=1; qq<=T; qq++)
    {
        
    }
}
