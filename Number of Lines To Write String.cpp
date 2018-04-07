//LeetCode806
class Solution {
public:
    vector<int> numberOfLines(vector<int>& widths, string S) {
        int ans=1,len=0;
        for(register unsigned int i=0;i<S.size();i++){
            if(len+widths[S[i]-'a']<=100) len+=widths[S[i]-'a'];
            else{
                ans++;
                len=widths[S[i]-'a'];
            }
        }
        vector<int> ret;
        ret.push_back(ans);
        ret.push_back(len);
        return ret;
    }
};
