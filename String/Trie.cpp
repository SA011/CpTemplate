struct vertex
{
    int next[26];
    int en; 
    vertex()
    {
        fill(next,next+26,-1);
        en=0;
    }
};
vector<vertex> trie(1);
void add_string(string &s)
{
    int v=0;
    for(char ch:s)
    {
        ch-='a';
        if(trie[v].next[ch]==-1)
        {
            trie[v].next[ch]=trie.size();
            trie.emplace_back();
        }
        v=trie[v].next[ch];
    }
    trie[v].en++;
}
