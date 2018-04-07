#include<cstdio>
#include<cstring>
#include<iostream>
#define maxn 40010
using namespace std;
int getint()
{
	char c;
	int p;
	for (c=getchar();(c<'0' || c>'9') && (c!='-');c=getchar());
	if (c=='-')
	{
		c=getchar();
		p=-1;
	}
	else p=1;
	int t=c-48;
	for (c=getchar();c>='0' && c<='9';c=getchar())
		t=t*10+c-48;
	return t*p;
}
int n,m,x,y,v[maxn*2],u,f[maxn][20],first[maxn*2],NEXt[maxn*2],height[maxn*2],
p[maxn*2],Q,l[maxn*2],leng[maxn*2];
int dfs(int root,int father,int h,int le)
{
	height[root]=h;
	l[root]=le;
	f[root][0]=father;
	for(int i=1;(1<<i)<h;i++)
		f[root][i]=f[f[root][i-1]][i-1];
	for(int e=first[root];e!=-1;e=NEXt[e])
		if(v[e]!=father){
			dfs(v[e],root,h+1,le+leng[e]);
		}
	return 0;
}

int LCA(int a,int b)
{
	if(height[a]>height[b]) swap(a,b);
	for(int i=height[b]-height[a],j=0;i>0;i>>=1,j++){
		if(i&1){
			b=f[b][j];
		}
	}
	if(a==b) return a;
	int k;
	for(k=0;(1<<k)<=height[a];k++);
	for(;k>=0;k--){
		if((1<<k)<=height[a] && f[a][k]!=f[b][k]){
			a=f[a][k];
			b=f[b][k];
		}
	}
	return f[a][0];
}

int find(int x)
{
	return (x==p[x] ? x : p[x]=find(p[x]));
}
void Union(int x,int y){
	p[find(x)]=find(y);
}

int main()
{
	n=getint();m=getint();
	memset(first,-1,sizeof(first));
	for(int i=1;i<=n;i++) p[i]=i;
	for(int i=1,e=1;i<=m;i++){
		u=getint();
		v[e]=getint();
		leng[e]=getint();
		if(find(u)!=find(v[e])) Union(u,v[e]);
		NEXt[e]=first[u];
		first[u]=e;
		e++;
		v[e]=u;
		leng[e]=leng[e-1];
		NEXt[e]=first[v[e-1]];
		first[v[e-1]]=e;
		e++;
	}
	memset(f,-1,sizeof(f));
	memset(height,0,sizeof(height));
	height[0]=-1;
	for(register int root=1;root<=n;root++) if(height[root]==0)
		dfs(root,0,1,0);
//	for(int i=1;i<=n;i++){
	//	printf("#%d ",i);
	//	for(int j=0;j<5;j++) printf("%d ",f[i][j]);
	//	printf("%d",l[i]);
	//	puts("");
//	}
	Q=getint();
	for(int i=0;i<Q;i++){
		x=getint();
		y=getint();
		if(find(x)!=find(y)) continue;
		int o=LCA(x,y);
		printf("%d\n",l[x]-l[o]+l[y]-l[o]);
	}
	return 0;
}
