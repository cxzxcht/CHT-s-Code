#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#define Mod 1000000007
using namespace std;

long long quickPow(long long a,long long p,long long m){
	long long ret=1;
	while(p>0){
		if(p&1) ret=(ret*a)%m;
		p>>=1;
		a=a*a%m;
	}
	return ret;
}

int m,n,k;

int main()
{
	scanf("%d%d%d",&m,&n,&k);
	long long ans=1;
	vector<pair<long long,long long> > a(k+2);
	long long p=((1ll*m*(m+1))>>1)%Mod;
	for(int i=0;i<k;i++){
		scanf("%lld%lld",&a[i].first,&a[i].second);
	}
	sort(a.begin(),a.begin()+k);
	vector<long long> s;
	s.push_back(a[0].second);
//	printf("%d  %d\n",a[0].first,a[0].second);	
	for(int i=1;i<k;i++){
//		printf("%d  %d\n",a[i].first,a[i].second);
		if(a[i].first!=a[i-1].first){
			s.push_back(a[i].second);
		}
		else{
			if(a[i].second!=a[i-1].second){
				s.back()=(s.back()+a[i].second)%Mod;
			}
		}
	}
	for(unsigned int i=0;i<s.size();i++){
		ans=(ans*(p-s[i]+Mod))%Mod;
//		printf("%lld ",ans);
	}
//	printf("\n");
	printf("%lld\n",(ans*quickPow(p,n-s.size(),Mod))%Mod);
	return 0;
}
