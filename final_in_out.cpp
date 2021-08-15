class input
{
    static const int string_size=1000000;
    char temp[string_size];
public:
    input& operator>>(int &x){scanf("%d",&x);return *this;}
    input& operator>>(long long int &x){scanf("%lld",&x);return *this;}
    input& operator>>(char &x){scanf("%c",&x);return *this;}
    input& operator>>(char s[]){scanf("%s",s);return *this;}
    input& operator>>(string &s){scanf("%s",temp);s=temp;return *this;}
    input& operator>>(double &f){scanf("%lf",&f);return *this;}
    template <class L,class R> input& operator>>(pair<L,R> &x){(*this)>>x.first>>x.second;return *this;}
    template <class L> input& operator>>(vector<L> &x){for(L &y:x)(*this)>>y;return *this;}
    template <class T> void getarray(T *x,int n){for(int i=0;i<n;i++)(*this)>>x[i];}
    void ignore(){getchar();}
}in;
class output
{
public:
    output& operator<<(int x){printf("%d",x);return *this;}
    output& operator<<(long long int x){printf("%lld",x);return *this;}
    output& operator<<(char x){printf("%c",x);return *this;}
    output& operator<<(char s[]){printf("%s",s);return *this;}
    output& operator<<(string s){printf("%s",s.c_str());return *this;}
    output& operator<<(double f){printf("%f",f);return *this;}
    output& operator<<(basic_ostream<char,char_traits<char>>&(*f)(basic_ostream<char,char_traits<char>>&)){printf("\n");fflush(stdout);return *this;}
    template <class L,class R> output& operator<<(pair<L,R> &x){(*this)<<x.first<<' '<<x.second;return *this;}
    template <class L> output& operator<<(vector<L> &x){for(int i=0;i<x.size();i++){if(i!=0)(*this)<<' ';(*this)<<x[i];}return *this;}
    template <class T> void putarray(T *x,int n){for(int i=0;i<n;i++){if(i!=0)(*this)<<' ';(*this)<<x[i];}}
}out;

void fastscan(ll &x)
{
    char c=getchar();
    ll m=1;
    if(c=='-')m=-1,c=getchar();
    x=0;
    while(isdigit(c))x=x*10+c-'0',c=getchar();
    x*=m;
}




//Updated with __int128

class input
{
	static const int string_size=1000000;
	char temp[string_size];
public:
    input& operator>>(int &x){scanf("%d",&x);return *this;}
    input& operator>>(unsigned int &x){scanf("%u",&x);return *this;}
    input& operator>>(long long int &x){scanf("%lld",&x);return *this;}
    input& operator>>(unsigned long long int &x){scanf("%llu",&x);return *this;}
    input& operator>>(char &x){scanf("%c",&x);return *this;}
    input& operator>>(char s[]){scanf("%s",s);return *this;}
    input& operator>>(string &s){scanf("%s",temp);s=temp;return *this;}
    input& operator>>(double &f){scanf("%lf",&f);return *this;}
#ifdef __SIZEOF_INT128__
    input& operator>>(__int128 &x){
        char c=getchar();
        int m=1;
        if(c=='-')m=-1,c=getchar();
        while(!isdigit(c))c=getchar();
        x=0;
        while(isdigit(c))x=x*10+c-'0',c=getchar();
        x*=m;
        return *this;
    }
#endif
    template <class L,class R> input& operator>>(pair<L,R> &x){(*this)>>x.first>>x.second;return *this;}
    template <class L> input& operator>>(vector<L> &x){for(L &y:x)(*this)>>y;return *this;}
    template <class T> void getarray(T *x,int n){for(int i=0;i<n;i++)(*this)>>x[i];}
    void ignore(){getchar();}
}in;
class output
{
public:
    output& operator<<(int x){printf("%d",x);return *this;}
    output& operator<<(unsigned int x){printf("%u",x);return *this;}
    output& operator<<(size_t x){printf("%u",(unsigned int)x);return *this;}
    output& operator<<(long long int x){printf("%lld",x);return *this;}
    output& operator<<(unsigned long long int x){printf("%llu",x);return *this;}
    output& operator<<(char x){printf("%c",x);return *this;}
    output& operator<<(const char s[]){printf("%s",s);return *this;}
    output& operator<<(string s){printf("%s",s.c_str());return *this;}
    output& operator<<(double f){printf("%.10f",f);return *this;}
#ifdef __SIZEOF_INT128__
    output& operator<<(__int128 x){
        string s;
        if(x<0)s.push_back('-'),x=-x;
        if(x==0)s.push_back('0');
        int u=s.size();
        while(x)s.push_back((char)(x%10+'0')),x/=10;
        reverse(s.begin()+u,s.end());
        printf("%s",s.c_str());
        return *this;
    }
#endif
    output& operator<<(basic_ostream<char,char_traits<char>>&(*f)(basic_ostream<char,char_traits<char>>&)){printf("\n");fflush(stdout);return *this;}
    template <class L,class R> output& operator<<(pair<L,R> x){(*this)<<x.first<<' '<<x.second;return *this;}
    template <class L> output& operator<<(vector<L> &x){for(int i=0;i<x.size();i++){if(i!=0)(*this)<<' ';(*this)<<x[i];}return *this;}
    template <class T> void putarray(T *x,int n){for(int i=0;i<n;i++){if(i!=0)(*this)<<' ';(*this)<<x[i];}}

}out;
