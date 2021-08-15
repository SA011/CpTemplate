
//Calculates minimum number of move required to transform pre into cur.
const int N=8;
int dp[1<<N];
int check(int ind,int mask,vii &pre,vii &cur){
    if(ind==N)return 0;
    if(dp[mask]!=-1)return dp[mask];
    int a=N*4;
    for(int i=0;i<N;i++){
        if(getbit(mask,i))continue;
        int x=check(ind+1,setbit1(mask,i),pre,cur);
        if(pre[ind]==cur[i])a=min(a,x);
        else if(pre[ind].fi==cur[i].fi||pre[ind].se==cur[i].se||abs(pre[ind].fi-cur[i].fi)==abs(pre[ind].se-cur[i].se))a=min(a,x+1);
        else a=min(a,x+2);
    }
    return dp[mask]=a;
}


//Finds the ways to put N queen in NxN board and keeps it in placed.
const int N=8;
vector<vii> placed;
void solve(int col,int ld,int rd,vii &cur){
    if(cur.size()==N){
        placed.push_back(cur);
        return;
    }
    int mask=col|ld|rd;
    for(int i=0;i<N;i++){
        if(!getbit(mask,i)){
            cur.push_back(ii(cur.size(),i));
            solve(setbit1(col,i),setbit1(ld,i)<<1,setbit1(rd,i)>>1,cur);
            cur.pop_back();
        }
    }
}
