#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#define N 10010
using namespace std;
stack<int> S;
vector<int> g[N];
int dfn[N],low[N],cnt,scnt,id[N],f[N];
int inde=0,n,m,x,y;
bool is[N];
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
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) g[i].clear();
	for(int i=0;i<m;i++){
		scanf("%d%d",&x,&y);
		g[x].push_back(y);
	}
	Search(n);
	int sum=0,ans=0;
	memset(f,0,sizeof f);
	memset(is,true,sizeof is);
	for(int i=1;i<=n;i++){
		if(!g[i].empty()){
			for(register unsigned int j=0;j<g[i].size();j++){
				if(id[g[i][j]]!=id[i]){
					is[id[i]]=false;
					break;
				}
			}
		}
		f[id[i]]++;
	}
	for(int i=0;i<scnt;i++){
		if(is[i]){
			sum++;
			ans=i;
		}
	}
	if(sum==1){
		printf("%d\n",f[ans]);
	}
	else printf("0\n");
	return 0;
}
