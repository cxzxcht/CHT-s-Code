#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#define N 110
using namespace std;
stack<int> S;
vector<int> g[N];
int dfn[N],low[N],cnt,scnt,id[N];
int inde=0,n,x;
bool f[N],d[N];
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
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		while(scanf("%d",&x) && x!=0)
			g[i].push_back(x);
	}
	Search(n);
	memset(f,true,sizeof f);
	memset(d,true,sizeof(d));
	int sum1=0,sum2=0;
	for(int i=1;i<=n;i++){
		for(register unsigned int j=0;j<g[i].size();j++){
			if(id[i]!=id[g[i][j]]){
				f[id[g[i][j]]]=false;
				d[id[i]]=false;
			}
		}
	}
	for(int i=0;i<scnt;i++){
		sum1+=f[i];
		sum2+=d[i];
	}
	printf("%d\n",sum1);
	if(scnt>1) printf("%d\n",max(sum1,sum2));
	else printf("0\n");
	return 0;
}
