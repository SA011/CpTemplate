namespace Geo
{
const double eps=1e-9,inf=1e30;
template <class T> class POINT
{
public:
    T x,y,z;
    POINT(T _x=0,T _y=0,T _z=0):x(_x),y(_y),z(_z) {}
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
    POINT<T> operator-(T p)
    {
        return (*this)+(-p);
    }
    friend ostream& operator<<(ostream& stream,POINT<T> &p)
    {
        stream<<"{"<<p.x<<", "<<p.y<<", "<<p.z<<"}";
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
    } POINT<T> operator--(int)
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
    double val()
    {
        return sqrt(norm());
    }
    double proj(POINT<T> p)
    {
        return (dot(p)/p.val());
    }
    double angle(POINT<T> p)
    {
        return acos(proj(p)/val());
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
    friend bool operator<(POINT<T> p2,POINT<T> p)
    {
        if(abs(p.x-p2.x<eps)&&abs(p.y-p2.y)<eps)return p2.z<p.z;
        if(abs(p.x-p2.x)<eps)return p2.y<p.y;
        return p2.x<p.x;
    }
    friend bool operator==(POINT<T> p2,POINT<T> p)
    {
        return abs(p.x-p2.x)<eps&&abs(p.y-p2.y)<eps&&abs(p.z-p2.z)<eps;
    }
    friend bool operator<=(POINT<T> p2,POINT<T> p)
    {
        return p2<p||p2==p;
    }
    friend bool operator>(POINT<T> p2,POINT<T> p)
    {
        return !(p2<=p);
    }
    friend bool operator>=(POINT<T> p2,POINT<T> p)
    {
        return !(p2<p);
    }
    friend bool operator!=(POINT<T> p2,POINT<T> p)
    {
        return !(p2==p);
    }
    double dist(POINT<T> p)
    {
        p-=(*this);
        return sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
    }
    bool cw(POINT<T> a,POINT<T> b)
    {
        return (a-*this).cross(b-*this).z<0;
    }
    bool ccw(POINT<T> a,POINT<T> b)
    {
        return (a-*this).cross(b-*this).z>0;
    }
    bool colinear(POINT<T> a,POINT<T> b)
    {
        return abs((a-*this).cross(b-*this).z)<eps;
    }
};
template<class T> class Line
{
public:
    T a,b,c;
    void adj()
    {
        if(abs(b)>eps)a/=b,c/=b,b/=b;
        else if(abs(a)>eps)b/=a,c/=a,a/=a;
    }

    T get_m()
    {
        if(abs(b)<eps)return inf;
        return -a/b;
    }

    T get_c()
    {
        if(abs(b)<eps)return inf;
        return -c/b;
    }

    Line(T _a=0,T _b=0,T _c=0):a(_a),b(_b),c(_c)
    {
        adj();
    }

    Line(POINT<T> p1,POINT<T> p2)
    {
        b=p1.x-p2.x;
        a=p2.y-p1.y;
        c=(p1.y-p2.y)*p1.x-(p1.x-p2.x)*p1.y;
        adj();
    }
    Line(POINT<T> p1,T m)
    {
        b=1.0,a=-m,c=p1.x*m-p1.y;
        adj();
    }
    T angle(Line l)
    {
        T x=abs(b*l.b-a*l.a);
        if(x<eps)return PI/2;
        return atan(abs(b*l.a-a*l.b)/x);
    }
    bool is_parallel(Line l)
    {
        return abs(a*l.b-b*l.a)<eps;
    }
    bool is_same(Line l)
    {
        return is_parallel(l)&&abs(c*l.b-b*l.c)<eps;
    }
    bool intersect(Line l,POINT<T> &p)
    {
        if(is_parallel(l))return false;
        T d=a*l.b-b*l.a;
        p.x=(b*l.c-l.b*c)/d;
        p.y=(l.a*c-a*l.c)/d;
        return true;
    }
    T val(POINT<T> p)
    {
        return a*p.x+b*p.y+c;
    }
    bool is_on_the_line(POINT<T> p)
    {
        return abs(val(p))<eps;
    }
    T dist_to_point(POINT<T> p,POINT<T> &x)
    {
        Line temp(b,-a,0);
        temp.c=-temp.val(p);
        intersect(temp,x);
        return p.dist(x);
    }
    T dist_to_line(Line l)
    {
        if(!is_parallel(l))return 0;
        return abs(c-l.c)/hypot(a,b);
    }
    bool points_r_away(POINT<T> cen,POINT<T> &p1,POINT<T> &p2,T r)
    {
        if(!is_on_the_line(cen))
        {
            POINT<T> cen2;
            T a=dist_to_point(cen,cen2);
            if(a>r)return false;
            return points_r_away(cen2,p1,p2,sqrt(r*r-a*a));
        }
        T a=atan(get_m());
        p1.x=cen.x-cos(a)*r;
        p1.y=cen.x-sin(a)*r;
        p2.x=cen.x+cos(a)*r;
        p2.y=cen.x+sin(a)*r;
        return true;
    }
    friend bool operator<(Line<T> l2,Line<T> l)
    {
        if(abs(l.a-l2.a<eps)&&abs(l.b-l2.b)<eps)return l2.c<l.c;
        if(abs(l.a-l2.a)<eps)return l2.b<l.b;
        return l2.a<l.a;
    }
    friend bool operator==(Line<T> l2,Line<T> l)
    {
        return (abs(l.a-l2.a)<eps&&abs(l.b-l2.b)<eps&&abs(l.c-l2.c)<eps);
    }
    friend bool operator<=(Line<T> l2,Line<T> l)
    {
        return l2<l||l2==l;
    }
    friend bool operator>(Line<T> l2,Line<T> l)
    {
        return !(l2<=l);
    }
    friend bool operator>=(Line<T> l2,Line<T> l)
    {
        return !(l2<l);
    }
    friend bool operator!=(Line<T> l2,Line<T> l)
    {
        return !(l2==l);
    }
    friend ostream& operator<<(ostream& stream,Line<T> &l)
    {
        stream<<"{"<<l.a<<", "<<l.b<<", "<<l.c<<"}";
        return stream;
    }
    friend istream& operator>>(istream& stream,Line &l)
    {
        stream>>l.a>>l.b>>l.c;
        l.adj();
        return stream;
    }
};
template<class T> class LineSegment
{
public:
    POINT<T> s,f;
    LineSegment() {}
    LineSegment(POINT<T> p1,POINT<T> p2):s(p1),f(p2) {}
    T dist_to_point(POINT<T> p,POINT<T> &x)
    {
        if(s==f)
        {
            x=s;
            return p.dist(x);
        }
        T u=(f-s).dot(p-s)/(f-s).norm();
        if(u<0)x=s;
        else if(u>1)x=f;
        else x=s+(f-s)*u;
        return p.dist(x);
    }
    int intersect(LineSegment<T> l,POINT<T> &p1,POINT<T> &p2)
    {
        Line<T> l1(s,f),l2(l.s,l.f);
        if(l1.is_same(l2))
        {
            T a=dist_to_point(l.s,p1);
            T b=dist_to_point(l.f,p2);
            if(abs(a)>eps&&abs(b)>eps)return 0;
            return 2;
        }
        if(!l1.intersect(l2,p1))return 0;
        if(abs(dist_to_point(p1,p2))>eps)return 0;
        if(abs(l.dist_to_point(p1,p2))>eps)return 0;
        return 1;
    }
};
template<class T> class Circle
{
    const double eps=1e-9;
    const double pi=acos(-1);
public:
    POINT<T> cen;
    T rad=0;
    Circle(POINT<T> c,T r=0):cen(c),rad(r) {}
    Circle() {}
    T area()
    {
        return pi*rad*rad;
    }
    int position_of_point(POINT<T> p)
    {
        //-1=Inside the circle, 0=on the circle, 1=outside the circle
        T a=hypot(p.x-cen.x,p.y-cen.y);
        if(a>rad)return 1;
        if(a<rad)return -1;
        return 0;
    }
    int LineIntersect(Line<T> l,POINT<T> &p1,POINT<T> &p2)
    {
        if(!l.points_r_away(cen,p1,p2,rad))return 0;
        if(p1==p2)return 1;
        return 2;
    }
    Line<T> CommonChord(Circle<T> C){
        T a=2*(cen.x-C.cen.x);
        T b=2*(cen.y-C.cen.y);
        T c=C.cen.x*C.cen.x+C.cen.y*C.cen.y-cen.x*cen.x-cen.y*cen.y+rad*rad-C.rad*C.rad;
        return Line<T>(a,b,c);
    }
    int CircleIntersect(Circle<T> C,POINT<T> &p1,POINT<T> &p2){
        return LineIntersect(CommonChord(C),p1,p2);
    }
};
template<class T> class Polygon:public vector<POINT<T>>
{
public:
    T area()
    {
        T a=0;
        for(int i=0; i<this->size(); i++)a+=(*this)[i].x*(*this)[(i+1)%this->size()].y-(*this)[i].y*(*this)[(i+1)%this->size()].x;
        return a;
    }
    Polygon<T> convex_hull()
    {
        Polygon<T> temp(*this);
        sort(temp.begin(),temp.end());
        if(temp.size()<2)return temp;
        POINT<T> p1=temp[0],p2=temp.back();
        Polygon<T> up,down;
        up.push_back(p1);
        down.push_back(p1);
        for(int i=1; i<temp.size(); i++)
        {
            if(i+1==temp.size()||temp[i].cw(p1,p2))
            {
                while(up.size()>1&&!up.back().cw(up[up.size()-2],temp[i]))up.pop_back();
                up.push_back(temp[i]);
            }
            if(i+1==temp.size()||temp[i].ccw(p1,p2))
            {
                while(down.size()>1&&!down.back().ccw(down[down.size()-2],temp[i]))down.pop_back();
                down.push_back(temp[i]);
            }
        }
        temp.clear();
        for(auto x:up)temp.push_back(x);
        for(int i=down.size()-2; i>0; i--)temp.push_back(down[i]);
        return temp;
    }
    bool pointInTriangle(POINT<T> p,int l = 0){
    	if(this->size()<3||l>=this->size()||l<0)return false;
    	Polygon<T> &ref = *this;
    	for(int i=0;i<2;i++)if(ref[(i+l)%ref.size()].cw(ref[(i+l+1)%ref.size()],p))return false;
    	return !ref[(l+2)%ref.size()].cw(ref[l],p);
    }
    bool isPointInside(POINT<T> p){
    	Polygon<T> &ref = *this;
        if(this->size()<1)return false;
        if(this->size() == 1)return ref[0] == p;
        POINT<T> garb;
        if(this->size() == 2){
            return LineSegment<T>(ref[0],ref[1]).dist_to_point(p,garb)<eps;
        }

        int l = 1,r = this->size()-1;
        while(r-l>1){
            int mid = (l+r)/2;
            if(ref[0].cw(ref[mid],p))r = mid;
            else l = mid;
        }
        if(l == r){
            return LineSegment<T>(ref[0],ref[l]).dist_to_point(p,garb)<eps;
        }
        return pointInTriangle(p,l);
    }
};
};
