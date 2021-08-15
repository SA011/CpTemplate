
const int D=31;
ll bs[D];
ll sz;
void add_val(ll x){
    for(ll i=0;x&&i<D;i++){
        if(x&(1LL<<i)){
            if(!bs[i])bs[i]=x,sz++;
            x^=bs[i];
        }
    }
}
