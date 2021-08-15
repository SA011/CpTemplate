
ll height[asz],euler[asz],pos[asz];
ll timer=0;
vector<ll> adj[asz];
void dfs(ll ind,ll depth=0,ll par=-1)
{
    euler[timer]=ind;
    pos[ind]=timer++;
    height[ind]=depth;
    for(ll x:adj[ind])
    {
        if(x!=par)
        {
            dfs(x,depth+1,ind);
            euler[timer++]=ind;
        }
    }
}

ll st[4*asz];
void init(ll node,ll ss, ll sf)
{
    if(ss==sf)
    {
        st[node]=euler[ss];
        return;
    }
    ll mid=(ss+sf)/2;
    init(2*node,ss,mid);
    init(2*node+1,mid,sf);
    if(height[st[2*node]]>height[st[2*node+1]])st[node]=st[2*node+1];
    else st[node]=st[2*node];
}

ll query(ll node,ll ss,ll sf,ll qs,ll qe)
{
    if(ss>sf||qs>sf||qe<ss)return -1;
    if(qs<=ss&&qe>=sf)return st[node];
    ll mid=(ss+sf)/2;
    ll l=query(2*node,ss,mid,qs,qe);
    ll r=query(2*node+1,mid+1,sf,qs,qe);
    if(l==-1)return r;
    if(r==-1)return l;
    if(height[l]>height[r])return r;
    else return l;
}

void lca_init(ll root)
{
    dfs(root);
    init(1,0,timer-1);
}
ll lca_search(ll a,ll b)
{
    if(pos[a]>pos[b])swap(a,b);
    return query(1,0,timer-1,pos[a],pos[b]);
}
