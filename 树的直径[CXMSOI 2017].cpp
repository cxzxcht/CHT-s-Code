#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define N 10010
#define M 10010
using namespace std;

struct Edge{
	int from,to,dist,ne;
	Edge():from(0),to(0),dist(0),ne(0){}
	Edge(int from,int to,int dist,int ne)
		:from(from),to(to),dist(dist),ne(ne){}
};

int p,maxd,cnt=0,x,y,z;
int g[N];
Edge e[M*2];

void DFS(int t,int f,int father){
	if(f>maxd){
		maxd=f;
		p=t;
	}
	for(int i=g[t];i!=-1;i=e[i].ne)
	if(e[i].to!=father){
		DFS(e[i].to,f+e[i].dist,t);
	}
}

int main()
{
	memset(g,-1,sizeof g);
	cnt=0;
	while(scanf("%d%d%d",&x,&y,&z)>0){
		e[cnt]=Edge(x,y,z,g[x]);
		g[x]=cnt++;
		e[cnt]=Edge(y,x,z,g[y]);
		g[y]=cnt++;
	}
	maxd=0;
	p=-1;
	DFS(1,0,0);
	if(p>0){
		DFS(p,0,0);
	}
	printf("%d\n",maxd);
	return 0;
}
