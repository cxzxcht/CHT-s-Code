//cht 
//dp+滚动数组 
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 10
using namespace std;
int cur=0,n,m,d[2][60000],a[N][N];
int cal[20];

void init(){cal[0]=1;for(int i=1;i<=13;i++)cal[i]=cal[i-1]*3;}

inline int get(int y,int S){
	return (S/cal[y])%3;
}

inline void Min(int &a,int b){
	a=min(a,b);
}

int main()
{
	init();
	while(scanf("%d%d",&n,&m)>0 && (n!=0 || m!=0)){
		memset(d,63,sizeof d);
		d[0][0]=0;
		cur=0;
		int p=cal[m+1];
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				scanf("%d",&a[i][j]);
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cur^=1;
				memset(d[cur],63,sizeof d[cur]);
				int D=a[i][j];
				for(register int k=0;k<p;k++){
					if(j==0 && k>=cal[m]) continue;
					if(d[cur^1][k]>1e9) continue;
					if(a[i][j]<2){
						int left=get(m,k);
						int up=get(j,k);
						if(i==0 && up!=0) continue;
						if(j==0 && left!=0) continue;
						if(left && up && left!=up) continue;
						if(D==1 && (left || up)) continue;
						//不放或连右下 
						if(!left && !up){
							d[cur][k]=min(d[cur][k],d[cur^1][k]);
							if(D==0){
								Min(d[cur][k+cal[j]+cal[m]],d[cur^1][k]+2);
								Min(d[cur][k+cal[j]*2+cal[m]*2],d[cur^1][k]+2);
							}
							continue;
						}
						if(left && up){
							//必须连到左边和上面 
							if(left==1)
							Min(d[cur][k-cal[j]-cal[m]],d[cur^1][k]+2);
							if(left==2)
							Min(d[cur][k-cal[j]*2-cal[m]*2],d[cur^1][k]+2);
							continue;
						}
						if(left && !up){
							//横线或连左下 
							Min(d[cur][k],d[cur^1][k]+2);
							if(left==1)
							Min(d[cur][k+cal[j]-cal[m]],d[cur^1][k]+2);
							if(left==2)
							Min(d[cur][k+cal[j]*2-cal[m]*2],d[cur^1][k]+2);
							continue;
						}
						if(up && !left){
							//竖线或连右上 
							Min(d[cur][k],d[cur^1][k]+2);
							if(up==1)
							Min(d[cur][k-cal[j]+cal[m]],d[cur^1][k]+2);
							if(up==2)
							Min(d[cur][k-cal[j]*2+cal[m]*2],d[cur^1][k]+2);
							continue;
						}						
					}
					else{
						int left=get(m,k);
						int up=get(j,k);
						if(i==0 && up) continue;
						if(j==0 && left) continue;
						if(left && up) continue;
						if(left && left!=D-1) continue;
						if(up && up!=D-1) continue;
						if(left){
							if(D==2)
							Min(d[cur][k-cal[m]],d[cur^1][k]+1);
							if(D==3)
							Min(d[cur][k-cal[m]*2],d[cur^1][k]+1);
							continue;
						}
						if(up){
							if(D==2)
							Min(d[cur][k-cal[j]],d[cur^1][k]+1);
							if(D==3)
							Min(d[cur][k-cal[j]*2],d[cur^1][k]+1);
							continue;
						}
						if(!up && !left){
							if(i<n-1){
								if(D==2)
								Min(d[cur][k+cal[j]],d[cur^1][k]+1);
								if(D==3)
								Min(d[cur][k+cal[j]*2],d[cur^1][k]+1);
							}
							if(j<m-1){
								if(D==2)
								Min(d[cur][k+cal[m]],d[cur^1][k]+1);
								if(D==3)
								Min(d[cur][k+cal[m]*2],d[cur^1][k]+1);
							}
						}
					}
				}
			}
		}
		if(d[cur][0]>1e9) puts("0");
		else printf("%d\n",d[cur][0]/2);
	}
	return 0;
}
