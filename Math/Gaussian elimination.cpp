int gauss(vector<vector<double>> &mat,vector<double> &ans){        //returns -1 if impossible,1 if solution is unique, 0 otherwise
    int n=mat.size(),m=mat[0].size()-1;             
    vector<int> w(m,-1);
    int ret=1;
    for(int i=0,j=0;j<n&&i<m;i++){
        int mx=j;
        for(int k=j+1;k<n;k++)if(mat[mx][i]<mat[k][i])mx=k;
        if(abs(mat[mx][i])<EPS){
            ret=0;
            continue;
        }
        for(int k=i;k<=m;k++)swap(mat[j][k],mat[mx][k]);
        for(int k=0;k<n;k++){
            if(k==j)continue;
            double d=mat[k][i]/mat[j][i];
            for(int l=i;l<=m;l++)mat[k][l]-=d*mat[j][l];
        }
        w[i]=j++;
    }
    ans.assign(m,0);
    for(int i=0;i<m;i++)if(w[i]!=-1)ans[i]=mat[w[i]][m]/mat[w[i]][i];
    for(int i=0;i<n;i++){
        double d=0;
        for(int j=0;j<m;j++)d+=ans[j]*mat[i][j];
        if(abs(d-mat[i][m])>EPS)return -1;
    }
    return ret;
}




//modular SLAE

ll fastpow(ll val,ll pwr,ll md=0)
{
    if(pwr==0)return 1;
    if(md){
    if(pwr%2)return (val*fastpow((val*val)%md,pwr/2,md))%md;
    return fastpow((val*val)%md,pwr/2,md);
    }
    else
    {
        if(pwr%2)return val*fastpow(val*val,pwr/2);
        return fastpow(val*val,pwr/2);
    }
}
int gauss(vector<vector<ll>> &mat,vector<ll> &ans,ll md){
    int n=mat.size(),m=mat[0].size()-1;
    vector<int> w(m,-1);
    int ret=1;
    for(int i=0,j=0;j<n&&i<m;i++){
        int mx=j;
        for(int k=j+1;k<n;k++)if(mat[mx][i]<mat[k][i])mx=k;
        if(!mat[mx][i]){
            ret=0;
            continue;
        }
        for(int k=i;k<=m;k++)swap(mat[j][k],mat[mx][k]);
        for(int k=0;k<n;k++){
            if(j==k)continue;
            ll d=mat[k][i]*fastpow(mat[j][i],md-2,md)%md;
            for(int l=i;l<=m;l++)mat[k][l]-=d*mat[j][l]%md,mat[k][l]+=md,mat[k][l]%=md;
        }
        w[i]=j++;
    }
    ans.assign(m,0);
    for(int i=0;i<m;i++)if(w[i]!=-1)ans[i]=mat[w[i]][m];
    for(int i=0;i<n;i++){
        ll d=0;
        for(int j=0;j<m;j++)d+=ans[j]*mat[i][j]%md,d%=md;
        if(d!=mat[i][m])return -1;
    }
    return ret;
}



//mod=2
int gauss(vector<bitset<asz>> &mat,int m,bitset<asz> &ans){
    int n=mat.size();
    vector<int> w(m,-1);
    int ret=1;
    for(int i=0,j=0;j<n&&i<m;i++){
        for(int k=j;k<n;k++)if(mat[k][i]){swap(mat[j],mat[k]);break;}
        if(!mat[j][i]){
            ret=0;
            continue;
        }
        for(int k=0;k<n;k++){
                if(k!=j&&mat[k][i])mat[k]^=mat[j];
        }
        w[i]=j++;
    }
    ans.reset();
    for(int i=0;i<m;i++)if(w[i]!=-1)ans[i]=mat[w[i]][m];
    for(int i=0;i<n;i++){
        int d=0;
        for(int j=0;j<m;j++)d+=(ans[j]&mat[i][j]);
        if(d^mat[i][m])return -1;
    }
    return ret;
}
