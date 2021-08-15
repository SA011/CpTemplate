
//2D SEGMENT TREE
ll st[asz*4][asz*4];
ll ara[asz][asz];
ll f(ll l,ll r)
{
    return l+r;
}
void initX(ll nodeX,ll nodeY,ll ssX,ll sfX,ll ssY,ll sfY)
{
    if(ssX==sfX)
    {
        if(ssY==sfY)
            st[nodeX][nodeY]=ara[ssX][ssY];
        else
            st[nodeX][nodeY]=f(st[nodeX][2*nodeY],st[nodeX][2*nodeY+1]);
        return;
    }
    ll mid=(ssX+sfX)/2;
    initX(2*nodeX,nodeY,ssX,mid,ssY,sfY);
    initX(2*nodeX+1,nodeY,mid+1,sfX,ssY,sfY);
    st[nodeX][nodeY]=f(st[nodeX*2][nodeY],st[nodeX*2+1][nodeY]);
}
void init(ll nodeY,ll ssY,ll sfY,ll n)
{
    if(ssY==sfY)
    {
        initX(1,nodeY,0,n-1,ssY,sfY);
        return;
    }
    ll mid=(ssY+sfY)/2;
    init(2*nodeY,ssY,mid,n);
    init(2*nodeY+1,mid+1,sfY,n);
    initX(1,nodeY,0,n-1,ssY,sfY);
}
void updateX(ll nodeX,ll nodeY,ll ssX,ll sfX,ll ssY,ll sfY,ll posX,ll val)
{
    if(ssX==sfX)
    {
        if(ssY==sfY)
            st[nodeX][nodeY]+=val;
        else
            st[nodeX][nodeY]=f(st[nodeX][2*nodeY],st[nodeX][2*nodeY+1]);
        return;
    }
    ll mid=(ssX+sfX)/2;
    if(posX<=mid)updateX(2*nodeX,nodeY,ssX,mid,ssY,sfY,posX,val);
    else updateX(2*nodeX+1,nodeY,mid+1,sfX,ssY,sfY,posX,val);
    st[nodeX][nodeY]=f(st[nodeX*2][nodeY],st[nodeX*2+1][nodeY]);
}
void update(ll nodeY,ll ssY,ll sfY,ll posX,ll posY,ll val,ll n)
{
    if(ssY==sfY)
    {
        updateX(1,nodeY,0,n-1,ssY,sfY,posX,val);
        return;
    }
    ll mid=(ssY+sfY)/2;
    if(posY<=mid)update(2*nodeY,ssY,mid,posX,posY,val,n);
    else update(2*nodeY+1,mid+1,sfY,posX,posY,val,n);
    updateX(1,nodeY,0,n-1,ssY,sfY,posX,val);
}
ll queryX(ll nodeX,ll nodeY,ll ssX,ll sfX,ll qsX,ll qeX)
{
    if(ssX>qeX||sfX<qsX)return 0;
    if(ssX>=qsX&&sfX<=qeX)return st[nodeX][nodeY];
    ll mid=(ssX+sfX)/2;
    return f(queryX(2*nodeX,nodeY,ssX,mid,qsX,qeX),queryX(2*nodeX+1,nodeY,mid+1,sfX,qsX,qeX));
}
ll query(ll nodeY,ll ssY,ll sfY,ll qsX,ll qeX,ll qsY,ll qeY,ll n)
{
    if(ssY>qeY||sfY<qsY)return 0;
    if(sfY<=qeY&&ssY>=qsY)
    {
        return queryX(1,nodeY,0,n-1,qsX,qeX);
    }

    ll mid=(ssY+sfY)/2;
    return f(query(2*nodeY,ssY,mid,qsX,qeX,qsY,qeY,n),query(2*nodeY+1,mid+1,sfY,qsX,qeX,qsY,qeY,n));
}

