//codeforces 945B

#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	string s;
	cin>>s;
	int sum=0;
	string s1="";
	for(unsigned int i=0;i<s.length()/2+1;i++){
		s1+=s[i];
		string s2="";
		for(unsigned int j=i+1;j<s.length();j++){
			s2+=s[j];
			if(s2==s1){
				sum=max(sum,(int)s2.length());
				break;
			}
		}
	}
	if(sum>0) printf("%d\n",n-sum+1);
	else printf("%d\n",n);
	return 0;
}
