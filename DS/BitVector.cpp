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
