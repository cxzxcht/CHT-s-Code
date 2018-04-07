#include<bits/stdc++.h>
#define N 410
using namespace std;
bool vx[N],vy[N];
int n,g[N][N],cx[N],cy[N],slack[N],ex[N],ey[N];
bool dfs(int t)
{
	vx[t]=true;
	for(int i=1;i<=n;i++){
		if(vy[i]) continue;
		int gap=ex[t]+ey[i]-g[t][i];
		if(gap==0){
			vy[i]=true;
			if(cy[i]==-1||dfs(cy[i])){
				cx[t]=i;
				cy[i]=t;
				return true;
			}
		} else{
			slack[i]=min(slack[i],gap);
		}
	}
	return false;
}
int KM()
{
	memset(ex,0,sizeof(ex));
	memset(ey,0,sizeof(ey));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ex[i]=max(ex[i],g[i][j]);
		}
	}
	memset(cx,-1,sizeof(cx));
	memset(cy,-1,sizeof(cy));
	for(int i=1;i<=n;i++){
		memset(slack,127,sizeof(slack));
		for(;;){
			memset(vx,false,sizeof(vx));
			memset(vy,false,sizeof(vy));
			if(dfs(i)) break;
			int d=1e9;
			for(int j=1;j<=n;j++){
				if(!vy[j]) d=min(d,slack[j]);
			}
			for(int j=1;j<=n;j++){
				if(vx[j]) ex[j]-=d;
				if(vy[j]) ey[j]+=d;
				else slack[j]-=d;
			}
		}	
	}
	int ret=0;
	for(int i=1;i<=n;i++){
		ret+=g[i][cx[i]];
	}
	return ret;
}
bool dfs2(int t)
{
	vx[t]=true;
	for(int i=1;i<=n;i++){
		if(vy[i]) continue;
		int gap=ex[t]+ey[i]-g[t][i];
		if(gap==0){
			vy[i]=true;
			if(cy[i]==-1||dfs2(cy[i])){
				cx[t]=i;
				cy[i]=t;
				return true;
			}
		} else{
			slack[i]=max(slack[i],gap);
		}
	}
	return false;
}
int KM2()
{
	memset(ex,127,sizeof(ex));
	memset(ey,127,sizeof(ey));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){		
			ex[i]=min(ex[i],g[i][j]);
		}
	}
	memset(cx,-1,sizeof(cx));
	memset(cy,-1,sizeof(cy));
	for(int i=1;i<=n;i++){
		memset(slack,-0x3f,sizeof(slack));
		for(;;){
			memset(vx,false,sizeof(vx));
			memset(vy,false,sizeof(vy));
			if(dfs2(i)) break;
			int d=-2e9;
			for(int j=1;j<=n;j++){
				if(!vy[j]) d=max(d,slack[j]);
			}
			for(int j=1;j<=n;j++){
				if(vx[j]) ex[j]-=d;
				if(vy[j]) ey[j]+=d;
				else slack[j]-=d;
			}
		}	
	}
	int ret=0;
	for(int i=1;i<=n;i++){
		ret+=g[i][cx[i]];
	}
	return ret;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&g[i][j]);
		}
	}
	printf("%d\n",KM2());
	printf("%d\n",KM());
	return 0;
}
