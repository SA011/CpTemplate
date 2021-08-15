//Sparse table
#define mxlg 25
ll st[asz][mxlg];
ll lg[asz];
ll ara[asz];
void init(int n)
{
    for(int i=0;i<n;i++)st[i][0]=ara[i];
    lg[1]=0;
    for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
    for(int i=1;i<mxlg;i++)
    {
        for(int j=0;j+(1<<i)<=n;j++)
            st[j][i]=max(st[j][i-1],st[j+(1<<(i-1))][i-1]);
    }
}
ll query(ll l,ll r)
{
    ll x=lg[r-l+1];
    return max(st[l][x],st[r-(1<<x)+1][x]);
}
//Sum
ll query(ll l,ll r)
{
    ll sum=0;
    for(ll i=mxlg-1;i>=0;i--)
    {
        if((1<<i)<=(r-l+1))
        {
            sum+=st[l][i];
            l+=(1<<i);
        }
    }
    return sum;
}
