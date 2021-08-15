
ll s2[105][105];
void s2_init(ll mx_n,ll mx_k,ll md=0){
    memset(s2,0,sizeof s2);
    s2[0][0]=1;
    for(int i=1;i<=mx_n;i++){
        for(int j=1;j<=mx_k;j++){
            if(md==0)
                s2[i][j]=s2[i-1][j-1]+s2[i-1][j]*j;
            else
                s2[i][j]=(s2[i-1][j-1]+s2[i-1][j]*j%md)%md;
        }
    }
}

//Formula:
//  Sum of (i^k) for(i=1....n)  =  sum of( j!*s2(k,j)*((n+1)C(j+1))) for (j=1...k)

// s2(n,k)=  Sum( (-1)^(k-j)*(kCj)*j^n)/(k!)  for(j=0...k)
