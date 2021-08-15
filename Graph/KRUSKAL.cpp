
class Unionfind
{
public:
    vi p,rnk;
    Unionfind(int N){p.assign(N,0);rnk.assign(N,1);for(int i=0;i<N;i++)p[i]=i;}
    int findset(int i){return (p[i]==i)?i:findset(p[i]);}
    bool sameset(int i,int j){return findset(i)==findset(j);}
    void unionset(int i,int j)
    {
        int x=findset(i),y=findset(j);
        if(x!=y)
        {
            if(rnk[x]>rnk[y])p[y]=x,rnk[x]+=rnk[y],rnk[y]=0;
            else {p[x]=y;rnk[y]+=rnk[x],rnk[x]=0;}
        }
    }
};


vii adj[asz];
ll KRUSKAL(vector<iii> &EDGELIST,int n)
{
    ll ans=0;
    Unionfind un(n);
    sort(EDGELIST.begin(),EDGELIST.end());
    for(auto x:EDGELIST)
    {
        if(!un.sameset(x.fi.se,x.se))
        {
            un.unionset(x.fi.se,x.se);
            ans+=x.fi.fi;
            adj[x.fi.se].push_back(ii(x.se,x.fi.fi));
            adj[x.se].push_back(ii(x.fi.se,x.fi.fi));
        }
    }
    return ans;
}
