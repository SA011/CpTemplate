

//AHO_CORASICK
char ww[asz];
    ll pos[asz];
    struct vertex
    {
        int next[26],go[26],p=-1,pch,link=-1;
        vi en;
        vertex(int p=-1,int ch='$'):p(p),pch(ch)
        {
            fill(next,next+26,-1);
            fill(go,go+26,-1);
        }
    };

    vector<vertex> trie(1);
    void add_string(string &s,int ind)
    {
        int v=0;
        for(char ch:s)
        {
            ch-='a';
            if(trie[v].next[ch]==-1)
            {
                trie[v].next[ch]=trie.size();
                trie.emplace_back(v,ch+'a');
            }
            v=trie[v].next[ch];
        }
        trie[v].en.push_back(ind);
        pos[ind]=v;
    }

    int go(int v, char ch);

    int get_link(int v) {
        if (trie[v].link == -1) {
            if (v == 0 || trie[v].p == 0)
                trie[v].link = 0;
            else
                trie[v].link = go(get_link(trie[v].p), trie[v].pch);
        }
        return trie[v].link;
    }

    int go(int v, char ch) {
        int c = ch - 'a';
        if (trie[v].go[c] == -1) {
            if (trie[v].next[c] != -1)
                trie[v].go[c] = trie[v].next[c];
            else
                trie[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
        }
        return trie[v].go[c];
    }
    ll num[505],vert[asz];
    void solve(string &s)
    {
        int v=0;
        for(int i=0;i<s.size();i++)
        {
            v=go(v,s[i]);
    //        cout<<v<<endl;
            vert[v]++;
        }
    }
    void dfs(int v)
    {

        for(int i=v;i;i=get_link(i))
            for(int k:trie[i].en)num[k]+=vert[v];
        for(int i=0;i<26;i++)
        {
            if(trie[v].next[i]!=-1)dfs(trie[v].next[i]);
        }
    }
    int main()
    {
        fastread;
        ll T,cs=1;
        scanf("%lld",&T);
        while(T--)
        {
           ll n;
           printf("Case %lld:\n",cs);
            cs++;
            scanf("%lld",&n);
            scanf("%s",ww);
            string s(ww);
//            cout<<"SIZE:: "<<s.size()<<' '<<strlen(ww)<<endl;
            for(int i=0;i<n;i++)
            {
                scanf("%s",ww);

                string t(ww);
//                cout<<"anot: "<<t.size()<<endl;
                num[i]=0;
                add_string(t,i);
            }
            solve(s);
            dfs(0);
            for(int i=0;i<n;i++)printf("%lld\n",num[i]);
            memset(vert,0,sizeof(vert));
            trie.clear();
            trie.emplace_back();
        }
    }



