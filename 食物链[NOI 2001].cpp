#include<bits/stdc++.h>
#define maxn 50010
using namespace std;
int f[maxn*3],n,m,D,x,y;
int find(int x)
{
	return (x==f[x] ? x : f[x]=find(f[x]));
}
void Union(int x,int y){
	f[find(x)]=find(y);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n*3;i++) f[i]=i;
	int ans=0;
	while(m--){
		scanf("%d%d%d",&D,&x,&y);
		if(x>n||y>n||x<1||y<1) {++ans;continue;}
		if(D==2&&(find(x)==find(y)||find(x+n)==find(y)))
		{++ans;continue;}
		if(D==1){
			if(find(x)==find(y+n)||find(x)==find(y+2*n)
			||find(y)==find(x+n)||find(y)==find(x+2*n)
			||find(y+n)==find(x+2*n)||find(y+2*n)==find(x+n)){
				++ans;continue;
			}
			else{
				Union(x,y);
				Union(x+n,y+n);
				Union(x+2*n,y+2*n);
			}
		}
		if(D==2){
			Union(x,y+n);
			Union(x+2*n,y);
			Union(x+n,y+2*n);
		}
	}
	printf("%d\n",ans);
	return 0;
}
