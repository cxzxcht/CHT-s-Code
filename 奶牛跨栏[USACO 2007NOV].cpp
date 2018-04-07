#include<bits/stdc++.h>
#define maxn 310
using namespace std;
int n,m,t,x,y,z,g[maxn][maxn],d[maxn][maxn],s,p;
void floyd()
{
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)
			if(i!=j&&j!=k&&i!=k){
				d[i][j]=min(d[i][j],max(d[i][k],d[k][j]));
			}
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&t);
	memset(g,101,sizeof(g));
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&x,&y,&z);
		g[x][y]=z;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			d[i][j]=g[i][j];
		}
	}
	floyd();
	for(int i=0;i<t;i++){
		scanf("%d%d",&s,&p);
		if(d[s][p]<1e7) printf("%d\n",d[s][p]);
		else printf("-1\n");
	}
	return 0;
}
