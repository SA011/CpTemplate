vector<pair<int, int>> manacher(string &s){
    int l = 0, r = -1;
    vector<pair<int, int>> ans;
    for(int i = 0; i < s.size(); i++){
        int k = 1;
        if(i <= r)k = min(ans[r - i + l].first, r - i + 1);
        while(i - k >= 0 && i + k < s.size() && s[i - k] == s[i + k])k++;
        ans.emplace_back(k--, 0);
        if(i + k > r)r = i + k, l = i - k;
    }
    l = 0, r = -1;
    for(int i = 0; i < s.size(); i++){
        int k = 0;
        if(i <= r)k = min(ans[r - i + l + 1].second, r - i + 1);
        while(i - k - 1 >= 0 && i + k < s.size() && s[i - k - 1] == s[i + k])k++;
        ans[i].second = k--;
        if(i + k > r)r = i + k, l = i - k - 1;
    }
    return ans;
}
