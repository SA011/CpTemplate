
template <class T> class point
{
public:
	T x,y;
	point(T x1,T y1){
        x=x1;
        y=y1;
	}
	bool operator<(point<T> &b)
	{
	    return (x<b.x||x==b.x&&y<b.y);
	}
};

//IS CLOCKWISE

template<class T> bool cw(point<T> &a,point<T> &b,point<T> &c)
{
	return (b.x-a.x)*(c.y-b.y)-(c.x-b.x)*(b.y-a.y)<0;
}

//IS COUNTER-CLOCKWISE
template<class T> bool ccw(point<T> &a,point<T> &b,point<T> &c)
{
	return (b.x-a.x)*(c.y-b.y)-(c.x-b.x)*(b.y-a.y)>0;
}

//CONVEX_HULL
template<class T> void convex_hull(vector<point<T>> &pol)
{
	if(pol.size()<2)return;
	sort(pol.begin(),pol.end());
	point<T> p1=pol[0],p2=pol.back();
	vector<point<T>>up,down;
	up.push_back(p1),down.push_back(p1);
	for(int i=1;i<(int)pol.size();i++)
	{
		if(i==(int)pol.size()-1||cw(p1,pol[i],p2))
		{
			while(up.size()>=2&&!cw(up[(int)up.size()-2],up.back(),pol[i]))up.pop_back();
			up.push_back(pol[i]);
		}
		if(i==(int)pol.size()-1||ccw(p1,pol[i],p2))
		{
			while(down.size()>=2&&!ccw(down[(int)down.size()-2],down.back(),pol[i]))down.pop_back();
			down.push_back(pol[i]);
		}
	}
	pol.clear();
	for(int i=0;i<up.size();i++)pol.push_back(up[i]);
	for(int i=1;i<down.size();i++)pol.push_back(down[(int)down.size()-i-1]);
}



template <class T> class POINT
{
public:
    T x,y,z;
    const double eps=1e-9;
    POINT(T _x=0,T _y=0,T _z=0)
    {
        x=_x,y=_y,z=_z;
    }
    POINT(POINT<T> &p)
    {
        x=p.x,y=p.y,z=p.z;
    }
    POINT<T> operator+=(POINT<T> p)
    {
        x+=p.x;
        y+=p.y;
        z+=p.z;
        return *this;
    }

    POINT<T> operator-=(POINT<T> p)
    {
        x-=p.x;
        y-=p.y;
        z-=p.z;
        return *this;
    }

    POINT<T> operator+=(T p)
    {
        x+=p;
        y+=p;
        z+=p;
        return *this;
    }

    POINT<T> operator-=(T p)
    {
        x-=p;
        y-=p;
        z-=p;
        return *this;
    }

    POINT<T> operator*=(T p)
    {
        x*=p;
        y*=p;
        z*=p;
        return *this;
    }

    POINT<T> operator/=(T p)
    {
        x/=p;
        y/=p;
        z/=p;
        return *this;
    }
    POINT<T> operator+(POINT<T> p)
    {
        p+=(*this);
        return p;
    }
    POINT<T> operator+(T p)
    {
        POINT<T> t(*this);
        t+=p;
        return t;
    }
    POINT<T> operator-()
    {
        POINT<T> t;
        t.x=-x;
        t.y=-y;
        t.z=-z;
        return t;
    }
    POINT<T> operator-(POINT<T> p)
    {
        return (*this)+(-p);
    }
    POINT<T>& operator-(T p)
    {
        return (*this)+(-p);
    }
    friend ostream& operator<<(ostream& stream,POINT<T> &p)
    {
        stream<<"X: "<<p.x<<", Y: "<<p.y<<", Z: "<<p.z;
        return stream;
    }
    friend istream& operator>>(istream& stream,POINT<T> &p)
    {
        stream>>p.x>>p.y>>p.z;
        return stream;
    }
    POINT<T> operator=(POINT<T> p)
    {
        x=p.x,y=p.y,z=p.z;
        return (*this);
    }
    POINT<T> operator++()
    {
        return (*this)=(*this)+1;
    }
    POINT<T> operator--()
    {
        return (*this)=(*this)-1;
    }
    POINT<T> operator++(int)
    {
        POINT<T> t(*this);
        ++(*this);
        return t;
    }
    POINT<T> operator--(int)
    {
        POINT<T> t(*this);
        --(*this);
        return t;
    }
    POINT<T> operator*(T p)
    {
        POINT<T> t(*this);
        t*=p;
        return t;
    }
    POINT<T> operator/(T p)
    {
        POINT<T> t(*this);
        t/=p;
        return t;
    }
    T dot(POINT<T> p)
    {
        return x*p.x+y*p.y+z*p.z;
    }
    POINT<T> cross(POINT<T> p)
    {
        POINT<T> temp;
        temp.x=(y*p.z-z*p.y);
        temp.y=(z*p.x-x*p.z);
        temp.z=(x*p.y-y*p.x);
        return temp;

    }
    T norm()
    {
        return dot(*this);
    }
    double abs()
    {
        return sqrt(norm());
    }
    double proj(POINT<T> p)
    {
        return (dot(p)/p.abs());
    }
    double angle(POINT<T> p)
    {
        return acos(proj(p)/abs());
    }
    T triple(POINT<T> b,POINT<T> c)
    {
        return dot(b.cross(c));
    }
    POINT<T> divide(POINT<T> p,T n,T m)
    {
        POINT<T> temp(*this);
        temp*=m;
        temp+=(p*n);
        temp/=(n+m);
        return temp;
    }
    bool operator<(POINT<T> p)
    {
        if(abs(p.x-x<eps)&&abs(p.y-y)<eps)return z-p.z>eps;
        if(abs(p.x-x)<eps)return y-p.y>eps;
        return x-p.x>eps;
    }
    bool operator==(POINT<T> p)
    {
        if(abs(p.x-x<eps)&&abs(p.y-y)<eps&&abs(p.z-z)<eps)return 1;
        return false;
    }
    bool operator<=(POINT<T> p)
    {
        return (*this)<p||(*this)==p;
    }
    bool operator>(POINT<T> p)
    {
        return !((*this)<=p);
    }
    bool operator>=(POINT<T> p)
    {
        return !((*this)<p);
    }
    bool operator!=(!POINT<T> p)
    {
        return !((*this)==p);
    }
    double dist(POINT<T> p)
    {
        p-=(*this);
        return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
    }

};
template<class T> class vec
{
    T a,b,c;
    vec()
    {
        a=b=c=0;
    }
    vec(POINT<T> x)
    {
        a=x.x,b=x.y,c=x.z;
    }
    vec(POINT<T> x,POINT<T> y)
    {
        y-=x;
        vec(y);
    }
    vec(vec<T> &x)
    {
        a=x.a,b=x.b,c=x.c;
    }
    vec<T> scale(T y)
    {
        vec<T> temp(*this);
        temp.a*=y,temp.b*=y,temp.c*=y;
        return *this;
    }
    vec<T> cross(vec<T> x)
    {
        vec<T> temp;
        temp.a=(b*x.c-c*x.b);
        temp.b=(c*x.a-a*x.c);
        temp.c=(a*x.b-b*x.a);
        return temp;
    }
    T dot(vec<T> x)
    {
        return a*x.a+b*x.b+c*x.c;
    }
    POINT<T> translate(POINT<T> p,vec<T> v)
    {
        return POINT<T>(p.x+v.a,p.y+v.b,p.z+v.c);
    }
}
