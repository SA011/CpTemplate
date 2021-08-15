
cd st[4*asz];
ll dot(cd a,cd b)
{
    return (conj(a)*b).real();
}
ll f(cd a,ll x)
{
    return dot(a,{x,1});
}
void update(cd x,ll node=1,ll ss=0,ll se=asz-1)
{
    ll mid=(ss+se)/2;
    bool l=f(st[node],ss)>f(x,ss);
    bool m=f(st[node],mid)>f(x,mid);
    if(m)swap(st[node],x);
    if(se-ss<=1)return;
    if(l!=m)update(x,2*node,ss,mid);
    else update(x,2*node+1,mid,se);
}
ll query(ll x,ll node=1,ll ss=0,ll se=asz-1)
{
    if(se-ss<=1)return f(st[node],x);
    ll mid=(ss+se)/2;
    if(x<mid)min(f(st[node],x),query(x,2*node,ss,mid));
    else min(f(st[node],x),query(x,2*node+1,mid,se));
}

