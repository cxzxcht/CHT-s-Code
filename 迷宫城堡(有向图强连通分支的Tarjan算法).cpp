#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#define N 10010
using namespace std;
stack<int> S;
vector<int> g[N];
int dfn[N],low[N],cnt,scnt,id[N];
int inde=0,n,m,x,y;
void Tarjan(int u){
	int minx=dfn[u]=low[u]=++inde;
	int t;
	S.push(u);
	for(unsigned int i=0;i<g[u].size();i++){
		t=g[u][i];
		if(dfn[t]==-1) Tarjan(t);
		if(low[t]<minx) minx=low[t];
	}
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
	while(scanf("%d%d",&n,&m)>0&&n!=0&&m!=0){
		for(int i=1;i<=n;i++) g[i].clear();
		for(int i=0;i<m;i++){
			scanf("%d%d",&x,&y);
			g[x].push_back(y);
		}
		Search(n);
		bool flag=true;
		for(int i=2;i<=n;i++){
			if(id[i]!=id[1]){
				printf("No\n");
				flag=false;
				break;
			}
		}
		if(flag) printf("Yes\n");
	}
	return 0;
}
