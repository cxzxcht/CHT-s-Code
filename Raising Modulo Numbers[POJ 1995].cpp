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
	int tp;
	scanf("%d",&tp);
	while(tp--){
		int m,n,a,b;
		long long ans=0;
		scanf("%d",&m);
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d%d",&a,&b);
			a%=m;
			ans=(ans+quickPow(a,b,m))%m;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
