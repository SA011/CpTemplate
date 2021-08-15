int LIS(vector<long long> &v)
{
    int n=v.size();
    vector<long long> dp(n+2,LONG_LONG_MAX);
    dp[0]=LONG_LONG_MIN;
    int ans=0;
    for(int i=0;i<n;i++)
    {
        int j=upper_bound(dp.begin(),dp.end(),v[i])-dp.begin();
        if(dp[j-1]<v[i])dp[j]=min(dp[j],v[i]),ans=max(ans,j);
    }
    return ans;
}
