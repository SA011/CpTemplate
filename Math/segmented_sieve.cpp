int prime[asz],prime_ind=0;
void segmented_sieve(int n){
  int seg=sqrt(n)+1;   vector<bool> mark(seg+1,1);
  mark[0]=mark[1]=1;    prime[prime_ind++]=2;
  for(int i=3;i<seg;i+=2){
    if(mark[i]){
      prime[prime_ind++]=i;
      if((long long)i*i>=seg)continue;
      for(int j=i*i;j<seg;j+=2*i)   mark[j]=0;
    }
  }
  int fp=prime_ind,lo=seg,hi=2*seg;
  while(lo<n){
    if(hi>=n)hi=n;
    fill(mark.begin(),mark.end(),1);
    for(int i=0;i<fp;i++){
      int lolim=lo/prime[i]*prime[i];
      if(lolim<lo)lolim+=prime[i];
    for(int j=lolim;j<hi;j+=prime[i])mark[j-lo]=0;
    }
    for(int i=lo;i<hi;i++){
      if(mark[i-lo])prime[prime_ind++]=i;
    }
    lo=hi;  hi+=seg;
  }
}
