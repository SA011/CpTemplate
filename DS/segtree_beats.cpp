
//may need some edit
struct vert
{
    int mx2=0;
    int mx=0;
    int num=0;
    ll sum=0;
};
vert st[4*asz];
ll ara[asz];
ll lz[4*asz];
void propagate(int node)
{
    if(lz[node]==-1)return;
    if(st[node].mx>lz[node])
    {
        lz[2*node]=(lz[node]<lz[2*node]||lz[2*node]==-1?lz[node]:lz[2*node]);
        lz[2*node+1]=(lz[node]<lz[2*node+1]||lz[2*node+1]==-1?lz[node]:lz[2*node+1]);
        st[node].sum-=st[node].num*(st[node].mx-lz[node]);
        st[node].mx=lz[node];
    }
    lz[node]=-1;
}
void f(vert &a,vert &b,vert &c)
{
    a.mx=max(b.mx,c.mx);
    if(a.mx!=c.mx)a.mx2=max(c.mx,b.mx2),a.num=b.num;
    else if(a.mx!=b.mx)a.mx2=max(c.mx2,b.mx),a.num=c.num;
    else a.mx2=max(b.mx2,c.mx2),a.num=b.num+c.num;
    a.sum=b.sum+c.sum;
}
void init(ll node,ll ss,ll sf)
{
    lz[node]=-1;
    if(ss==sf)
    {
        st[node].mx=ara[ss];
        st[node].sum=ara[ss];
        st[node].mx2=-1;
        st[node].num=1;
        return;
    }
    ll mid=(ss+sf)/2;
    init(2*node,ss,mid);
    init(2*node+1,mid+1,sf);
    f(st[node],st[node*2],st[node*2+1]);
}
void update(ll node,ll ss,ll sf,ll qs,ll qe,ll t)
{
    propagate(node);
    if(st[node].mx<=t)return;
    if(qs>sf||qe<ss||qs>qe)return;
    if(qs<=ss&&qe>=sf&&st[node].mx2<t)
    {
        lz[node]=t;
        propagate(node);
        return;
    }
    int mid=(ss+sf)/2;
    update(2*node,ss,mid,qs,qe,t);
    update(2*node+1,mid+1,sf,qs,qe,t);
    f(st[node],st[node*2],st[node*2+1]);
}
ii query(ll node,ll ss,ll sf,ll qs,ll qe)
{
    ll mid=(ss+sf)/2;
    propagate(node);
    if(qs>sf||qe<ss||qs>qe)return ii(0,0);
    if(qs<=ss&&qe>=sf)return ii(st[node].sum,st[node].mx);
    ii a=query(2*node,ss,mid,qs,qe);
    ii b=query(2*node+1,mid+1,sf,qs,qe);
    return ii(a.fi+b.fi,max(a.se,b.se));
}
