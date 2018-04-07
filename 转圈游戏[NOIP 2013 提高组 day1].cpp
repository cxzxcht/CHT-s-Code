#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;

long long quickPow(int a,int p,int m){
	long long ret=1;
	while(p>0){
		if(p&1) ret=(ret*a)%m;
		p>>=1;
		a=a*a%m;
	}
	return ret;
}

int main()
{
	int n,m,x;
	long long k;
	scanf("%d%d%lld%d",&n,&m,&k,&x);
	k=quickPow(10,k,n);
	printf("%lld",(x+m*k)%n);
	return 0;
}
