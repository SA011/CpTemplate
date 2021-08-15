struct line{
  ll x,y;     line(ll x=0,ll y=0):x(x),y(y){}
};
bool ccw(line &a,line &b,line &c) {
return (b.x-a.x)*(c.y-b.y)-(c.x-b.x)*(b.y-a.y)>0;
}
vector<line> hull;
void addline(line x){
while(hull.size()>=2&&!ccw(hull[(int)hull.size()
              -2],hull.back(),x))hull.pop_back();
  hull.push_back(x);
}
ll getval(line a,ll x) {  return a.x*x+a.y;  }
ll getmin(ll x){
  if(hull.empty())return LLONG_MAX;
  ll lo=0,hi=hull.size();     hi--;
  while(lo<hi){
    ll mid=(lo+hi)/2;
    if(getval(hull[mid],x)>getval(hull[mid+1],x))
        lo=mid+1;
    else hi=mid;
  }
  return getval(hull[lo],x);
}
