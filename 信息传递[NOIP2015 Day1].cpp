#include<cstdio>
#include<cstring>
#include<vector>
#include<stack>
#include<climits>
#define N 200010
using namespace std;
stack<int> S;
vector<int> g[N];
int dfn[N],low[N],cnt,scnt,id[N];
int inde=0,n,m,a[N],f[N];
void Tarjan(int u){
	int minx=dfn[u]=low[u]=++inde;
	int t;
	S.push(u);
	t=a[u];
	if(dfn[t]==-1) Tarjan(t);
	if(low[t]<minx) minx=low[t];
	if(minx<low[u]){
		low[u]=minx; return;
	}
	do
	{
		id[t=S.top()]=scnt;low[t]=n;
		S.pop();
	}while(t!=u);
	scnt++;
}
void Search(int n)
{
	memset(dfn,-1,sizeof dfn);
	memset(id,-1,sizeof id);
	cnt=0;
	scnt=0;
	inde=0;
	for(int i=1;i<=n;i++){
		if(dfn[i]==-1) Tarjan(i);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	Search(n);
	int ans=INT_MAX;
	for(int i=1;i<=n;i++){
		f[id[i]]++;
	}
	for(int i=0;i<scnt;i++){
		if(f[i]>1&&f[i]<ans) ans=f[i];
	}
	printf("%d\n",ans);
	return 0;
}
