int ara[N];
unordered_set<int> taken;
int getrn(){
    //int x;
    //while(taken.count(x = rng()));
    //taken.insert(x);
    //return x;
    return rng();
}

struct vert{
    ll sum = 0, val = 0;
    vert (ll _v = 0){
        val = sum = _v;
    }
    void reset(){
        sum = val;
    }
    void comb(vert l, vert r){
        sum = l.sum + r.sum;
    }
};
class item{
public:
    int sz, prior;
    vert val;
    int lz;
    item *l,*r;
    item(vert t = vert(), int c = 1, int _p = getrn(), item* _l = NULL, item* _r = NULL):
        val(t), sz(c), prior(_p), l(_l), r(_r), lz(0) {}
};
typedef item* pitem;
class Treap{
public:
    pitem root;
    Treap() : root(NULL) {}
    
    int get_sz(pitem t){
        if(t)return t -> sz;
        return 0;
    }
    void upd_sz(pitem t){
        if(t)
            t -> sz = get_sz(t -> l) + get_sz(t -> r) + 1;
    }
    void reset(pitem t){
        if(t)t -> val.reset();
    }
    void combine(pitem &t, pitem l, pitem r){
        if(!l || !r)t = (l ? l : r);
        else t -> val.comb(l -> val, r -> val);
    }
    
    void proc(pitem t){
        if(!t)return;
        reset(t);
        combine(t, t -> l, t);
        combine(t, t, t -> r);
    }
    void prop(pitem t){
		if(!t || t -> lz == 0)return;
		t -> lz = 0;
		swap(t -> r, t -> l);
		if(t -> r)t -> r -> lz ^= 1;
		if(t -> l)t -> l -> lz ^= 1;
	}
    
    void split(pitem t, pitem &l, pitem &r, int key, int add = 0){
		prop(t);
        if(!t)return void(l = r = NULL);
        int cur_pos = add + get_sz(t -> l);
        if(key <= cur_pos)split(t -> l, l, t -> l, key, add), r = t;
        else split(t -> r, t -> r, r, key, cur_pos + 1), l = t;
        upd_sz(t);
        proc(t);
    }
    
    void merge(pitem &t, pitem l, pitem r){
		prop(l), prop(r);
        if(!l || !r)return void(t = (l ? l : r));
        if(l -> prior < r -> prior) merge(r -> l, l, r -> l), t = r;
        else merge(l -> r, l -> r, r), t = l;
        upd_sz(t);
        proc(t);
    }
    
    void build(int ss, int sf, pitem &t){
        if(ss > sf)return;
        if(ss == sf)return void(t = new item(vert(ara[ss])));
        int mid = ss + sf >> 1;
        t = new item(vert(ara[mid]));
        pitem a = NULL, b = NULL;
        build(ss, mid - 1, a);
        build(mid + 1, sf, b);
        merge(a, a, t);
        merge(t, a, b);
    }
    void build(int ss,int sf){
        build(ss, sf, root);
    }
    
    void insert(vert v, int pos){
        if(!root)return void(root = new item(v));
        pitem l, r;
        l = r = NULL;
        split(root, l, r, pos - 1);
        merge(l, l, new item(v));
        merge(root, l, r);
    }
    
    void erase(int pos, pitem &t, int add = 0){
        prop(t);
        if(!t)return;
        if(get_sz(t -> l) + add + 1 == pos)merge(t, t -> l, t -> r), proc(t);
        else if(get_sz(t -> l) + add >= pos)erase(pos, t -> l, add);
        else erase(pos, t -> r, add + get_sz(t -> l) + 1);
        upd_sz(t);
        proc(t);
    }
    void erase(int pos){
        if(!root)return;
        pitem l = NULL, r = NULL;
        split(root, l, r, pos);
        pitem w = NULL;
        split(l, l, w, pos - 1);
        delete w;
        merge(root, l, r);
    }
    
    void replace(int pos, pitem t, vert v, int add = 0){
        if(!t)return;
        prop(t);
        if(get_sz(t -> l) + add + 1 == pos)t -> val = v;
        else if(get_sz(t -> l) + add >= pos)replace(pos, t -> l, v, add);
        else replace(pos, t -> r, v, add + get_sz(t -> l) + 1);
    }
    void replace(int pos, vert v){
        if(!root)return;
        pitem l = NULL, r = NULL;
        split(root, l, r, pos);
        pitem w = NULL;
        split(l, l, w, pos - 1);
        w -> val = v;
        merge(l, l, w);
        merge(root, l, r);
    }
    
    vert find(int pos, pitem t, int add = 0){
        if(!t)return vert();
        prop(t);
        if(get_sz(t -> l) + add + 1 == pos)return t -> val;
        else if(get_sz(t -> l) + add >= pos)return find(pos, t -> l, add);
        else return find(pos, t -> r, add + get_sz(t -> l) + 1);
    }
    vert find(int pos){return find(pos,root);}
    
    void update(int l, int r){
		pitem L = NULL, mid = NULL, R = NULL;
        split(root, L, mid, l - 1);
        split(mid, root, R, r - l + 1);
        root -> lz ^= 1;
        merge(mid, L, root);
        merge(root, mid, R);
	}
    
    vert query(int l, int r){
        pitem L = NULL, mid = NULL, R = NULL;
        split(root, L, mid, l - 1);
        split(mid, root, R, r - l + 1);
        vert ans = root -> val;
        merge(mid, L, root);
        merge(root, mid, R);
        return ans;
    }
    size_t size(){
        return get_sz(root);
    }
    void clear(pitem t){
        if(t == NULL)return;
        clear(t -> l);
        clear(t -> r);
        delete t;
    }
    ~Treap(){
        clear(root);
    }
};
