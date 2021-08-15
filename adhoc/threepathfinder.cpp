#include <bits/stdc++.h>
using namespace std;
#define INF 2000000000
typedef long long int ll;
typedef pair<ll,ll> ii;
typedef pair<ii,ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define getbit(n,i) (((n)&(1<<(i)))!=0)
#define setbit0(n,i) ((n)&(~(1<<(i))))
#define setbit1(n,i) ((n)|(1<<(i)))
#define lastone(n) ((n)&(-(n)))
#define read freopen("debug\\in.txt","r",stdin)
#define write freopen("debug\\out.txt","w",stdout)
#define fi first
#define se second
#define PI (acos(-1))
#define M_E (2.718281828459045)
#define fastread ios_base::sync_with_stdio(false);cin.tie(NULL)
#define mod (1000000007)
#define asz 200005
vi adj[asz];
ll dis1[asz],dis2[asz],mxdir[asz],dis3[asz],dis4[asz],scdir[asz],thdir[asz];
ll par[asz];
ll dfs(ll ind,ll dis)
{
    dis1[ind]=dis;
    dis2[ind]=0;
    dis3[ind]=0;
    dis4[ind]=0;
    for(auto x:adj[ind])
    {
        if(x!=par[ind])
        {
            par[x]=ind;
            ll a=dfs(x,dis+1)+1;
            if(a>dis2[ind])thdir[ind]=scdir[ind],scdir[ind]=mxdir[ind],dis4[ind]=dis3[ind],dis3[ind]=dis2[ind],dis2[ind]=a,mxdir[ind]=x;
            else if(a>dis3[ind])thdir[ind]=scdir[ind],scdir[ind]=x,dis4[ind]=dis3[ind],dis3[ind]=a;
            else if(a>dis4[ind])thdir[ind]=x,dis4[ind]=a;
        }
    }
    return dis2[ind];
}
ll ans[asz],mxg[asz];
ll scnd[asz],thrd[asz],tdir[asz],sdir[asz];
ii solve(ll ind)
{
    if(par[ind]==-1)sdir[ind]=scdir[ind],tdir[ind]=thdir[ind],mxg[ind]=mxdir[ind],ans[ind]=dis2[ind],scnd[ind]=dis3[ind],thrd[ind]=dis4[ind];
    if(ans[ind]!=-1)return ii(ans[ind],mxg[ind]);
    ii a=solve(par[ind]);
    if(a.se!=ind)
    {
        mxg[ind]=par[ind];
        ans[ind]=a.fi+1;
        scnd[ind]=dis2[ind];
        thrd[ind]=dis3[ind];
        sdir[ind]=mxdir[ind];
        tdir[ind]=scdir[ind];
        return ii(ans[ind],mxg[ind]);
    }
    ans[ind]=1+scnd[par[ind]];
    if(ans[ind]>dis2[ind])thrd[ind]=dis3[ind],scnd[ind]=dis2[ind],mxg[ind]=par[ind],sdir[ind]=mxdir[ind],tdir[ind]=scdir[ind];
    else if(ans[ind]>dis3[ind])scnd[ind]=ans[ind],thrd[ind]=dis3[ind],ans[ind]=dis2[ind],mxg[ind]=mxdir[ind],sdir[ind]=par[ind],tdir[ind]=scdir[ind];
    else
    {
        if(ans[ind]>=dis4[ind])tdir[ind]=par[ind];
        else tdir[ind]=thdir[ind];
        scnd[ind]=dis3[ind],thrd[ind]=max(dis4[ind],ans[ind]),ans[ind]=dis2[ind],mxg[ind]=mxdir[ind],sdir[ind]=scdir[ind];
    }
    return ii(ans[ind],mxg[ind]);
}
void dfs3(ll ind,vi &e,vi &u,ll pos=-1,ll p=-1,ll r=0)
{
    if(pos==-1)
    {
        if(tdir[ind]==-1)e[2]=ind;
        else dfs3(tdir[ind],e,u,2,ind,1);
        if(sdir[ind]==-1)e[1]=adj[ind][0];
        else dfs3(sdir[ind],e,u,1,ind,1);
        dfs3(mxg[ind],e,u,0,ind,1);
        return;
    }
    if(u[pos]<r)e[pos]=ind,u[pos]=r;
    for(auto x:adj[ind])
    {
        if(x!=p)
        {
            dfs3(x,e,u,pos,ind,r+1);
        }
    }
}
int main()
{
    fastread;
    ll T=1;
//    cin>>T;
    for(ll qq=1;qq<=T;qq++)
    {
        ll n;
        cin>>n;
        memset(par,-1,sizeof par);
        memset(ans,-1,sizeof ans);
        memset(mxdir,-1,sizeof mxdir);
        memset(scdir,-1,sizeof scdir);
        memset(thdir,-1,sizeof thdir);
        memset(mxg,-1,sizeof mxg);
        memset(sdir,-1,sizeof sdir);
        memset(tdir,-1,sizeof tdir);
        for(int i=0;i<n-1;i++)
        {
            ll x,y;
            cin>>x>>y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        dfs(1,0);
        for(int i=1;i<=n;i++)solve(i);
        ll p=1;
        for(int i=1;i<=n;i++)
        {
            if(ans[i]+scnd[i]+thrd[i]>=ans[p]+scnd[p]+thrd[p])p=i;
        }
        vi u(3);
        vi e(3);
        dfs3(p,e,u);
        cout<<thrd[p]+ans[p]+scnd[p]<<endl;
        cout<<e[0]<<' '<<e[1]<<' '<<e[2]<<endl;
    }
    return 0;
}
