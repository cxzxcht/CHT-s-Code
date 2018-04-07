#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<vector>
#include<cstdlib>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<list>
#include<ctime>
#include<string>
#include<sstream>
#include<fstream>
#include<cmath>
#include<climits>
#define N 1000005
using namespace std;

inline int getint()
{
	char ch;
	int p=0,t;
	for(ch=getchar();ch!='-' && !isdigit(ch);ch=getchar());
	if(ch=='-'){
		t=-1;
	}
	else{
		t=1;
	}
	for(;!isdigit(ch);ch=getchar());
	for(;isdigit(ch);ch=getchar()){
		p=p*10+ch-48;
	}
	return t*p;
}

long long n,a[N];

int main()
{
	while(scanf("%lld",&n)>0){
		for(int i=1;i<=n;i++){
			a[i]=getint();
		}
		sort(a+1,a+1+n);
		long long m=(n*(n-1)/2+1)/2;
		long long l,r,mid,num;
		register long long j;
		l=0;
		r=a[n];
        while (l<r){
			j=1;
			num=0;
			mid=(l+r)>>1;
			for (int i=2;i<=n;i++){
				while(a[i]-a[j]>mid)
					j++;
				num+=i-j;
			}
			if (num<m)
				l=mid+1;
			else
				r=mid;
        }
		cout<<l<<endl;
	}
	return 0;
}
