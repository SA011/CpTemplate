mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
unordered_map<ll,ll> ump;
ll getrn()
{
    ll x;
    while(ump[x=rng()]==1);
    ump[x]=1;
    return x;
}
struct vert
{
    ll sum,val,pref,suf,mxs,mx;
    vert (ll _v=0):val(_v){
        sum=_v;
        pref=_v;
        suf=pref;
        mxs=pref;
        mx=_v;
    }
    void reset()
    {
        sum=val;
        pref=val;
        suf=pref;
        mxs=pref;
        mx=val;
    }
    void comb(vert l,vert r)
    {
        sum=l.sum+r.sum;
        mx=max(l.mx,r.mx);
        pref=max(l.pref,l.sum+r.pref);
        suf=max(r.suf,r.sum+l.suf);
        mxs=max(max(l.mxs,r.mxs),l.suf+r.pref);
    }
};
class item
{
public:
    ll sz,prior;
    vert val;
    item *l,*r;
    item(vert t=vert(),ll c=1,ll _p=getrn(),item* _l=NULL,item* _r=NULL):val(t),sz(c),prior(_p),l(_l),r(_r){}
};
typedef item* pitem;
class Treap
{
public:
    pitem root;
    Treap():root(NULL){}
    ll get_sz(pitem t)
    {
        if(t)return t->sz;
        return 0;
    }
    void upd_sz(pitem t)
    {
        if(t)t->sz=get_sz(t->l)+get_sz(t->r)+1;
    }
    void reset(pitem t)
    {
        if(t)t->val.reset();
    }
    void combine(pitem &t,pitem l,pitem r)
    {
        if(!l||!r)t=(l?l:r);
        else t->val.comb(l->val,r->val);
    }
    void proc(pitem t)
    {
        if(!t)return;
        reset(t);
        combine(t,t->l,t);
        combine(t,t,t->r);
    }
    void split(pitem t,pitem &l,pitem &r,int key,int add=0)
    {
        if(!t)return void(l=r=NULL);
        int cur_pos=add+get_sz(t->l);
        if(key<=cur_pos)split(t->l,l,t->l,key,add),r=t;
        else split(t->r,t->r,r,key,cur_pos+1),l=t;
        upd_sz(t);
        proc(t);
    }
    void merge(pitem &t,pitem l,pitem r)
    {
        if(!l||!r)return void(t=(l?l:r));
        if(l->prior<r->prior)merge(r->l,l,r->l),t=r;
        else merge(l->r,l->r,r),t=l;
        upd_sz(t);
        proc(t);
    }
    void insert(vert v,int pos)
    {
        if(!root)return void(root=new item(v));
        pitem l,r;
        l=r=NULL;
        split(root,l,r,pos-1);
        //proc(l);
        //proc(r);
        merge(l,l,new item(v));
        merge(root,l,r);
    }
    void erase(int pos,pitem &t,int add=0)
    {
        if(!t)return;
        if(get_sz(t->l)+add+1==pos)merge(t,t->l,t->r),proc(t);
        else if(get_sz(t->l)+add>=pos)erase(pos,t->l,add);
        else erase(pos,t->r,add+get_sz(t->l)+1);
    }
    void erase(int pos){
        if(!root)return;
        pitem l=NULL,r=NULL;
        split(root,l,r,pos);
        //proc(l);
        //proc(r);
        pitem w=NULL;
        split(l,l,w,pos-1);
        //proc(l);
        delete w;
        merge(root,l,r);
        proc(root);
    }
    void replace(int pos,vert v)
    {
        if(!root)return;
        pitem l=NULL,r=NULL;
        split(root,l,r,pos);
        //proc(l);
        //proc(r);
        pitem w=NULL;
        split(l,l,w,pos-1);
        //proc(l);
        w->val=v;
        //proc(w);
        merge(l,l,w);
        //proc(l);
        merge(root,l,r);
        //proc(root);
    }
    vert find(int pos,pitem t,int add=0)
    {
        if(get_sz(t->l)+add+1==pos)return t->val;
        else if(get_sz(t->l)+add>=pos)return find(pos,t->l,add);
        else return find(pos,t->r,add+get_sz(t->l)+1);
    }
    vert find(int pos){return find(pos,root);}
    vert query(int l,int r,pitem t)
    {
        pitem L=NULL,mid=NULL,R=NULL;
        split(t,L,mid,l-1);
       // proc(L);
       // proc(mid);
        split(mid,t,R,r-l+1);
       // proc(t);
        //proc(R);
//        if(t==NULL)return vert();
        vert ans=t->val;
        merge(mid,L,t);
       // proc(mid);
        merge(t,mid,R);
       // proc(t);
        return ans;
    }
    vert query(int l,int r){return query(l,r,root);}
    void clear(pitem t){
        if(t == NULL)return;
        clear(t->l);
        clear(t->r);
        delete t;
    }
    ~Treap(){
        clear(root);
    }
};







//MAY B IT"S BETTER

//Indexed from 1
int ara[N];
unordered_map<ll,ll> ump;
ll getrn()
{
    ll x;
    while(ump[x=rng()]==1);
    ump[x]=1;
    return x;
}
struct vert
{
    ll sum = 0,val = 0;
    vert (ll _v=0){
        val = sum = _v;
    }
    void reset()
    {
        sum = val;
    }
    void comb(vert l,vert r)
    {
        sum = l.sum+r.sum;
    }
};
class item
{
public:
    ll sz,prior;
    vert val;
    item *l,*r;
    item(vert t=vert(),ll c=1,ll _p=getrn(),item* _l=NULL,item* _r=NULL):val(t),sz(c),prior(_p),l(_l),r(_r){}
};
typedef item* pitem;
class Treap
{
public:
    pitem root;
    Treap():root(NULL){}
    ll get_sz(pitem t)
    {
        if(t)return t->sz;
        return 0;
    }
    void upd_sz(pitem t)
    {
        if(t)t->sz=get_sz(t->l)+get_sz(t->r)+1;
    }
    void reset(pitem t)
    {
        if(t)t->val.reset();
    }
    void combine(pitem &t,pitem l,pitem r)
    {
        if(!l||!r)t=(l?l:r);
        else t->val.comb(l->val,r->val);
    }
    void proc(pitem t)
    {
        if(!t)return;
        reset(t);
        combine(t,t->l,t);
        combine(t,t,t->r);
    }
    void split(pitem t,pitem &l,pitem &r,int key,int add=0)
    {
        if(!t)return void(l=r=NULL);
        int cur_pos=add+get_sz(t->l);
        if(key<=cur_pos)split(t->l,l,t->l,key,add),r=t;
        else split(t->r,t->r,r,key,cur_pos+1),l=t;
        upd_sz(t);
        proc(t);
    }
    void merge(pitem &t,pitem l,pitem r)
    {
        if(!l||!r)return void(t=(l?l:r));
        if(l->prior<r->prior)merge(r->l,l,r->l),t=r;
        else merge(l->r,l->r,r),t=l;
        upd_sz(t);
        proc(t);
    }
    void build(int ss,int sf,pitem &t)
    {
        if(ss>sf)return;
        if(ss==sf)return void(t=new item(vert(ara[ss])));
        int mid=(ss+sf)/2;
        t=new item(vert(ara[mid]));
        pitem a=NULL,b=NULL;
        build(ss,mid-1,a);
        build(mid+1,sf,b);
        merge(a,a,t);
        merge(t,a,b);
    }
    void build(int ss,int sf){build(ss,sf,root);}
    void insert(vert v,int pos)
    {
        if(!root)return void(root=new item(v));
        pitem l,r;
        l=r=NULL;
        split(root,l,r,pos-1);
        merge(l,l,new item(v));
        merge(root,l,r);
    }
    void erase(int pos,pitem &t,int add=0)
    {
        if(!t)return;
        if(get_sz(t->l)+add+1==pos)merge(t,t->l,t->r),proc(t);
        else if(get_sz(t->l)+add>=pos)erase(pos,t->l,add);
        else erase(pos,t->r,add+get_sz(t->l)+1);
    }
    void erase(int pos){
        if(!root)return;
        pitem l=NULL,r=NULL;
        split(root,l,r,pos);
        pitem w=NULL;
        split(l,l,w,pos-1);
        delete w;
        merge(root,l,r);
    }
    void replace(int pos,vert v)
    {
        if(!root)return;
        pitem l=NULL,r=NULL;
        split(root,l,r,pos);
        pitem w=NULL;
        split(l,l,w,pos-1);
        w->val=v;
        merge(l,l,w);
        merge(root,l,r);
    }
    vert find(int pos,pitem t,int add=0)
    {
        if(get_sz(t->l)+add+1==pos)return t->val;
        else if(get_sz(t->l)+add>=pos)return find(pos,t->l,add);
        else return find(pos,t->r,add+get_sz(t->l)+1);
    }
    vert find(int pos){return find(pos,root);}
    vert query(int l,int r,pitem t)
    {
        pitem L=NULL,mid=NULL,R=NULL;
        split(t,L,mid,l-1);
        split(mid,t,R,r-l+1);
        vert ans=t->val;
        merge(mid,L,t);
        merge(t,mid,R);
        return ans;
    }
    vert query(int l,int r){return query(l,r,root);}
    size_t size(){
        return get_sz(root);
    }
    void clear(pitem t){
        if(t == NULL)return;
        clear(t->l);
        clear(t->r);
        delete t;
    }
    ~Treap(){
        clear(root);
    }
};

//updated with simple lazy subarray reversal update
int ara[N];
unordered_map<ll,ll> ump;
ll getrn()
{
    ll x;
    while(ump[x=rng()]==1);
    ump[x]=1;
    return x;
}
struct vert
{
    ll sum = 0,val = 0;
    vert (ll _v=0){
        val = sum = _v;
    }
    void reset()
    {
        sum = val;
    }
    void comb(vert l,vert r)
    {
        sum = l.sum+r.sum;
    }
};
class item
{
public:
    ll sz,prior;
    vert val;
    int lz;
    item *l,*r;
    item(vert t=vert(),ll c=1,ll _p=getrn(),item* _l=NULL,item* _r=NULL):val(t),sz(c),prior(_p),l(_l),r(_r),lz(0){}
};
typedef item* pitem;
class Treap
{
public:
    pitem root;
    Treap():root(NULL){}
    ll get_sz(pitem t)
    {
        if(t)return t->sz;
        return 0;
    }
    void upd_sz(pitem t)
    {
        if(t)t->sz=get_sz(t->l)+get_sz(t->r)+1;
    }
    void reset(pitem t)
    {
        if(t)t->val.reset();
    }
    void combine(pitem &t,pitem l,pitem r)
    {
        if(!l||!r)t=(l?l:r);
        else t->val.comb(l->val,r->val);
    }
    void proc(pitem t)
    {
        if(!t)return;
        reset(t);
        combine(t,t->l,t);
        combine(t,t,t->r);
    }
    void prop(pitem t){
		if(!t || t -> lz == 0)return;
		t -> lz = 0;
		swap(t->r,t->l);
		if(t->r)t -> r -> lz ^=1;
		if(t->l)t -> l -> lz ^=1;
	}
    void split(pitem t,pitem &l,pitem &r,int key,int add=0)
    {
		prop(t);
        if(!t)return void(l=r=NULL);
        int cur_pos=add+get_sz(t->l);
        if(key<=cur_pos)split(t->l,l,t->l,key,add),r=t;
        else split(t->r,t->r,r,key,cur_pos+1),l=t;
        upd_sz(t);
        proc(t);
    }
    void merge(pitem &t,pitem l,pitem r)
    {
		prop(l),prop(r);
        if(!l||!r)return void(t=(l?l:r));
        if(l->prior<r->prior)merge(r->l,l,r->l),t=r;
        else merge(l->r,l->r,r),t=l;
        upd_sz(t);
        proc(t);
    }
    void build(int ss,int sf,pitem &t)
    {
        if(ss>sf)return;
        if(ss==sf)return void(t=new item(vert(ara[ss])));
        int mid=(ss+sf)/2;
        t=new item(vert(ara[mid]));
        pitem a=NULL,b=NULL;
        build(ss,mid-1,a);
        build(mid+1,sf,b);
        merge(a,a,t);
        merge(t,a,b);
    }
    void build(int ss,int sf){build(ss,sf,root);}
    void insert(vert v,int pos)
    {
        if(!root)return void(root=new item(v));
        pitem l,r;
        l=r=NULL;
        split(root,l,r,pos-1);
        merge(l,l,new item(v));
        merge(root,l,r);
    }
    void erase(int pos,pitem &t,int add=0)
    {
        if(!t)return;
        if(get_sz(t->l)+add+1==pos)merge(t,t->l,t->r),proc(t);
        else if(get_sz(t->l)+add>=pos)erase(pos,t->l,add);
        else erase(pos,t->r,add+get_sz(t->l)+1);
    }
    void erase(int pos){
        if(!root)return;
        pitem l=NULL,r=NULL;
        split(root,l,r,pos);
        pitem w=NULL;
        split(l,l,w,pos-1);
        delete w;
        merge(root,l,r);
    }
    void replace(int pos,vert v)
    {
        if(!root)return;
        pitem l=NULL,r=NULL;
        split(root,l,r,pos);
        pitem w=NULL;
        split(l,l,w,pos-1);
        w->val=v;
        merge(l,l,w);
        merge(root,l,r);
    }
    vert find(int pos,pitem t,int add=0)
    {
        if(get_sz(t->l)+add+1==pos)return t->val;
        else if(get_sz(t->l)+add>=pos)return find(pos,t->l,add);
        else return find(pos,t->r,add+get_sz(t->l)+1);
    }
    vert find(int pos){return find(pos,root);}
    void update(int l,int r, pitem t){
		pitem L=NULL,mid=NULL,R=NULL;
        split(t,L,mid,l-1);
        split(mid,t,R,r-l+1);
        t -> lz ^= 1;
        merge(mid,L,t);
        merge(t,mid,R);
	}
    void update(int l,int r){
		update(l,r,root);
	}
    vert query(int l,int r,pitem t)
    {
        pitem L=NULL,mid=NULL,R=NULL;
        split(t,L,mid,l-1);
        split(mid,t,R,r-l+1);
        vert ans=t->val;
        merge(mid,L,t);
        merge(t,mid,R);
        return ans;
    }
    vert query(int l,int r){return query(l,r,root);}
    size_t size(){
        return get_sz(root);
    }
    void clear(pitem t){
        if(t == NULL)return;
        clear(t->l);
        clear(t->r);
        delete t;
    }
    ~Treap(){
        clear(root);
    }
};







//Particular problem
unsigned int ara[asz];
unsigned int C[20][20];
unsigned int pwr[asz][20];
struct vert
{
    unsigned int ans[11],val[11];
    vert (ll _v=0){
        for(int i=0;i<=10;i++)ans[i]=val[i]=_v;
    }
    void reset()
    {
        for(int i=0;i<=10;i++)ans[i]=val[i];
    }
    void comb(vert l,vert r,int g)
    {
        for(int i=0;i<=10;i++)
        {
            ans[i]=l.ans[i];
            for(int j=0;j<=i;j++)
            {
                ans[i]+=r.ans[i-j]*C[i][j]*pwr[g][j];
            }
        }
    }
};
class item
{
public:
    ll sz,prior;
    vert val;
    item *l,*r;
    item(vert t=vert(),ll c=1,ll _p=getrn(),item* _l=NULL,item* _r=NULL):val(t),sz(c),prior(_p),l(_l),r(_r){}
};
typedef item* pitem;
class Treap
{
public:
    pitem root;
    Treap():root(NULL){}
    ll get_sz(pitem t)
    {
        if(t)return t->sz;
        return 0;
    }
    void upd_sz(pitem t)
    {
        if(t)t->sz=get_sz(t->l)+get_sz(t->r)+1;
    }
    void reset(pitem t)
    {
        if(t)t->val.reset();
    }
    void combine(pitem &t,pitem l,pitem r,ll g)
    {
        if(!l||!r)t=(l?l:r);
        else t->val.comb(l->val,r->val,g);
    }
    void proc(pitem t)
    {
        if(!t)return;
        reset(t);
        combine(t,t->l,t,get_sz(t->l));
        combine(t,t,t->r,get_sz(t->l)+1);
    }
    void split(pitem t,pitem &l,pitem &r,int key,int add=0)
    {
        if(!t)return void(l=r=NULL);
        int cur_pos=add+get_sz(t->l);
        if(key<=cur_pos)split(t->l,l,t->l,key,add),r=t;
        else split(t->r,t->r,r,key,cur_pos+1),l=t;
        upd_sz(t);
        proc(t);
    }
    void merge(pitem &t,pitem l,pitem r)
    {
        if(!l||!r)return void(t=(l?l:r));
        if(l->prior<r->prior)merge(r->l,l,r->l),t=r;
        else merge(l->r,l->r,r),t=l;
        upd_sz(t);
        proc(t);
    }
    void build(int ss,int sf,pitem &t)
    {
        if(ss>sf)return;
        if(ss==sf)return void(t=new item(vert(ara[ss])));
        int mid=(ss+sf)/2;
        t=new item(vert(ara[mid]));
        pitem a=NULL,b=NULL;
        build(ss,mid-1,a);
        build(mid+1,sf,b);
        merge(a,a,t);
        merge(t,a,b);
    }
    void build(int ss,int sf){build(ss,sf,root);}
    void insert(vert v,int pos)
    {
        if(!root)return void(root=new item(v));
        pitem l,r;
        l=r=NULL;
        split(root,l,r,pos-1);
        merge(l,l,new item(v));
        merge(root,l,r);
    }
    void erase(int pos,pitem &t,int add=0)
    {
        if(!t)return;
        if(get_sz(t->l)+add+1==pos)merge(t,t->l,t->r),proc(t);
        else if(get_sz(t->l)+add>=pos)erase(pos,t->l,add);
        else erase(pos,t->r,add+get_sz(t->l)+1);
    }
    void erase(int pos){
        if(!root)return;
        pitem l=NULL,r=NULL;
        split(root,l,r,pos);
        pitem w=NULL;
        split(l,l,w,pos-1);
        delete w;
        merge(root,l,r);
    }
    void replace(int pos,vert v)
    {
        if(!root)return;
        pitem l=NULL,r=NULL;
        split(root,l,r,pos);
        pitem w=NULL;
        split(l,l,w,pos-1);
        w->val=v;
        merge(l,l,w);
        merge(root,l,r);
    }
    vert find(int pos,pitem t,int add=0)
    {
        if(get_sz(t->l)+add+1==pos)return t->val;
        else if(get_sz(t->l)+add>=pos)return find(pos,t->l,add);
        else return find(pos,t->r,add+get_sz(t->l)+1);
    }
    vert find(int pos){return find(pos,root);}
    vert query(int l,int r,pitem t)
    {
        pitem L=NULL,mid=NULL,R=NULL;
        split(t,L,mid,l-1);
        split(mid,t,R,r-l+1);
        vert ans=t->val;
        merge(mid,L,t);
        merge(t,mid,R);
        return ans;
    }
    vert query(int l,int r){return query(l,r,root);}
    void clear(pitem t){
        if(t == NULL)return;
        clear(t->l);
        clear(t->r);
        delete t;
    }
    ~Treap(){
        clear(root);
    }
};
