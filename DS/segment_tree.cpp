// SEGMENT TREE
ll st[4*N];
ll ara[N];
ll f(ll l,ll r){
    return l + r;
}
void init(int node, int ss, int sf){
    if(ss == sf){
        st[node] = ara[ss];
        return;
    }
    int mid = (ss + sf) >> 1;
    init(node << 1, ss, mid);
    init(node << 1 | 1, mid + 1, sf);
    st[node] = f(st[node << 1], st[node << 1 | 1]);
}
//adds value
void update(int node, int ss, int sf, int pos, ll val){
    if(ss == sf){
        st[node] += val;
        return;
    }
    int mid = (ss + sf) >> 1;
    if(pos <= mid) update(node << 1, ss, mid, pos, val);
    else update(node << 1 | 1, mid + 1, sf, pos, val);
    st[node] = f(st[node << 1], st[node << 1 | 1]);
}
ll query(int node, int ss, int sf, int qs, int qe){
    if(qs > sf || qe < ss || qe < qs)return 0;
    if(qs <= ss && qe >= sf)return st[node];
    int mid = (ss + sf) >> 1;
    return f(query(node << 1, ss, mid, qs, qe), query(node << 1 | 1, mid + 1, sf, qs, qe));
}

//Modified update for ordered multiset
int update(ll node,ll ss,ll sf,ll pos,int val)    //returns i(pos)-th smallest element if val==0. if val>0, then adds pos val times. 
{                                                 //Otherwise deletes i(pos)-th smallest element val times.
    if(ss==sf)                                    //to find number of smaller element than x, use query(0,x-1)
    {
        st[node]+=val;
        if(st[node]<0)st[node]=0;
        return ss;
    }
    ll mid=(ss+sf)/2;
    int x=pos;
    if(val>0){
        if(pos<=mid)update(2*node,ss,mid,pos,val);
        else update(2*node+1,mid+1,sf,pos,val);
    }
    else{
        if(st[2*node]>=pos)x=update(2*node,ss,mid,pos,val);
        else x=update(2*node+1,mid+1,sf,pos-st[2*node],val);
    }
    st[node]=f(st[2*node],st[2*node+1]);
    return x;
}


//Iterative

ll st[4*asz];
void update(int k,int val,int n)
{
    k+=n;
    st[k] = val;
    while(k>1){
        st[k>>1] = max(st[k],st[k^1]);
        k>>=1;
    }
}
ll query(int l,int r,int n)
{
    l+=n,r+=n;
    r++;
    ll ans = 0;
    while(l<r){
        if(l&1)ans = max(ans,st[l++]);
        if(r&1)ans = max(ans,st[--r]);
        l>>=1;
        r>>=1;
    }
    return ans;
}
