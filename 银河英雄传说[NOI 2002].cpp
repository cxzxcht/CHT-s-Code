#include<bits/stdc++.h>
#define maxn 30010
using namespace std;
int n,p[maxn],f[maxn],num[maxn],x,y;
char c;
int find(int x){
	if(f[x]==x) return x;
	else{
		int ne=f[x];
		f[x]=find(f[x]);
		num[x]=num[f[x]];
		p[x]+=p[ne];
		return f[x];
	}
}
void Union(int a,int b){
	int x=find(a),y=find(b);
	if(x!=y){
		f[x]=y;
		p[x]=num[y];
		num[y]+=num[x];
	}
}
int main()
{
	memset(p,sizeof(p),0);
	scanf("%d",&n);
	for(int i=1;i<=30001;i++){
		f[i]=i;num[i]=1;
	}
	for(int it=0;it<n;it++){
		for(c=getchar();c!='M'&&c!='C';c=getchar());
		scanf("%d%d",&x,&y);
		if(c=='M') Union(x,y);
		else if(c=='C'){
			if(find(x)==find(y)){
				if(x==y) printf("0\n");
				else
				printf("%d\n",abs(p[x]-p[y])-1);
			}
			else printf("-1\n");
		}
	}
	return 0;
}
