struct Tree_iso
{
    vector<vi> adj[2];
    vector<vi> lv[2];
    vector<int> par[2];
    vector<int> val[2];
    vi dg[2];
    int n,rt[2];
    Tree_iso(int _n,int r1=0,int r2=0):n(_n)
    {
        rt[0]=r1-1,rt[1]=r2-1;
        for(int i=0; i<2; i++)
        {
            adj[i].resize(n);
            lv[i].assign(n,vi());
            dg[i].assign(n,0);
            par[i].assign(n,-1);
            val[i].assign(n,0);
        }
    }
    void add_edge(int t,int a,int b)
    {
        a--,b--;
        adj[t][a].push_back(b);
        adj[t][b].push_back(a);
    }
    void dfs(int ind,int t,int p=-1,int d=0)
    {
        lv[t][d].push_back(ind);
        par[t][ind]=p;
        for(auto x:adj[t][ind])
            if(x!=p)
            {
                dfs(x,t,ind,d+1);
                dg[t][ind]++;
            }
    }
    //O(nlogn)
    bool Iso_2_util()
    {
        dfs(rt[0],0);
        dfs(rt[1],1);
        for(int i=n-1; i>=0; i--)
        {
            if(lv[0][i].size()!=lv[1][i].size())
                return false;
            if(lv[0][i].empty())
                continue;
            vector<pair<vi,ii>> v;
            for(int j=0; j<2; j++)
            {
                for(auto x:lv[j][i])
                {
                    v.push_back(make_pair(vi(),ii(x,j)));
                    for(auto y:adj[j][x])
                        if(y!=par[j][x])
                            v.back().fi.push_back(val[j][y]);
                    sort(v.back().fi.begin(),v.back().fi.end());
                }
            }
            sort(v.begin(),v.end());
            int l=0;
            val[v[0].se.se][v[0].se.fi]=0;
            int a[2]= {0};
            a[v[0].se.se]++;
            for(int j=1; j<v.size(); j++)
            {
                if(v[j].fi!=v[j-1].fi)
                {
                    if(a[0]!=a[1])return false;
                    a[0]=a[1]=0;
                    l++;
                }
                val[v[j].se.se][v[j].se.fi]=l;
                a[v[j].se.se]++;
            }
            if(a[0]!=a[1])return false;
        }
        return true;
    }

    //O(n)
    bool Iso_util()
    {
        dfs(rt[0],0);
        dfs(rt[1],1);
        vector<vii> pos(2,vii(n));
        vector<vector<iii>> ls(2*n);
        for(int i=n-1; i>=0; i--)
        {
            if(lv[0][i].size()!=lv[1][i].size())
                return false;
            if(lv[0][i].empty())
                continue;
            vector<iii> buc(1);
            vii v;
            int mx=-1;
            for(int j=0; j<2; j++)
            {
                for(auto x:lv[j][i])
                {
                    for(auto y:adj[j][x])
                        if(y!=par[j][x])
                        {
                            if(ls[val[j][y]].empty()||ls[val[j][y]].back().fi!=ii(x,j))
                                ls[val[j][y]].push_back(iii(ii(x,j),1)),mx=max(mx,val[j][y]);
                            else
                                ls[val[j][y]].back().se++;
                        }
                    pos[j][x]=ii(v.size(),0);
                    v.emplace_back(x,j);
                }
            }
            buc[0].se=v.size();
            for(int j=0; j<=mx; j++)
            {
                vi cn;
                vector<iii> temp;
                for(auto x:ls[j])
                {
                    ii u=pos[x.fi.se][x.fi.fi];
                    dg[v[u.fi].se][v[u.fi].fi]--;
                    x.se--;
                    if(x.se)temp.push_back(x);
                    swap(v[u.fi],v[buc[u.se].fi.se]);
                    swap(pos[x.fi.se][x.fi.fi].fi,pos[v[u.fi].se][v[u.fi].fi].fi);
                    if(buc[u.se].fi.se==buc[u.se].fi.fi)cn.push_back(u.se);
                    buc[u.se].fi.se++;
                }
                ls[j]=temp;
                if(!temp.empty())j--;
                while(!cn.empty())
                {
                    int u=cn.back();
                    cn.pop_back();
                    int l=-1;
                    if(buc[u].se!=buc[u].fi.se)
                    {
                        for(int k=buc[u].fi.fi; k<buc[u].fi.se; k++)pos[v[k].se][v[k].fi].se=buc.size();
                        l=buc.size();
                        buc.push_back(iii(ii(buc[u].fi.fi,buc[u].fi.fi),buc[u].fi.se));
                        buc[u].fi.fi=buc[u].fi.se;
                    }
                    else l=u,buc[u].fi.se=buc[u].fi.fi;
                    if(l!=-1)
                    {
                        for(int k=buc[l].fi.fi; k<buc[l].se; k++)
                        {
                            if(dg[v[k].se][v[k].fi]==0)
                            {
                                swap(v[k],v[buc[l].fi.se]);
                                swap(pos[v[k].se][v[k].fi].fi,pos[v[buc[l].fi.se].se][v[buc[l].fi.se].fi].fi);
                                buc[l].fi.se++;
                            }
                        }
                        if(buc[l].fi.fi==buc[l].fi.se||buc[l].fi.se==buc[l].se)continue;
                        for(int k=buc[l].fi.fi; k<buc[l].fi.se; k++)pos[v[k].se][v[k].fi].se=buc.size();
                        buc.push_back(iii(ii(buc[l].fi.fi,buc[l].fi.fi),buc[l].fi.se));
                        buc[l].fi.fi=buc[l].fi.se;
                    }
                }
            }
            for(int l=0; l<buc.size(); l++)
            {
                int a[2]= {0};
                for(int j=buc[l].fi.fi; j<buc[l].se; j++)val[v[j].se][v[j].fi]=l,a[v[j].se]++;
                if(a[0]!=a[1])return false;
            }
        }
        return true;
    }
    ii dfs2(int ind,vi &pr,int t)
    {
        ii mx=ii(-1,ind);
        for(auto x:adj[t][ind])if(pr[ind]!=x)pr[x]=ind,mx=max(mx,dfs2(x,pr,t));
        mx.fi++;
        return mx;
    }
    void restor(){
        for(int i=0; i<2; i++)
        {
            lv[i].assign(n,vi());
            dg[i].assign(n,0);
            par[i].assign(n,-1);
            val[i].assign(n,0);
        }
    }
    bool ISO(int t=0)
    {
        if(rt[0]==-1||rt[1]==-1)
        {
            vi pr(n,-1);
            ii a=dfs2(0,pr,0);
            pr[a.se]=-1;
            ii b=dfs2(a.se,pr,0);
            vi cn,cn1;
            while(b.se!=-1)cn.push_back(b.se),b.se=pr[b.se];
            pr[0]=-1;
            a=dfs2(0,pr,1);
            pr[a.se]=-1;
            b=dfs2(a.se,pr,1);
            while(b.se!=-1)cn1.push_back(b.se),b.se=pr[b.se];
            if(cn.size()%2!=cn1.size()%2)return false;
            if(cn.size()%2==0)
            {
                rt[0]=cn[cn.size()/2];
                rt[1]=cn1[cn1.size()/2-1];
                if(t&&Iso_2_util())return true;
                else if(!t&&Iso_util())return true;
                restor();

            }
            rt[0]=cn[cn.size()/2];
            rt[1]=cn1[cn1.size()/2];
        }
        if(t&&Iso_2_util())return true;
        else if(!t&&Iso_util())return true;
        return false;
    }
};
int main()
{
    fastread;
    int T=1;
    cin>>T;
    for(int qq=1; qq<=T; qq++)
    {
        int n;
        cin>>n;
        Tree_iso tr(n);
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<n-1; j++)
            {
                int a,b;
                cin>>a>>b;
                tr.add_edge(i,a,b);
            }
        }
        if(tr.ISO())cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}
