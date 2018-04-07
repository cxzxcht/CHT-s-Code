#include<bits/stdc++.h>
#define maxn 1010
using namespace std;
vector<int> g[maxn];
int n1,n2,m,x,y,cx[maxn],cy[maxn];
bool v[maxn];
bool dfs(int t)
{
	if(t<=0) return false;
	for(register unsigned int i=0;i<g[t].size();i++)
	if(v[g[t][i]]){
		int &p=g[t][i];
		v[p]=false;
		if(cy[p]==0||dfs(cy[p])){
			cx[t]=p;
			cy[p]=t;
			return true;
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d%d",&n1,&n2,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d",&x,&y);
		if(y>n2) continue;
		g[x].push_back(y);
	}
	int ans=0;
	memset(cy,0,sizeof(cy));
	memset(cx,0,sizeof(cx));
	for(int i=1;i<=n1;i++)
	if(cx[i]==0){
		memset(v,true,sizeof(v));
		ans+=dfs(i);
	}
	printf("%d\n",ans);
//	for(int i=1;i<=n1;i++) printf("%d ",cx[i]);
//	printf("\n");
	return 0;
}
