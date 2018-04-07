#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	int l=0,r=2e9;
	while(l<r){
		int mid=(l+r)>>1;
		if(floor(mid*log10(mid))+1<n) l=mid+1;
		else r=mid; 
	}
	printf("%d\n",r);
	return 0;
}
