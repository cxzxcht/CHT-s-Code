#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#define N 50010
using namespace std;
int n,minx,x[N*3],y[N*3],a[N*3],z[N*3];
struct CartesianTree{
	int st[N],T[N],lc[N],rc[N],top;
	CartesianTree(){
		memset(st,0,sizeof st);
		memset(T,0,sizeof T);
		top=-1;
	}
	void build(int A[N]){
		CartesianTree();
		int k;
		for(int i=0;i<=150000;i++) if(a[i]>-2e9){
			k=top;
			while(k>=0&&A[st[k]]>A[i]) k--;
			if(k!=-1){
				T[z[i]]=z[st[k]];
				rc[z[st[k]]]=z[i];
			}
			if(k<top){
				T[z[st[k+1]]]=z[i];
				lc[z[i]]=z[st[k+1]];
			}
			st[++k]=i;
			top=k;
//			printf("#%d:\n",i);
//			for(int j=0;j<=k;j++) printf("%d ",st[j]);
//			print(n);
//			printf("\n");
		}
		T[z[st[0]]]=0;
	}
	void print(int n){
		for(int i=1;i<=n;i++){
	//		T[i]=(T[i]==0?0:T[i]+minx-1);
	//		lc[i]=(lc[i]==0?0:lc[i]+minx-1);
	//		rc[i]=(rc[i]==0?0:rc[i]+minx-1);
			printf("%d %d %d\n",T[i],lc[i],rc[i]);
		}
	}
} tree;
int main()
{
	int n;
	scanf("%d",&n);
	int minx=1e9;
	for(int i=0;i<n;i++){
		scanf("%d%d",&x[i],&y[i]);
		minx=min(minx,x[i]);
	}
	for(int i=0;i<=150010;i++) a[i]=-2e9; 
	memset(z,-1,sizeof z);
//	x[0]-=minx-1;
//	a[x[0]]=y[0];
//	z[x[0]]=1;
	for(int i=0;i<n;i++){
		x[i]-=minx-1;
		z[x[i]]=i+1;
		a[x[i]]=y[i];
	}
	tree.build(a);
	puts("YES");
	tree.print(n);
	return 0;
}
