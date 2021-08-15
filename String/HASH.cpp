#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define asz 100
const int NOB=2;
class Hash
{
public:
    ll v[NOB];
    Hash(ll vl=0){for(int i=0;i<NOB;i++)v[i]=vl;}
    Hash(ll _v[]){for(int i=0;i<NOB;i++)v[i]=_v[i];}
    Hash operator+(Hash x){Hash ans(NOB); for(int i=0;i<NOB;i++)ans.v[i]=v[i]+x.v[i];return ans;}
    Hash operator*(Hash x){Hash ans(NOB); for(int i=0;i<NOB;i++)ans.v[i]=v[i]*x.v[i];return ans;}
    Hash operator*(ll x){Hash ans(NOB); for(int i=0;i<NOB;i++)ans.v[i]=v[i]*x;return ans;}
    Hash operator-(Hash x){Hash ans(NOB); for(int i=0;i<NOB;i++)ans.v[i]=v[i]-x.v[i];return ans;}
    Hash operator%(Hash x){Hash ans(NOB); for(int i=0;i<NOB;i++)ans.v[i]=v[i]%x.v[i];return ans;}
    //bool operator<(Hash x){for(int i=0;i<NOB;i++)if(v[i]!=x.v[i])return v[i]<x.v[i];return false;}
    friend bool operator<(Hash y,Hash x){for(int i=0;i<NOB;i++)if(y.v[i]!=x.v[i])return y.v[i]<x.v[i];return false;}
    bool operator==(Hash x){int i=0;while(i<NOB&&v[i]==x.v[i])i++;return i==NOB;}
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
ll _b[]={31,53};
ll _m[]={(ll)(1e9+7),(ll)(1e9+9)};
Hash base(_b);
Hash MOD(_m);
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
Hash full_hash(string &v)
{
    for(int i=1;i<=v.size();i++)
    {
        val[i]=(val[i-1]+pn[i-1]*(ll)(v[i-1]-'a'+1))%MOD;
    }
    return val[(ll)v.size()];
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
    cout<<full_hash(s)<<endl;
    ll q;
    for(int i=0;i<s.size();i++)cout<<val[i]<<endl;
    cin>>q;
    while(q--)
    {
        ll l,r;
        cin>>l>>r;
        cout<<s.substr(l,(r-l+1))<<endl;
        cout<<hashed_val(l,r)<<endl;
    }
}
