#include<bits/stdc++.h>
#define maxn 60
using namespace std;
int n,g[maxn][maxn],cx[maxn],cy[maxn],p[maxn],a[maxn];
bool v[maxn];
bool dfs(int t)
{
	if(t<=0) return false;
	if(p[t]&&a[t]) return true;
	for(int i=1;i<=n;i++)
	if(g[t][i]&&v[i]&&p[i]){
		int &q=i;
		v[q]=false;
		if(cy[q]==-1||dfs(cy[q])){
			cx[t]=q;
			cy[q]=t;
			return true;
		}
	}
	return false;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(cx,-1,sizeof(cx));
		memset(cy,-1,sizeof(cy));
		memset(g,0,sizeof(g));
		int sum=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&p[i]);
			if(p[i]==0) sum++;
		}
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				scanf("%d",&g[i][j]);
				if(!p[j]){
					g[i][j]=0;
				}
			}
			g[i][i]=1;
		}
		for(int i=1;i<=n;i++){
			if(p[i]&&(a[i]==0)){
				cx[i]=i;
				cy[i]=i;
			}
		}
		//bool flag=true;
		int ans=0;
		for(int i=1;i<=n;i++){
			if((!p[i])&& cx[i]==-1){
				memset(v,true,sizeof(v));
			//	if(!dfs(i)){
			//		printf("T_T\n");
			//		flag=false;
			//		break;
			//	}
				ans+=dfs(i);
			}
		}
		//if(flag) printf("^_^\n");
		if(ans>=sum) printf("^_^\n");
		else printf("T_T\n");
	}
	return 0;
}
