#include<bits/stdc++.h>
#define NM 1600
#define N 40
using namespace std;
int n1,n2,m,cx[NM],cy[NM],f[N][N],x,y;
bool v[NM];
vector<int> g[NM];
bool dfs(int k)
{
	if(k<0) return false;
	for(register unsigned int i=0;i<g[k].size();i++)
	if(v[g[k][i]]){
		int &p=g[k][i];
		v[p]=false;
		if(cy[p]==-1||dfs(cy[p])){
			cx[k]=p;
			cy[p]=k;
			return true;
		}
	}
	return 0;
}
bool check(int x)
{
	return f[(x-1)/n2+1][(x-1)%n2+1];
}
int main()
{
	scanf("%d%d%d",&n1,&n2,&m);
	memset(f,true,sizeof(f));
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		f[y][x]=false;
	}
	if((n1*n2-m)&1){
		printf("NO\n");
		return 0;
	}
	int t=0,p=1;
	for(int i=1;i<=n1;i++){
		for(int j=1;j<=n2;j++,p++) if(f[i][j]){
			if(!((i+j)&1)){
				if(j>1&&check(p-1)) 
					g[t].push_back(p-1);
				if(j<n2&&check(p+1)) 
					g[t].push_back(p+1);
				if(i>1&&check(p-n2)) 
					g[t].push_back(p-n2);
				if(i<n1&&check(p+n2)) 
					g[t].push_back(p+n2);
				t++;
			}
		}
	}
/*	for(int i=0;i<t;i++){
		printf("%d ",i);
		for(unsigned int j=0;j<g[i].size();j++){
			printf("%d ",g[i][j]);
		}
		printf("\n");
	}*/
	memset(cx,-1,sizeof(cx));
	memset(cy,-1,sizeof(cy));
	int ans=0;
	for(int i=0;i<t;i++){
		if(cx[i]==-1){
			memset(v,true,sizeof(v));
			ans+=dfs(i);
		}
	}
	if(ans==(n1*n2-m)/2) printf("YES\n");
	else printf("NO\n");
	return 0;
}
