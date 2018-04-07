#include<cstdio>
#include<cstring>
#define maxn 110
#define rg register
using namespace std;
int ans=0,n,x,y,p[maxn],cx[maxn],cy[maxn];
bool v[maxn],g[maxn][maxn];
bool dfs(int t)
{
	if(t<=0) return false;
	for(int i=1;i<=n;i++)
	if(g[t][i]&&v[i]){
		int &p=i;
		v[p]=false;
		if(cy[p]==-1||dfs(cy[p])){
			cx[t]=p;
			cy[p]=t;
			return true;
		}
	}
	return 0;
}
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++){
			g[i][j]=true;
		}
	}
	while(scanf("%d%d",&x,&y)>0&&x!=0&&y!=0){
		g[x][y]=false;
	}
	memset(cx,-1,sizeof(cx));
	memset(cy,-1,sizeof(cy));
	for(register int i=1;i<=n;i++){
		if(cx[i]==-1){
			memset(v,true,sizeof(v));
			ans+=dfs(i);
		}
	}
	if(ans<n){
		printf("none\n");
		return 0;
	}
	bool flag=true;
	for(rg int i=1;i<=n;i++){
   		int p=cx[i];
		g[i][p]=false;
		cx[i]=-1;
		cy[p]=-1;
		memset(v,true,sizeof(v));
		if(!dfs(i)){
			printf("%d %d\n",i,p);
			flag=false;
			cx[i]=p;
			cy[p]=i;
		}
		g[i][p]=true;
	}
	if(flag) printf("none\n");
	return 0;
}
