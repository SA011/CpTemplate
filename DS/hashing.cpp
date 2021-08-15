
const ll h_mod=1000003;
ll val[h_mod],indx[h_mod],prevs[h_mod],keys[h_mod];
ll ind=0;
void insrt(ll ky,ll vl)
{
    ll x=ky%h_mod;
    val[ind]=vl;
    keys[ind]=ky;
    prevs[ind]=indx[x];
    indx[x]=ind++;
}
ll fnd(ll ky)
{
    ll x=ky%h_mod;
    for(ll i=indx[x];i!=-1;i=prevs[i])
        if(keys[i]==ky)return val[i];
    return -1;

}
