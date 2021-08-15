
ll extended_euclid(ll a,ll b,ll &x,ll &y)
{
    if(a==0)
    {
        x=0,y=1;
        return b;
    }
    ll x1,y1;
    ll ans=extended_euclid(b%a,a,x1,y1);
    x=y1-(b/a)*x1;
    y=x1;
    return ans;
}
//linear diophantite
// All_solution: x=x+k*b/g and y=y-k*a/g;
bool find_solution(ll a,ll b,ll c,ll &x,ll &y,ll &g)
{
    g=extended_euclid(abs(a),abs(b),x,y);
    if(c%g)return false;
    x*=(c/g);
    y*=(c/g);
    if(a<0)x=-x;
    if(b<0)y=-y;
    return true;

}

void shift_sol(ll a,ll b,ll g,ll &x,ll &y,ll k)
{
    x=x+k*b/g;
    y=y-k*a/g;
}
ll find_sol_in_range(ll a,ll b,ll c,ll minx,ll maxx,ll miny,ll maxy)
{
    ll x,y,g;
    if(a==0)
    {
        if(b==0)
        {
            if(c==0)return max(0LL,(maxx-minx+1))*max(0LL,(maxy-miny+1));
            else return 0;
        }
        if(abs(c)%abs(b)==0&&c/b>=miny&&c/b<=maxy)return max(0LL,(maxx-minx+1));
        else return 0;
    }
    else if(b==0)
    {
        if(abs(c)%abs(a)==0&&c/a>=minx&&c/a<=maxx)return max(0LL,(maxy-miny+1));
        else return 0;
    }
    if(!find_solution(a,b,c,x,y,g))return 0;
    a/=g,b/=g;
    ll sign_a=(a>0?1:-1);
    ll sign_b=(b>0?1:-1);
    shift_sol(a,b,1,x,y,(minx-x)/b);
    if(minx>x)shift_sol(a,b,1,x,y,sign_b);
    if (x > maxx)return 0;
    ll lx1 = x;
    shift_sol(a,b,1,x,y,(maxx-x)/b);
    if (x > maxx)shift_sol(a,b,1,x,y,-sign_b);
    ll rx1 = x;
    shift_sol(a,b,1,x,y,-(miny-y)/a);
    if (y < miny)shift_sol(a,b,1,x,y,-sign_a);
    if (y > maxy)return 0;
    ll lx2 = x;
    shift_sol(a,b,1,x,y,-(maxy-y)/a);
    if (y > maxy)shift_sol(a,b,1,x,y,sign_a);
    ll rx2 = x;
    if (lx2 > rx2)swap(lx2, rx2);
    ll lx = max(lx1, lx2);
    ll rx = min(rx1, rx2);
    if (lx > rx)return 0;
    return (rx - lx) / abs(b) + 1;
}
