#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define asz 100
ll NOB=2;
class Hash
{
public:
    vector<ll> v;
    Hash(ll vl=0){v.assign(NOB,vl);}
    Hash(vector<ll> _v):v(_v){}
    Hash operator+(Hash x){Hash ans(NOB); for(int i=0;i<NOB;i++)ans.v[i]=v[i]+x.v[i];return ans;}
    Hash operator*(Hash x){Hash ans(NOB); for(int i=0;i<NOB;i++)ans.v[i]=v[i]*x.v[i];return ans;}
    Hash operator*(ll x){Hash ans(NOB); for(int i=0;i<NOB;i++)ans.v[i]=v[i]*x;return ans;}
    Hash operator-(Hash x){Hash ans(NOB); for(int i=0;i<NOB;i++)ans.v[i]=v[i]-x.v[i];return ans;}
    Hash operator%(Hash x){Hash ans(NOB); for(int i=0;i<NOB;i++)ans.v[i]=v[i]%x.v[i];return ans;}
    bool operator<(Hash x){return v<x.v;}
    bool operator==(Hash x){return v==x.v;}
    friend ostream& operator<<(ostream& s,Hash x)
    {
        cout<<"{ ";
        for(int i=0;i<NOB;i++)
        {
            if(i)cout<<", ";
            cout<<x.v[i];
        }
        cout<<" }"<<endl;
        return s;
    }
};
ll bigmod(ll a,ll p, ll m)
{
    ll res=1,x=a;
    while(p)
    {
        if(p&1)res=(res*x)%m;
        x=(x*x)%m;
        p>>=1;
    }
    return res;
}
Hash base({31,53});
Hash MOD({(ll)(1e9+7),(ll)(1e9+9)});
Hash val[asz],pn[asz],pinv[asz];
void preprocess()
{
    pn[0]=pinv[0]=Hash(1);
    for(int i=0;i<NOB;i++)
    {
        pinv[1].v[i]=bigmod(base.v[i],MOD.v[i]-2,MOD.v[i]);
        pn[1].v[i]=base.v[i];
    }
    for(int i=2;i<asz;i++)
    {
        pn[i]=(pn[i-1]*base)%MOD;
        pinv[i]=(pinv[i-1]*pinv[1])%MOD;
    }
}
Hash full_hash(vector<ll> &v)
{
    for(int i=1;i<=v.size();i++)
    {
        val[i]=(val[i-1]+pn[i-1]*v[i-1])%MOD;
    }
    return val[(ll)v.size()];
}
Hash string_hashing(string &s)
{
    vector<ll> v;
    for(auto x:s)v.push_back(x-'a'+1);
    return full_hash(v);
}
//0 indexed
Hash hashed_val(ll l,ll r)
{
    return (((val[r+1]-val[l]+MOD)%MOD)*pinv[l])%MOD;
}

int main()
{
    string s;
    cin>>s;
    preprocess();
    cout<<string_hashing(s)<<endl;
}
