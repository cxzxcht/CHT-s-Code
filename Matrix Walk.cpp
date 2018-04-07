//codeforces 945C

#include<cstring>
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	vector<int> a(n+10);
	scanf("%d",&a[1]);
	int ans=(1e9+7);
	int maxa=a[1];
//	if(a[1]!=1){
//		puts("NO");
//		return 0;
//	}
	for(int i=2;i<=n;i++){
		scanf("%d",&a[i]);
		maxa=max(maxa,a[i]);
		if(a[i]==a[i-1]){
			puts("NO");
			return 0;
		}
		if(a[i]-a[i-1]==1&&a[i-1]%ans==0){
			puts("NO");
			return 0;
		}
		if(a[i-1]-a[i]==1&&a[i]%ans==0){
			puts("NO");
			return 0;
		}
		if(a[i]-a[i-1]>1){
			if(ans!=a[i]-a[i-1]&&ans!=(1e9+7)){
				puts("NO");
				return 0;
			}
			if(ans==(1e9+7)) ans=a[i]-a[i-1];
		}
		if(a[i-1]-a[i]>1){
			if(ans!=a[i-1]-a[i]&&ans!=(1e9+7)){
				puts("NO");
				return 0;
			}
			if(ans==(1e9+7)) ans=a[i-1]-a[i];
		}
	}
	if(ans==(1e9+7)) ans=maxa;
	if(ans>1e9||ans<1){
		puts("NO");
		return 0;
	}
	printf("YES\n1000000000 %d\n",ans);
	return 0;
}
