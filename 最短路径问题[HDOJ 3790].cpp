#include<bits/stdc++.h>
#define maxn 1010
using namespace std;
int n,m,d1[maxn],d2[maxn],x1,x2,x3,x4,s,t;
bool f[maxn];
struct Edge{
	int to,d,p;
	Edge(){
		to=d=p=0;
	}
	Edge(int _to,int _d,int _p){
		to=_to;
		d=_d;
		p=_p;
	}
};
vector<Edge> g[maxn];
void SPFA()
{
	memset(f,false,sizeof(f));
	memset(d1,127,sizeof(d1));
	memset(d2,127,sizeof(d2));
//	memset(num,0,sizeof(num));
	queue<int> q;
	q.push(s);
	f[s]=true;
	d1[s]=0;
	d2[s]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		f[x]=false;
		for(register unsigned int i=0;i<g[x].size();i++){
			bool fl=false;
			if(d1[x]+g[x][i].d<d1[g[x][i].to]||(d1[x]+g[x][i].d==d1[g[x][i].to]&&d2[x]+g[x][i].p<d2[g[x][i].to])){
				d1[g[x][i].to]=d1[x]+g[x][i].d;
				d2[g[x][i].to]=d2[x]+g[x][i].p;
			//	++num[g[x][i].to];
				fl=true;
			}
	/*		else
			if(d1[x]+g[x][i].d==d1[g[x][i].to]&&d2[x]+g[x][i].p<d2[g[x][i].to]){
				d2[g[x][i].to]=d2[x]+g[x][i].p;
				fl=true;
			}*/
			if(fl && !f[g[x][i].to]){
				f[g[x][i].to]=true;
				q.push(g[x][i].to);
			}
		}
	}
}
int main()
{
	while(scanf("%d%d",&n,&m)>0&&(n!=0||m!=0)){
		for(int i=0;i<m;i++){
			scanf("%d%d%d%d",&x1,&x2,&x3,&x4);
			g[x1].push_back(Edge(x2,x3,x4));
			g[x2].push_back(Edge(x1,x3,x4));
		}
		scanf("%d%d",&s,&t);
		SPFA();
		printf("%d %d\n",d1[t],d2[t]);
	}
	return 0;
}
