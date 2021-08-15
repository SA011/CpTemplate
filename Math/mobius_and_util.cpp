
int mu[asz];
void mobius()
{
    memset(mu,-1,sizeof mu);
    mu[1]=1;
    for(int i=2;i<asz;i++)for(int j=2*i;j<asz;j+=i)mu[j]-=mu[i];
}
int number_of_coprime(vi &cnt,vi &divs){
    int a=0;
    for(auto x:divs)a+=cnt[x]*mu[x];
    return a;
}
vi dv[asz];
ll largest_coprime_product(vi &v,vi &cnt){
    ll ans=0;
    vi a;
    for(int i=(int)v.size()-1;i>=0;i--){
        int x=number_of_coprime(cnt,dv[v[i]]);
        while(x--){
            while(1){
                for(auto y:dv[a.back()])cnt[y]--;
                if(__gcd(a.back(),v[i])==1)break;
                a.pop_back();
            }
            ans=max(ans,a.back()*v[i]);
            a.pop_back();
        }
        a.push_back(v[i]);
        for(auto y:dv[v[i]])cnt[y]++;
    }
    while(!a.empty()){
        for(auto y:dv[a.back()])cnt[y]--;
        a.pop_back();
    }
    return ans;
}
