#include <algorithm>
#include <vector>
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int n,m,cur;  
const int maxn=15;
long long d[2][1<<maxn];

void updata(int a,int b) {
	if(b&(1<<m)) d[cur][b^(1<<m)]+=d[cur^1][a];
}

int main(){
	while(scanf("%d%d",&n,&m)>0){
		if(n<m) swap(n,m);
		memset(d,0,sizeof d);
		cur=0;
		d[0][(1<<m)-1]=1;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cur^=1;
				memset(d[cur],0,sizeof d[cur]);
				for(int k=0;k<(1<<m);k++){
					updata(k,k<<1);//不放
					//向上放 
					if(i && !(k&(1<<(m-1)))) updata(k,(k<<1)^(1<<m)^1);
					//向左放 
					if(j && !(k&1)) updata(k,(k<<1)^3);
				}
			}
		}
		printf("%lld\n",d[cur][(1<<m)-1]);
	}
	return 0;
}
