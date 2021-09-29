
const int D = 31;
ll bs[D];
int sz;
void addVal(ll x){
    for(int i = 0; x && i < D; i++){
        if(x & (1LL << i)){
            if(!bs[i])bs[i] = x, sz++;
            x ^= bs[i];
        }
    }
}
