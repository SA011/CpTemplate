
struct vertex{
	int link,len;
	int next[26];
	vertex(){
		link = -1;
		len = 0;
		memset(next,-1,sizeof next);
	}
};

vertex sa[N*2];

int last = 0,sz = 1;
void add_char(char c){
	c-='a';
	int cur = sz++;
	sa[cur].len = sa[last].len+1;
	int u = last;
	while(u!=-1&&sa[u].next[c]==-1)sa[u].next[c] = cur, u = sa[u].link;
	if(u==-1)
		sa[cur].link = 0;
	else{
		int v = sa[u].next[c];
		if(sa[u].len+1 == sa[v].len)
			sa[cur].link = v;
		else{
			int nw = sz++;
			sa[nw].link = sa[v].link;
			sa[nw].len = sa[u].len+1;
			memcpy(sa[nw].next,sa[v].next,sizeof sa[v].next);
			while(u!=-1&&sa[u].next[c]==v)
				sa[u].next[c] = nw, u = sa[u].link;
			sa[cur].link = sa[v].link = nw;
		}
	}
	last = cur;
}













struct vertex{
    int link,len;
    map<char,int> next;
    vertex(){
        link=-1,len=0;
    }
};
vertex sa[asz*2];
int last=0,sz=1;
void add_char(char c){
    int cur=sz++;
    sa[cur].len=sa[last].len+1;
    int u=last;
    while(u!=-1&&sa[u].next.count(c)==0){
        sa[u].next[c]=cur;
        u=sa[u].link;
    }
    if(u==-1)
        sa[cur].link=0;
    else{
        int v=sa[u].next[c];
        if(sa[u].len==sa[v].len-1)
            sa[cur].link=v;
        else{
            int nw=sz++;
            sa[nw].link=sa[v].link;
            sa[nw].len=sa[u].len+1;
            sa[nw].next=sa[v].next;
            while(u!=-1&&sa[u].next[c]==v){
                sa[u].next[c]=nw;
                u=sa[u].link;
            }
            sa[v].link=sa[cur].link=nw;
        }
    }
    last=cur;
}

//cnt is the number of instances of an equivalence class //init cnt with 1 except for clones and starting node
//d is the number of instances of an equivalence class being a prefix //to count distinct replace all the cnt with 1
void pre(){
    vector<vector<int>> v(sz+1);
    for(int i=0;i<sz;i++)v[sa[i].len].push_back(i);
    for(int i=sz;i>=0;i--)
        for(auto x:v[i])
        if(x)sa[sa[x].link].cnt+=sa[x].cnt;
    sa[0].cnt=0; //ignoring empty substring
    
    for(int i=sz;i>=0;i--){
        for(auto x:v[i]){
            sa[x].d=sa[x].cnt;
            for(auto u:sa[x].next)sa[x].d+=sa[u.se].d;
        }
    }
}
