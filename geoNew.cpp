
using li = long long int;
using ld = long double;
using T = li;
const ld eps = 1e-9;

int ldcmp(ld a) {return abs(a) < eps? 0: (a>0?1:-1);}

struct pt{
    T x,y;
    pt operator+(pt p) {return {x+p.x, y+p.y};}
    pt operator-(pt p) {return {x-p.x, y-p.y};}
    pt operator*(T m) {return {x*m, y*m};}
    pt operator/(T m) {return {x/m, y/m};}
};

bool operator==(pt a, pt b) {return !ldcmp(a.x-b.x) && !ldcmp(a.y-b.y);}
bool operator<(const pt &a, const pt &b) {return a.x == b.x? a.y<b.y : a.x<b.x;}

T norm(pt p) {return p.x*p.x + p.y*p.y;}
ld abs(pt p) {return sqrt((ld)norm(p));}

ostream& operator<<(ostream& os, pt p){
    return os << "(" << p.x << "," << p.y << ")";
}
istream& operator>>(istream& os, pt &p){
    return os >> p.x >> p.y;
}

pt trans(pt p, pt v) {return p + v;}
pt scale(pt p, pt c, ld s) {return (p-c)*s + c;}
pt rot(pt p, pt c, ld ang) {
    return {(p.x-c.x)*cos(ang) - (p.y-c.y)*sin(ang) + c.x, (p.x-c.x)*sin(ang) + (p.y-c.y)*cos(ang) + c.y};
}

T dot(pt a, pt b) {return a.x*b.x + a.y*b.y;}
bool isPerp(pt a, pt b) {return !ldcmp(dot(a,b));}

ld angle(pt a, pt b){ //[0,PI]
    return acos(max((ld)-1.0,min((ld)1.0,(ld)dot(a,b) / abs(a) / abs(b))));
}

T cross(pt a, pt b) {return a.x*b.y - a.y*b.x;}

//orient>0 anti-clock, orient=0 colinear, orient>0 clock
T orient(pt a, pt b, pt c){ return cross(b-a,c-a);}

//is p inside BAC
bool insideAngle(pt a, pt b, pt c, pt p) {
    if(orient(a,b,c) < 0) swap(b,c);
    return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}

//angle BAC [0,2PI]
ld orientedAngle(pt a, pt b, pt c){
    ld k = angle(b-a, c-a);
    if(orient(a, b, c) >= 0) return k;
    return 2*PI - k;
}

bool half(pt p) { return p.y > 0 || p.x < 0 && p.y == 0;}

bool polarCmp(pt a, pt b, pt o = {0,0}){
    return make_tuple(half(a-o), 0, norm(a-o)) < make_tuple(half(b-o), cross(a-o, b-o), norm(b-o));
}


vector<pt> convexHull(vector<pt> v){
    int n = v.size();
    
    if(n <= 2)return v;
    sort(v.begin(), v.end(), [&](pt &a, pt &b){
        return a.x == b.x ? (a.y < b.y) : (a.x < b.x);
    });
    
    vector<pt> upper({v[0],v[1]}), lower({v[0],v[1]});
    
    for(int i = 2; i < n; i++){
        while(upper.size() > 1 && orient(upper[upper.size() - 2], upper.back(), v[i]) <= 0) upper.pop_back();
        while(lower.size() > 1 && orient(lower[lower.size() - 2], lower.back(), v[i]) >= 0) lower.pop_back();
        lower.push_back(v[i]);
        upper.push_back(v[i]);
    }
    upper.pop_back();
    while(upper.size() > 1)lower.push_back(upper.back()), upper.pop_back();
    
    return lower;
    
}


bool pointInConvex(vector<pt> &v, pt &a){
    //v must be sorted in CCW
    int n = v.size();
    if(n == 1)return v[0] == a;
    if(n == 2){
        if(orient(v[0], v[1], a) != 0)return false;
        return !ldcmp(abs(a-v[0]) + abs(v[1]-a) - abs(v[1]-v[0]));
    }
    
    int l = 1, r = n-2;
    while(l < r){
        int mid = (l + r + 1)/2;
        if(orient(v[0], v[mid], a) < 0) r = mid - 1;
        else l = mid;
    }
    
    if(!insideAngle(v[0], v[l], v[l+1], a))return false;
    if(!insideAngle(v[l], v[0], v[l+1], a))return false;
    return true;
}
