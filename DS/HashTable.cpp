namespace HashTable{
    const int hMod = 1e6 + 3;
    ll val[hMod], keys[hMod];
    int indx[hMod], prevs[hMod], ind = -1;
    void init(){
        if(ind < 0){
            memset(indx, -1, sizeof indx);
            memset(prevs, -1, sizeof prevs);
            ind = 0;
        }
        while(ind){
            prevs[keys[--ind] % hMod] = -1;
            indx[keys[ind] % hMod] = -1;
        }
    }
    int searchInd(ll ky){
        int x = ky % hMod;
        for(int i = indx[x]; i != -1; i = prevs[i])
            if(keys[i] == ky)return i;
        return -1;
    }
    
    void setVal(ll ky, ll v){
        int cur = searchInd(ky);
        if(cur != -1){
            val[cur] = v;
            return;
        }
        int x = ky % hMod;
        val[ind] = v;
        keys[ind] = ky;
        prevs[ind] = indx[x];
        indx[x] = ind++;
    }
    
    ll getVal(ll ky){
        int cur = searchInd(ky);
        return cur == -1 ? 0 : val[cur];
    }
};
