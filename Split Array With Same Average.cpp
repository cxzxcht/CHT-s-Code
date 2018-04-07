#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    long long sum=0;
    bool dfs(vector<int>& A,long long s1,long long s2,int t1,int t2,int curr){
        printf("%d %d %d %d %d\n",s1,t1,s2,t2,curr);
        if(t2==0) return false;
        if(fabs((double)s1/t1-(double)s2/t2)<1e-5){
                    return true;
                }
            bool ret=false;
            for(int i=curr+1;i<A.size();i++){
                cout<<i<<endl;
                ret|=dfs(A,s1+A[i],s2-A[i],t1+1,t2-1,i);
                if(ret) return true;
            }
            return ret;
        }
    bool splitArraySameAverage(vector<int>& A) {
        if(A.size()<2) return false;
        for(unsigned int i=0;i<A.size();i++) sum+=A[i];
        //printf("%d\n",sum);
        //sort(A.begin(),A.end());
        return dfs(A,A[0],sum-A[0],1,A.size()-1,0);
    }
/*    bool dfs(const vector<int>& A,int t,long long s1,long long s2,int t1,int t2){
            if(t>=A.size()){
                if(t1==0||t2==0) return false;
                if(abs((double)s1/t1-(double)s2/t2)<1e-5){
                    return true;
                }
                return false;
            }
            return (dfs(A,t+1,s1+A[t],s2,t1+1,t2)||dfs(A,t+1,s1,s2+A[t],t1,t2+1));
        }
    bool splitArraySameAverage(vector<int>& A) {
        if(A.size()<2) return false;
      //  sort(A.begin(),A.end());
        return dfs(A,1,A[0],0,1,0);
    }*/
};
//void trimLeftTrailingSpaces(string &input) {
//    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
//        return !isspace(ch);
//    }));
//}

//void trimRightTrailingSpaces(string &input) {
//    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
//        return !isspace(ch);
//    }).base(), input.end());
//}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

string boolToString(bool input) {
    return input ? "True" : "False";
}

int main() {
    string line;
    while (getline(cin, line)) {
        vector<int> A = stringToIntegerVector(line);
        
        bool ret = Solution().splitArraySameAverage(A);

        string out = boolToString(ret);
        cout << out << endl;
    }
    return 0;
}
