
//Articulation Point and bridge


vi adj[asz];
ll num[asz],low[asz];
ll timer;
//set all num to -1
//count root children to make sure its articulation vertex
void dfs(ll ind,ll par)
{
    num[ind]=low[ind]=timer++;
    for(ll x:adj[ind])
    {
        if(x==par)continue;
        if(num[x]!=-1)low[ind]=min(low[ind],num[x]);
        else
        {
            dfs(x,ind);
            if(low[x]>num[ind])
            {
                cout<<"BRIDGE: "<<ind<<" -> "<<x<<endl;
            }
            if(low[x]>=num[ind])
            {
                cout<<"NODE: "<<ind<<endl;
            }
            low[ind]=min(low[ind],low[x]);
        }
    }
}
