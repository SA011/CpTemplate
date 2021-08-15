
struct BitVector{
//pragma GCC target ("sse4.2")
    using T = unsigned int;
    int n, blk;
    vector<T> bits,cnt;
    BitVector(int _n = 0):n(_n){
        blk = (n + 32) >> 5;
        bits.assign(blk,0);
        cnt.assign(blk,0);
    }
    inline bool operator[] (int i){ return (bits[i >> 5] >> (i & 31)) & 1;}
    inline void set(int i){ bits[i >> 5] |= 1 << (i & 31);}
    inline void reset(int i){  bits[i >> 5] &= ~(1 << (i & 31));}
    void build(){
        for(int i = 0,cur = 0; i < blk; i++){
            cnt[i] = cur;
            cur += __builtin_popcountll(bits[i]);
        }
    }
    inline T count(int l) { return cnt[l>>5] + __builtin_popcountll(bits[l>>5] & ((1 << (l&31))-1));}
    inline T count(int dig,int l) {return dig ? count(l) : l - count(l);}
    inline T count(int dig,int l,int r) { return count(dig,r) - count(dig,l);}
    inline bool swap(int l){
        if(operator [](l) == operator [](l+1))return false;
        if((l & 31) == 31){
            if(operator [](l))cnt[l >> 5]--, cnt[(l >> 5) + 1]++, reset(l), set(l + 1);
            else cnt[l >> 5]++, cnt[(l >> 5) + 1]--, set(l), reset(l + 1);
        }
        else{
            bits[l >> 5] ^= (3 << (l&31));
        }
        return true;
    }
};
struct WaveletMatrix{
    using T = ll;
    vector<BitVector> lvl;
    vector<int> mid;
    T offset;
    int h, n;
    void build(vector<T> v){
        v.push_back(0);
        n = v.size();
        offset = -*min_element(v.begin(),v.end());
        for(auto &x:v)x += offset;
        h = *max_element(v.begin(),v.end());
        h = 64 - __builtin_clzll(h);
        lvl.assign(h, BitVector(n));
        mid.assign(h,0);
        T msk = 1LL << (h-1);
        vector<T> temp = v;
        
        for(int i = 0; i < h; i++){
            int z = 0;
            for(auto &x:v)z += !(x & msk);
            mid[i] = z;
            for(int j = 0, k = 0; j < n; j++){
                if(v[j] & msk)temp[z++] = v[j], lvl[i].set(j);
                else temp[k++] = v[j], lvl[i].reset(j);
            }
            v = temp;
            lvl[i].build();
            msk >>= 1;
        }
    }
    WaveletMatrix(vector<T> &v){
        build(v);
    }
    WaveletMatrix(){
        vector<T> temp;
        build(temp);
    }
    
    T access(int ind){
        T res = 0;
        for(int i = 0; i < h; i++){
            int cur = lvl[i][ind];
            res = (res << 1) | cur;
            ind = lvl[i].count(cur,ind);
            if(cur) ind += mid[i];
        }
        return res - offset;
    }
    
    T quantile(int l, int r, int k, bool rev = false){
        //k th smallest ( largest if rev = true ) element in [l,r)
        if(l < 0 || r >= n || k < 0 || k >= r-l)return -1;
        T res = 0;
        for(int i = 0; i < h; i++){
            int temp = lvl[i].count(rev, l, r);
            int cur = (k >= temp) ^ rev;
            res = (res << 1) | cur;
            if(cur ^ rev)k -= temp;
            l = lvl[i].count(cur,l), r = lvl[i].count(cur,r);
            if(cur) l += mid[i], r += mid[i];
        }
        return res - offset;
    }
    tuple<int,int,int> rank(int l, int r, T v){
        int ls = 0, gt = 0;
        v += offset;
        for(int i = 0; i < h; i++){
            int cur = (v >> (h-1-i)) & 1;
            int nl = lvl[i].count(cur, l), nr = lvl[i].count(cur, r);
            if(cur)ls += (r - l) - (nr - nl);
            else gt += (r - l) - (nr - nl);
            
            l = nl, r = nr;
            if(cur)l += mid[i], r += mid[i];
        }
        return make_tuple(ls,r-l,gt);
    }
    void swap(int ind){
        if(ind < 0 || ind + 1 >= n)return;
        for(int i = 0; i < h; i++){
            if(lvl[i].swap(ind))break;
            bool cur = lvl[i][ind];
            ind = lvl[i].count(cur,ind);
            if(cur)ind += mid[i];
        }
    }
};
