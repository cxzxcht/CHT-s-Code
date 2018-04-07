#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <queue>
#define N 510
using namespace std;
struct Edge{
	int v,cost;
	Edge(){
		v=cost=0;
	}
	Edge(int _v,int _cost){
		v=_v;
		cost=_cost;
	}
};
stack<int> S;
vector<Edge> g[N];
int dfn[N],low[N],cnt,scnt,id[N],d[N];
int inde=0,n,m,x,y,z,k,G[N][N];
bool vis[N];
void Tarjan(int u){
	int minx=dfn[u]=low[u]=++inde;
	int t;
	S.push(u);
	for(unsigned int i=0;i<g[u].size();i++){
		t=g[u][i].v;
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
	memset(low,0,sizeof(low));
	while(!S.empty()) S.pop();
	cnt=0;
	scnt=0;
	inde=0;
	for(int i=1;i<=n;i++){
		if(dfn[i]==-1) Tarjan(i);
	}
}
void build()
{
	memset(G,63,sizeof G);
	for(register int i=1;i<=n;i++){
		for(register unsigned int j=0;j<g[i].size();j++){
			int e=g[i][j].v;
			if(id[e]!=id[i]){
				G[id[i]][id[e]]=min(G[id[i]][id[e]],g[i][j].cost);
			}
		}
	}
}
/*void floyd()
{
	for(register int k=0;k<scnt;k++){
		for(register int i=0;i<scnt;i++){
			for(register int j=0;j<scnt;j++){
				if(i!=j&&j!=k&&i!=k){
					d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
				}
			}
		}
	}
}*/
void SPFA(int s)
{
	memset(d,63,sizeof d);
	memset(vis,true,sizeof(vis));
	queue<int> q;
	q.push(s);
	d[s]=0;
	vis[s]=false;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		vis[x]=true;
		for(int i=0;i<scnt;i++) if(G[x][i]<1e9&&d[i]>d[x]+G[x][i]){
			d[i]=d[x]+G[x][i];
			if(vis[i]){
				vis[i]=false;
				q.push(i);
			}
		}
	}
}
int main()
{
	while(scanf("%d%d",&n,&m)>0&&n!=0){
		for(int i=1;i<=n;i++) g[i].clear();
		for(int i=0;i<m;i++){
			scanf("%d%d%d",&x,&y,&z);
			g[x].push_back(Edge(y,z));
		}
		Search(n);
		build();
	//	floyd();
		scanf("%d",&k);
		for(int i=0;i<k;i++){
			scanf("%d%d",&x,&y);
			if(id[x]==id[y]){
				puts("0");
				continue;
			}
			SPFA(id[x]);
			int sum=d[id[y]];
			if(sum>1e9) puts("Nao e possivel entregar a carta");
			else printf("%d\n",sum);
		}
		printf("\n");
	}
	return 0;
}
