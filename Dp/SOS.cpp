//∀x F(x) = Sum of all A[i] such that x&i=i
// to x&i=x, i is superset of x change
// mask&(1<<i) to !(mask&(1<<i))
for(int i=0;i<(1<<N);++i) F[i] = A[i];
for(int i=0;i<N;++i)
  for(int mask = 0; mask < (1<<N); ++mask)
    if(mask&(1<<i)) F[mask]+=F[mask^(1<<i)];
// iterate over all the subsets of the mask
for(int i = mask; i > 0; i = (i-1) & mask)
