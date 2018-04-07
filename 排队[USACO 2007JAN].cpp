#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cctype>
#define N 50010
using namespace std;
int f[N][20],d[N][20];
inline int getint()
{
	char ch;int p=1;
	for(ch=getchar();ch!='-' && !isdigit(ch);ch=getchar());
	if(ch=='-'){
		p=-1;
		ch=getchar();
	}
	int t=0;
	for(;isdigit(ch);ch=getchar()){
		t=t*10+(ch-48);
	}
	return t*p;
}
int RMQ(int L,int R)
{
	int k=0;
	while((1<<(k+1))<=R-L+1) k++;
	return max(f[L][k],f[R-(1<<k)+1][k])-min(d[L][k],d[R-(1<<k)+1][k]);
}
int main()
{
	int n=getint();
	int q=getint();
	memset(f,-1,sizeof(f));
	memset(d,127,sizeof(d));
	for(int i=1;i<=n;i++){
		d[i][0]=f[i][0]=getint();
	}
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			d[i][j]=min(d[i][j-1],d[i+(1<<(j-1))][j-1]);
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
	while(q--){
		int x=getint(),y=getint();
		printf("%d\n",RMQ(x,y));
	}
	return 0;
}
