template<class T>
struct SplayNode{
    T value;
    SplayNode<T> *child[2],*parent;
    SplayNode(T _v, SplayNode<T> *p):value(_v){
        child[0]=child[1]=NULL;
        parent=p;
    }
    void rotate(){
        if(parent==NULL)return;
        int u=(parent->child[1]==this);
        if(parent->parent!=NULL){
            int v=(parent->parent->child[1]==parent);
            parent->parent->child[v]=this;
        }
        parent->child[u]=child[u^1];
        if(child[u^1]!=NULL)child[u^1]->parent=parent;
        child[u^1]=parent;
        parent=parent->parent;
        child[u^1]->parent=this;
    }
    void splay(){
        while(parent!=NULL){
            if(parent->parent!=NULL){
                if((parent->parent->child[1]==parent)==(parent->child[1]==this))parent->rotate();
                else rotate();
            }
            rotate();
        }
    }
};
template<class T>
struct SplayTree{
    SplayNode<T> *root;
    size_t size;
    SplayTree(){
        root=NULL;
        size=0;
    }
    void delete_all(SplayNode<T> *t){
        if(t==NULL)return;
        delete_all(t->child[0]);
        delete_all(t->child[1]);
        delete t;
    }
    ~SplayTree(){
        delete_all(root);
    }
    SplayNode<T>* search(T key){
        SplayNode<T>* u=root;
        while(u!=NULL&&u->value!=key){
            SplayNode<T>* v=u->child[u->value<key];
            if(v==NULL)u->splay(),root=u;
            u=v;
        }
        if(u!=NULL)u->splay(),root=u;
        return u;

    }
    void insert(T key){
        if(root==NULL)
            root=new SplayNode<T>(key,NULL),size++;
        SplayNode<T> *u=root;
        while(u->value!=key){
            if(u->child[u->value<key]==NULL)u->child[u->value<key]=root=new SplayNode<T>(key,u),size++;
            u = u->child[u->value<key];
        }
        u->splay();
    }
    bool erase(T key){
        if(search(key)==NULL)return false;
        size--;
        SplayNode<T>* d=root;
        if(root->child[0]==NULL){
            root=root->child[1];
            if(root!=NULL)root->parent=NULL;
            delete d;
            return true;
        }
        if(root->child[1]==NULL){
            root=root->child[0];
            root->parent=NULL;
            delete d;
            return true;
        }
        root=root->child[0];
        root->parent=NULL;
        while(root->child[1]!=NULL)root=root->child[1];
        root->splay();
        SplayNode<T> *t=d;
        d=d->child[1];
        d->parent=NULL;
        delete t;
        while(d->child[0]!=NULL)d=d->child[0];
        d->child[0]=root;
        root->parent=d;
        root->splay();
        return true;
    }
    void inorder(SplayNode<T> *t){
        if(t==NULL)return;
        inorder(t->child[0]);
        cout<<t->value<<' ';
        inorder(t->child[1]);

    }
};
