struct vertex{
    int next[26], go[26], p, pch, link, link2;
    vi en;
    vertex(int p = -1, int ch = '$') : p(p), pch(ch){
        link = link2 = -1;
        fill(next, next + 26, -1);
        fill(go, go + 26, -1);
    }
};

vector<vertex> trie(1);
void addString(string &s, int ind)
{
    int v=0;
    for(char ch : s)
    {
        ch -= 'a';
        if(trie[v].next[ch] == -1){
            trie[v].next[ch] = trie.size();
            trie.emplace_back(v, ch + 'a');
        }
        v = trie[v].next[ch];
    }
    trie[v].en.push_back(ind);
}

int go(int v, char ch);

int getLink(int v) {
    if(trie[v].link == -1) {
        if(v == 0 || trie[v].p == 0)
            trie[v].link = 0;
        else
            trie[v].link = go(getLink(trie[v].p), trie[v].pch);
    }
    return trie[v].link;
}

int go(int v, char ch) {
    int c = ch - 'a';
    if(trie[v].go[c] == -1) {
        if(trie[v].next[c] != -1)
            trie[v].go[c] = trie[v].next[c];
        else
            trie[v].go[c] = (v == 0 ? 0 : go(getLink(v), ch));
    }
    return trie[v].go[c];
}
int getLink2(int v){
    if(trie[v].link2 == -1){
        if(v == 0 || !trie[getLink(v)].en.empty())
            trie[v].link2 = trie[v].link;
        else
            trie[v].link2 = getLink2(trie[v].link);
    }
    return trie[v].link2;
}
