#include<vector>
#include<cstdio>
#include<stack>
#include<cstring>
#include<map>
#include<iostream>
#define N 100010
#define RC 1000010
#define mp make_pair
using namespace std;
const int dd[8][2]={
	{0,-1},{1,0},{0,1},{-1,0},{-1,-1},{1,1},{-1,1},{1,-1}
};
struct Node{
	int p,r,c,type,s;
	Node(){
		p=r=c=type=s=0;
	}
	Node(int p,int r,int c,int type,int s)
	:p(p), r(r), c(c), type(type), s(s) {} 
};
/*
struct Point{
	int p,s;bool ty;
	Point(int p,int s,bool ty)
	:p(p), s(s) ,ty(ty){}
	Point(){
		p=s=0;
		ty=false;
	} 
};*/
map<pair<int,int>,Node> M;
stack<int> S;
vector<int> g[N],G[N];
vector<Node> X[RC],Y[RC];
Node P[N];
int dfn[N],low[N],cnt,scnt,id[N];
int inde=0,n,R,C,x,y,z,d[N],f[N];
bool v[N];
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
void build(Node t)
{
//	if(t.p==1) cout<<"-----"<<endl;
	if(t.type==1){
		for(register unsigned int i=0;i<X[t.r].size();i++){
			g[t.p].push_back(X[t.r][i].p);
		}
	}
	if(t.type==2){
		for(register unsigned int i=0;i<Y[t.c].size();i++){
			g[t.p].push_back(Y[t.c][i].p);
		}
	}
	if(t.type==3){
		for(int i=0;i<8;i++){
			int nx=t.r+dd[i][0],
				ny=t.c+dd[i][1];
			if(M.find(mp(nx,ny))!=M.end()){
				g[t.p].push_back(M[mp(nx,ny)].p);
			}
		}
	}
}
int dp(int t)
{
	if(d[t]) return d[t];
	d[t]=0;
	for(register unsigned int j=0;j<G[t].size();j++){
		d[t]=max(d[t],dp(G[t][j]));
	}
	return d[t]=d[t]+f[t];
}
int main()
{
	scanf("%d%d%d",&n,&R,&C);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&x,&y,&z);
		X[x].push_back(Node(i,x,y,z,1));
		Y[y].push_back(Node(i,x,y,z,1));
		M.insert(mp(mp(x,y),Node(i,x,y,z,1)));
		P[i]=Node(i,x,y,z,1);
	}
/*	for(unsigned int i=0;i<Y[7].size();i++){
		printf("%d ",Y[7][i].p);
	}
	printf("\n");*/
	for(int i=1;i<=n;i++){
		build(P[i]);
	/*	if(i==3){
			for(unsigned int j=0;j<g[i].size();j++){
				printf("%d ",g[i][j]);
			}
			printf("\n");
		}*/
	}
/*	for(int i=1;i<=n;i++){
		for(unsigned int j=0;j<g[i].size();j++){
			printf("%d ",g[i][j]);
		}
		printf("\n");
	}*/
	Search(n);
	for(register int i=1;i<=n;i++){
		f[id[i]]++;
	}
	for(register int i=1;i<=n;i++){
		for(register unsigned int j=0;j<g[i].size();j++){
			int e=g[i][j];
			if(id[e]!=id[i]){
				G[id[i]].push_back(id[e]);
			}
		}
	}
	memset(d,0,sizeof(d));
	memset(v,true,sizeof(v));
	int ans=0;
	for(int i=0;i<scnt;i++){
		if(v[i]) ans=max(ans,dp(i));
	}
	printf("%d\n",ans);
	return 0;
}
