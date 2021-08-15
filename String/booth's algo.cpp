int kmp[asz];
//lexicographically-minimum-string-rotation
int booth(string &s){
    s+=s;
    int ans=0;
    kmp[0]=-1;
    for(int i=1;i<s.size();i++){
        int j=kmp[i-ans-1];
        while(j>=0&&s[i]!=s[ans+j+1]){
            if(s[i]<s[ans+j+1])ans=i-j-1;
            j=kmp[j];
        }
        if(s[i]!=s[ans+j+1]){
            if(s[i]<s[ans])ans=i;
            kmp[i-ans]=-1;
        }
        else kmp[i-ans]=j+1;
    }
    return ans;
}
