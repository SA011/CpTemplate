int kmp[N];
void kmpProcess(string &s){
    int j = -1, n = s.size();
    kmp[0] = -1;
    for(int i = 0; i < n;){
        while(j >= 0 && s[i] != s[j])j = kmp[j];
        j++, i++;
        kmp[i] = j;
    }
}

vector<int> kmpSearch(string &text, string &pat){
    //kmpProcess(pat)
    int j = 0, n = text.size();
    vector<int> ans;
    for(int i = 0; i < n;){
        while(j >= 0 && text[i] != pat[j])j = kmp[j];
        i++, j++;
        if(j == pat.size())ans.push_back(i - j), j = kmp[j];
    }
    return ans;
}
