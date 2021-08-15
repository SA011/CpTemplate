struct LinkCutTree{
    struct SplayNode{
        int value,sub,sub_val,parent,path_parent,lazy,child[2];
        bool rev;
        SplayNode(int _val=0):value(_val){
            sub=1;
            sub_val=_val;
            parent=path_parent=lazy=rev=0;
            child[0]=child[1]=0;
        }
    };

    vector<SplayNode> Nodes;
    LinkCutTree(int n){
        Nodes.resize(n+1);
    }
    int side(int u){
        return Nodes[Nodes[u].parent].child[1]==u;
    }
    void propagate(int u){
        if(!u)return;
        Nodes[u].value+=Nodes[u].lazy;
        Nodes[u].sub_val+=Nodes[u].lazy*Nodes[u].sub;
        int &l=Nodes[u].child[0];
        int &r=Nodes[u].child[1];
        if(Nodes[u].rev)swap(l,r);
        if(l)Nodes[l].lazy+=Nodes[u].lazy,Nodes[l].rev^=Nodes[u].rev;
        if(r)Nodes[r].lazy+=Nodes[u].lazy,Nodes[r].rev^=Nodes[u].rev;
        Nodes[u].lazy=Nodes[u].rev=0;
    }
    void combine(int u){
        propagate(Nodes[u].child[0]);
        propagate(Nodes[u].child[1]);
        Nodes[u].sub=1;
        Nodes[u].sub_val=Nodes[u].value;
        if(Nodes[u].child[0])Nodes[u].sub+=Nodes[Nodes[u].child[0]].sub,Nodes[u].sub_val+=Nodes[Nodes[u].child[0]].sub_val;
        if(Nodes[u].child[1])Nodes[u].sub+=Nodes[Nodes[u].child[1]].sub,Nodes[u].sub_val+=Nodes[Nodes[u].child[1]].sub_val;
    }
    void setChild(int u,int d,int v){
        Nodes[u].child[d]=v;
        combine(u);
        if(v)Nodes[v].parent=u;
    }
    void rotate(int u){
        if(Nodes[u].parent==0)return;
        int p=Nodes[u].parent,pp=Nodes[p].parent;
        swap(Nodes[u].path_parent,Nodes[p].path_parent);
        int x=side(p),y=side(u);
        setChild(pp,x,u);
        setChild(p,y,Nodes[u].child[y^1]);
        setChild(u,y^1,p);
    }
    void splay(int u){
        propagate(u);
        while(Nodes[u].parent){
            int p=Nodes[u].parent;
            int pp=Nodes[p].parent;
            propagate(pp),propagate(p),propagate(u);
            if(pp)rotate(side(p)==side(u)?p:u);
            rotate(u);
        }
    }
    void detach(int u){
        if(Nodes[u].child[1]){
            Nodes[Nodes[u].child[1]].parent=0;
            Nodes[Nodes[u].child[1]].path_parent=u;
            setChild(u,1,0);
        }
    }
    int access(int u){
        splay(u);
        detach(u);
        int par=u;
        while(Nodes[u].path_parent){
            par=Nodes[u].path_parent;
            splay(par);
            detach(par);
            setChild(par,1,u);
            Nodes[u].path_parent=0;
            splay(u);
        }
        return par;
    }
    void makeRoot(int u){
        access(u);
        int l=Nodes[u].child[0];
        Nodes[l].rev^=1;
        swap(Nodes[l].parent,Nodes[l].path_parent);
        setChild(u,0,0);
    }
    int findRoot(int u){
        access(u);
        propagate(u);
        while(Nodes[u].child[0])u=Nodes[u].child[0],propagate(u);
        splay(u);
        return u;
    }
    bool connected(int u,int v){
        if(u==v)return true;
        makeRoot(u);
        access(v);
        splay(u);
        return Nodes[v].parent==u||Nodes[Nodes[v].parent].parent==u;
    }
    int lca(int u,int v){
        if(!connected(u,v))return 0;
        access(u);
        return access(v);
    }
    void link(int u,int v){
        makeRoot(v);
        Nodes[v].path_parent=u;
    }
    void cut(int u,int v){
       makeRoot(u);
       access(u);
       splay(v);
       Nodes[v].path_parent=0;
    }
    void update(int u,int v,int w){
        makeRoot(u),access(v);
        Nodes[v].lazy+=w;
    }
    int query(int u,int v){
        makeRoot(u),access(v);
        return Nodes[v].sub_val;
    }
};
