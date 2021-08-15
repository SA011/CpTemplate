/*Template Matrix
    Fib: vector<vector<ll>> v(2);v[0]={0,1},v[1]={1,1};
    FibSum: vector<vector<ll>> v(4); v[0]={0,0,0,0},v[1]={1,0,0,-1},v[2]={0,1,0,0},v[3]={0,0,1,2};
*/
template <class T> class MATRIX
{
public:
    vector<vector<T>> mat;
    ll n,m;
    ll md;
    MATRIX(vector<vector<T>> &MT, ll MD=0)
    {
        mat=MT;
        n=mat.size();
        m=mat[0].size();
        md=MD;
    }
    MATRIX(ll N=0,ll M=0,ll MD=0)
    {
        n=N,m=M;
        mat.resize(N,vector<T>(M));
        md=MD;
    }
    MATRIX(string c,ll N=0,ll M=0,ll MD=0)
    {

        n=N,m=M;
        mat.resize(N,vector<T>(M));
        md=MD;
        if((c=="i"||c=="I")&&n==m)
        {
            for(int i=0;i<n;i++)mat[i][i]=1;
        }
    }
    void PRINT()
    {
        for(ll i=0;i<n;i++)
        {
            for(ll j=0;j<m;j++)cout<<mat[i][j]<<' ';
            cout<<endl;
        }
    }
    MATRIX& operator=(MATRIX MT)
    {
        mat=MT.mat;
        n=MT.n;
        m=MT.m;
        md=MT.md;
        return *this;
    }
    MATRIX& operator+=(MATRIX &MT)
    {
        if(n!=MT.n||m!=MT.m)return *this;
        for(ll i=0;i<n;i++)
        {
            for(ll j=0;j<m;j++)
            {
                mat[i][j]+=MT.mat[i][j];
                if(md)mat[i][j]=(mat[i][j]+md)%md;
            }
        }
        return *this;
    }
    MATRIX& operator*=(MATRIX &MT)
    {
        if(m!=MT.n)return *this;
        MATRIX<T> temp(n,MT.m,md);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<MT.m;j++)
            {
               T sum=0;
               for(int k=0;k<m;k++)
               {
                   if(md)
                    sum+=(mat[i][k]*MT.mat[k][j]+md)%md,sum%=md;
                   else
                    sum+=(mat[i][k]*MT.mat[k][j]);
               }
               temp.mat[i][j]=sum;
            }
        }
        m=MT.m,mat=temp.mat;
        return *this;
    }
    MATRIX& operator-=(MATRIX &MT)
    {
        if(n!=MT.n||m!=MT.m)return *this;
        for(ll i=0;i<n;i++)
        {
            for(ll j=0;j<m;j++)
            {
                mat[i][j]-=MT.mat[i][j];
                if(md)mat[i][j]+=md,mat[i][j]%=md;
            }
        }
        return *this;
    }
    MATRIX operator+(MATRIX &MT)
    {
        MATRIX<T> temp=(*this);
        temp+=MT;
        return temp;
    }
    MATRIX operator-(MATRIX &MT)
    {
        MATRIX<T> temp=(*this);
        temp-=MT;
        return temp;
    }
    MATRIX operator*(MATRIX &MT)
    {
        MATRIX<T> temp=(*this);
        temp*=MT;
        return temp;
    }
    MATRIX POWER(MATRIX &MT,ll pwr)
    {
        if(MT.n!=MT.m||pwr==1)return MT;
        if(pwr==0)return MATRIX<T>("I",MT.n,MT.m,MT.md);
        MATRIX<T> temp=MT;
        temp*=temp;
        temp=POWER(temp,pwr/2);
        if(pwr%2)return MT*temp;
        return temp;
    }
    MATRIX& POWER(ll pwr)
    {
        if(n!=m||pwr==1)return *this;
        (*this)=POWER(*this,pwr);
        return (*this);
    }
    T det()
    {
        T ans=0;
        if(n!=m||n==0)return 0;
        if(n==1)return mat[0][0];
        for(ll i=0;i<m;i++)
        {
            MATRIX<T> temp(n-1,m-1,md);
            for(ll j=1;j<n;j++)
            {
                ll x=0;
                for(ll k=0;k<m-1;k++)
                {
                    if(i==k)x=1;
                    temp.mat[j-1][k]=mat[j][k+x];
                }
            }
            ans=(ans+(i%2?-1:1)*mat[0][i]*temp.det());
            if(md)ans+=md,ans%=md;
        }
        return ans;
    }
    vector<T>& operator[](int i)
    {
        return mat[i];
    }
};




//Faster
vector<vi> mul(vector<vi> &a,vector<vi> &b,ll md){
    vector<vi> v(a.size(),vi(b[0].size()));
    int l=a[0].size();
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[i].size();j++){
            __int128 p=0;
            for(int k=0;k<l;k++)p+=a[i][k]*b[k][j];
            v[i][j]=p%md;
        }
    }
    return v;
}

vector<vi> POWER(vector<vi> a,ll n,ll md){
    vector<vi> ans(a.size(),vi(a.size()));
    int m=a.size();
    for(int i=0;i<m;i++)ans[i][i]=1;
    while(n){
        if(n&1)ans=mul(ans,a,md);
        n>>=1;
        if(n)a=mul(a,a,md);
    }
    return ans;
}


//static array construction
//r = a*b;
//pr = b^n;


const int N = 35;

ll a[N][N],b[N][N],r[N][N],pr[N][N];
void mul(ll md){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            ll p=0;
            for(int k=0;k<N;k++)p=(p+a[i][k]*b[k][j])%md;
            r[i][j]=p;
        }
    }
}
void POWER(ll n,ll md){
    memset(pr,0,sizeof pr);
    for(int i=0;i<N;i++)pr[i][i]=1;
    while(n){
        if(n&1){
            for(int i=0;i<N;i++)for(int j=0;j<N;j++)a[i][j] = pr[i][j];
            mul(md);
            for(int i=0;i<N;i++)for(int j=0;j<N;j++)pr[i][j] = r[i][j];
        }
        n>>=1;
        if(n){
            for(int i=0;i<N;i++)for(int j=0;j<N;j++)a[i][j] = b[i][j];
            mul(md);
            for(int i=0;i<N;i++)for(int j=0;j<N;j++)b[i][j] = r[i][j];

        }
    }
}
