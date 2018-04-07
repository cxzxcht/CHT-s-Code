//codeforces 945A

#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	string s;
	cin>>s;
	if(s.length()==1) puts("1");
	else{
		int sum=n;
		bool f=true;
		for(register unsigned int i=1;i<s.length();i++){
			if(s[i]=='U'&&s[i-1]=='R'&&f){
				sum--;
				f=false;
				continue;
			}
			if(s[i]=='R'&&s[i-1]=='U'&&f){
				sum--;
				f=false;
				continue;
			}
			f=true;
		}
		printf("%d\n",sum);
	}
	return 0;
}
