//0 indexed
struct BCC{
    struct node{
        int num, low;
        bool art;
        vector<int> adj,bcc;
        node(){
            num = -1;
            art = 0;
        }
    };
    vector<node> vert;
    vector<vector<int>> B;
    int b_num, n, t;
    vector<pair<int,int>> st;
    BCC(int _n):n(_n){
        vert.resize(n);
        b_num = t = 0;
    }
    void addEdge(int u,int v){
        vert[u].adj.push_back(v);
    }
    void bcc_util(int ind,int p = -1){
        auto &cur = vert[ind];
        cur.num = cur.low = t++;
        int child = 0;
        for(auto x:cur.adj){
            if(vert[x].num == -1){
                child ++;
                st.emplace_back(ind,x);
                bcc_util(x, ind);
                cur.low = min(cur.low, vert[x].low);
                
                if(vert[x].low >= cur.num){
                    B.emplace_back();
                    cur.art = true;
                    pair<int,int> u;
                    do{
                        u = st.back();
                        st.pop_back();
                        if(vert[u.first].bcc.empty() || vert[u.first].bcc.back() != b_num)
                            vert[u.first].bcc.push_back(b_num),B.back().push_back(u.first);
                        if(vert[u.second].bcc.empty() || vert[u.second].bcc.back() != b_num)
                            vert[u.second].bcc.push_back(b_num),B.back().push_back(u.second);
                    }while(u.first != ind || u.second != x);
                    b_num++;
                }
            }else if(x != p && cur.num > vert[x].num){
                //back-edge
                cur.low = min(cur.low, vert[x].num);
                st.emplace_back(ind,x);
            }
        }
        
        if(p == -1)cur.art = child>1;
    }
    void create_bcc(){
        for(int i=0;i<n;i++){
            if(vert[i].num == -1)bcc_util(i);
        }
    }
    vector<vector<int>> compress(){
        create_bcc();
        int cur = b_num;
        vector<vector<int>> ans(b_num);
        for(int i=0;i<n;i++){
            if(vert[i].art || vert[i].bcc.empty()){
                vert[i].bcc.push_back(cur++);
                ans.emplace_back();
            }
            if(vert[i].art){
                for(auto x:vert[i].bcc){
                    if(cur-1 == x)continue;
                    ans[cur-1].push_back(x);
                    ans[x].push_back(cur-1);
                }
            }
        }
        return ans;
    }
};
