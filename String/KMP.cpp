
//KMP

ll kmp[asz];
void kmpprocess(string &s)
{
    ll j=-1,n=s.size();
    kmp[0]=-1;
    for(ll i=0;i<n;)
    {
        while(j>=0&&s[i]!=s[j])j=kmp[j];
        j++,i++;
        kmp[i]=j;
    }
}

vector<ll> kmpsearch(string &text,string &pat,vector<ll> &kmp)
{
    ll j=0,n=s.size();
    vector<ll> ans;
    for(ll i=0;i<n;)
    {
        while(j>=0&&text[i]!=pat[j])j=kmp[j];
        i++,j++;
        if(j==pat.size())ans.push_back(i-j),j=kmp[j];
    }
    return ans;
}
