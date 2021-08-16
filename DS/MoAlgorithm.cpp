const int B = 200;
struct query{
    int l, r, nUpd, ind;
    bool operator < (const query &a) const{
        if(l / B == a.l / B){
            if(r / B == a.r / B)return nUpd < a.nUpd;
            return r < a.r;
        }
        return l < a.l;
    }
};
struct upd{
    int p, pre, nw;
};
query qr[N];
upd up[N];
ll ara[N], ans[N];
int qL, qR, qU;

void update(int pos, int val){
    if(pos >= qL && pos <= qR){
        del(ara[pos]);
        add(val);
    }
    ara[pos] = val;
}
void MO(int q){
    sort(qr, qr + q);
    qL = 0, qR = -1;
    //qU = 0;
    for(int i = 0; i < q; i++){
        while(qU < qr[i].nUpd)update(up[qU].p, up[qU].nw), qU++;
        while(qU > qr[i].nUpd)qU--, update(up[qU].p, up[qU].pre);
        while(qR < qr[i].r)add(ara[++qR]);
        while(qL > qr[i].l)add(ara[--qL]);
        while(qR > qr[i].r)del(ara[qR--]);
        while(qL < qr[i].l)del(ara[qL++]);
        ans[qr[i].ind] = answer;
    }
}
