class Integer
{
public:
    bool sign=true;
    string s;
    int base=10;
    void set(int rev)
    {
        if(s.size()==0)s="0";
        if(s[0]=='-')s[0]='0',sign=false;
        if(rev)reverse(s.begin(),s.end());
        while(s.size()>1&&s.back()=='0')
            s.pop_back();
        reverse(s.begin(),s.end());
        if(s=="0")
            sign=true;
    }
    Integer(string _s="0",int b=10)
    {
        sign=true;
        base=b;
        s=_s;
        set(1);
    }
    template<class T> Integer(T t,int b=10)
    {
        sign=true;
        if(t<0)t=-t,sign=false;
        base=b;
        if(t==0)
            s="0";
        while(t)
            s+=(t%b+'0'),t/=b;
        reverse(s.begin(),s.end());
    }
    Integer& operator=(Integer x)
    {
        s=x.s,base=x.base,sign=x.sign;
        return *this;
    }
    friend ostream& operator<<(ostream &stream,Integer x)
    {
        if(!x.sign)stream<<'-';
        stream<<x.s;
        return stream;
    }
    friend istream& operator>>(istream &stream,Integer &x)
    {
        stream>>x.s;
        x.base=10;
        x.sign=true;
        x.set(1);
        return stream;
    }
    bool operator<(Integer x)
    {
        if(sign!=x.sign)return !sign;
        if(x.s.size()<s.size())return !sign;
        if(x.s.size()>s.size())return sign;
        for(int i=0;i<s.size();i++)
        {
            if(x.s[i]>s[i])return sign;
            if(x.s[i]<s[i])return !sign;
        }
        return false;
    }
    bool operator>(Integer x)
    {
        if(sign!=x.sign)return sign;
        if(x.s.size()<s.size())return sign;
        if(x.s.size()>s.size())return !sign;
        for(int i=0;i<s.size();i++)
        {
            if(x.s[i]>s[i])return !sign;
            if(x.s[i]<s[i])return sign;
        }
        return false;
    }
    bool operator<=(Integer x)
    {
        return !((*this)>x);
    }
    bool operator>=(Integer x)
    {
        return !((*this)<x);
    }
    bool operator==(Integer x)
    {
        return (sign==x.sign&&x.s==s);
    }
    bool operator!=(Integer x)
    {
        return !((*this)==x);
    }
    template<class T>bool operator<(T x)
    {
        return (*this)<Integer(x);
    }
    template<class T>bool operator>(T x)
    {
        return (*this)>Integer(x);
    }
    template<class T>bool operator<=(T x)
    {
        return (*this)<=Integer(x);
    }
    template<class T>bool operator>=(T x)
    {
        return (*this)>=Integer(x);
    }
    template<class T>bool operator==(T x)
    {
        return (*this)==Integer(x);
    }
    template<class T>bool operator!=(T x)
    {
        return (*this)!=Integer(x);
    }
    Integer operator+=(Integer x);
    Integer operator-=(Integer x);
    Integer operator-()
    {
        Integer x=(*this);
        x.sign=!sign;
        if(x.s=="0")x.sign=true;
        return x;
    }
    Integer operator+(Integer x)
    {
        x+=(*this);
        return x;
    }
    Integer operator-(Integer x)
    {
        x-=(*this);
        return -x;
    }
    template<class T>Integer operator+=(T x)
    {
        (*this)+=Integer(x);
        return (*this);
    }
    template<class T>Integer operator-=(T x)
    {
        (*this)-=Integer(x);
        return (*this);
    }
    template<class T>Integer operator+(T x)
    {
        return (*this)+Integer(x);
    }
    template<class T>Integer operator-(T x)
    {
        return (*this)-Integer(x);
    }
    Integer operator++()
    {
        (*this)+=Integer(1);
        return (*this);
    }
    Integer operator--()
    {
        (*this)-=Integer(1);
        return (*this);
    }
    Integer operator++(int)
    {
        Integer temp=(*this);
        (*this)+=Integer(1);
        return temp;
    }
    Integer operator--(int)
    {
        Integer temp=(*this);
        (*this)-=Integer(1);
        return temp;
    }
    Integer operator*(Integer x)
    {
        Integer ans;
        reverse(x.s.begin(),x.s.end());
        reverse(s.begin(),s.end());
        long long k=0;
        int ind=0;
        for(int i=0;i<s.size();i++)
        {
            k=0;
            ind=i;
            for(int j=0;j<x.s.size();j++)
            {
                k+=(s[i]-'0')*(x.s[j]-'0');
                if(ans.s.size()<=ind)ans.s+=(k%base)+'0',ind++,k/=base;
                else k+=ans.s[ind]-'0',ans.s[ind]=(k%base)+'0',ind++,k/=base;
            }
            while(k)
            {
                if(ans.s.size()<=ind)ans.s+=(k%base)+'0',ind++,k/=base;
                else k+=ans.s[ind]-'0',ans.s[ind]=(k%base)+'0',ind++,k/=base;
            }
        }
        reverse(s.begin(),s.end());
        ans.base=base;
        ans.sign=!(sign^x.sign);
        ans.set(0);
        return ans;
    }
    Integer operator*=(Integer x)
    {
        return (*this)=(*this)*x;
    }
    template<class T>Integer operator*(T x)
    {
        return (*this)*Integer(x);
    }
    template<class T>Integer operator*=(T x)
    {
        return (*this)*=Integer(x);
    }
    Integer operator/(Integer x)
    {
        Integer d=(*this);
        Integer ans;
        ans.base=base;
        ans.sign=!(sign^x.sign);
        d.sign=true,x.sign=true;
        if(x==0||x>d)return Integer(0);
        Integer util;
        util.s.pop_back();
        ans.s.pop_back();
        int ind=0;
        while(ind<d.s.size()){
            util.s+=d.s[ind++];
            int hi=9,lo=0;
            while(lo<hi)
            {
                int mid=(hi+lo+1)>>1;
                if(x*mid>util)hi=mid-1;
                else lo=mid;
            }
            ans.s+=lo+'0';
            util-=(x*lo);
            if(util.s=="0")
            {
                util.s.pop_back();
            }
        }
        ans.set(1);
        return ans;
    }
    Integer operator/=(Integer x)
    {
        (*this)=(*this)/x;
        return (*this);
    }
    template<class T>Integer operator/(T x)
    {
        return (*this)/Integer(x);
    }
    template<class T>Integer operator/=(T x)
    {
        return (*this)/=Integer(x);
    }
    Integer operator%(Integer x)
    {
        return (*this)-(((*this)/x)*x);
    }
    Integer operator%=(Integer x)
    {
        return (*this)=((*this)%x);
    }
    template<class T>Integer operator%(T x)
    {
        return (*this)%Integer(x);
    }
    template<class T>Integer operator%=(T x)
    {
        return (*this)%=Integer(x);
    }
    Integer gcd(Integer x)
    {
        Integer d=(*this);
        x.sign=true;
        d.sign=true;
        Integer temp;
        while(x>0)
        {
            temp=(d%x);
            d=x;
            x=temp;
        }
        return d;
    }
};
Integer Integer::operator+=(Integer x)
{
    if(sign!=x.sign)
    {
        if(sign)
        {
            x.sign=true;
            (*this)-=x;
        }
        else
        {
            sign=true;
            x-=(*this);
            (*this)=x;
        }
        return (*this);
    }
    long long k=0;
    reverse(x.s.begin(),x.s.end());
    reverse(s.begin(),s.end());
    int i;
    for(i=0;i<min((int)s.size(),(int)x.s.size());i++)
    {
        k+=(s[i]-'0'+x.s[i]-'0');
        s[i]=(k%base)+'0';
        k/=base;
    }
    while(i<(int)s.size())k+=(s[i]-'0'),s[i]=(k%base)+'0',k/=base,i++;
    while(i<(int)x.s.size())k+=x.s[i]-'0',s+=(k%base)+'0',k/=base,i++;
    while(k)s+=(k%base)+'0',k/=base;
    reverse(s.begin(),s.end());
    return (*this);
}
Integer Integer::operator-=(Integer x)
{
    if(sign!=x.sign)
    {
        if(sign)
        {
            x.sign=true;
            (*this)+=x;
        }
        else
        {
            sign=false;
            (*this)+=x;
        }
        return (*this);
    }
    if(!sign)
    {
        sign=true,x.sign=true;
        x-=(*this);
        (*this)=x;
        return (*this);
    }
    if((*this)==x)
    {
        sign=true;
        s="0";
        return (*this);
    }
    if((*this)<x)
    {
        x-=(*this);
        (*this)=x;
        sign=false;
        return (*this);
    }
    long long k=0;
    reverse(x.s.begin(),x.s.end());
    reverse(s.begin(),s.end());
    while(x.s.size()<s.size())x.s+='0';
    int i;
    for(i=0;i<s.size();i++)
    {
        k+=(s[i]-x.s[i]);
        if(k<0)s[i]=(k+base+'0'),k=-1;
        else s[i]=k+'0',k=0;
    }
    set(0);
    return (*this);
}
