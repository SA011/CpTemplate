#include <bits/stdc++.h>
using namespace std;
#define INF 2000000000
typedef long long int ll;
typedef pair<ll,ll> ii;
typedef pair<ii,ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define getbit(n,i) (((n)&(1<<(i)))!=0)
#define setbit0(n,i) ((n)&(~(1<<(i))))
#define setbit1(n,i) ((n)|(1<<(i)))
#define togglebit(n,i) ((n)^(1<<(i)))
#define lastone(n) ((n)&(-(n)))
#define read freopen("debug\\in.txt","r",stdin)
#define write freopen("debug\\out.txt","w",stdout)
#define fi first
#define se second
#define getI(a) scanf("%d",&a)
#define getII(a,b) scanf("%d%d",&a,&b)
#define PI (acos(-1))
#define fastread ios_base::sync_with_stdio(false);cin.tie(NULL)
#define mod (1000000007)
#define asz 100001
int ara[10000];
int main()
{
    write;
    int x=0;
    int ind=0;
    printf("{");
    for(int i=0;i<30030;i++)
    {
        if(i%2&&i%3&&i%5&&i%7&&i%11&&i%13)
        {
            if(x){ara[ind++]=i-x;}
            printf(",%d",ind);
            x=i;
        }
        else
        {
            if(i==0)printf("0");
            else printf(",0");
        }

    }
    printf("};\n");
    for(int i=30030;1;i++)
    {
        if(i%2&&i%3&&i%5&&i%7&&i%11&&i%13)
        {
            ara[ind++]=i-x;
            break;
        }
    }
    printf("{");
    for(int i=0;i<ind;i++)
    {
        printf("%d",ara[i]);
        if(i!=ind-1)printf(",");
    }
    printf("};\n\n");
    printf("%d\n",ind);
}
