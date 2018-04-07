#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#define N 500010
using namespace std;
vector<vector<int> > g(N);
//vector<int> p;
int l[N],r[N];
bool f[N];
int num=0;
struct fenwickTree{
	vector<int> c;//下标从1开始 
	
	fenwickTree(){
		c.clear();
		c.push_back(0);
	}
	
	fenwickTree(int n):c(n+1){
		c[0]=0;
	}
	
	fenwickTree(vector<int> &a):c(a.size()+2){//a下标从0开始 
		for(register unsigned i=0;i<a.size();i++){
			updata(i+1,a[i]);
		}
		c[0]=0;
	}
	
	inline int lowbit(int x){
		return x & -x;
	}
	
	void updata(unsigned int pos,int x){
		if(pos<1) return;
		while(pos<c.size()){
			c[pos]+=x;
			pos+=lowbit(pos);
		}
	}
	
	int sum(int pos){
		int ret=0;
		while(pos>0){
			ret+=c[pos];
			pos-=lowbit(pos);
		}
		return ret;
	}
};
void dfs(int t){
	l[t]=++num;
	for(register unsigned int i=0;i<g[t].size();i++){
		dfs(g[t][i]);
	}
	r[t]=num;
}
int main()
{
	int n,x,y,m;
	scanf("%d",&n);
	vector<int> a(n);
	for(int i=0;i<n-1;i++){
		scanf("%d%d",&x,&y);
		g[x].push_back(y);
	}
	for(int i=0;i<n;i++){
		a[i]=1;
		f[i+1]=true;
	}
	memset(l,-1,sizeof l);
	memset(r,-1,sizeof r);
	dfs(1);
	fenwickTree tree(a);
	scanf("%d",&m);
	for(int i=0;i<m;i++){
		char ch;
		for(ch=getchar();ch!='Q'&&ch!='C';ch=getchar());
		scanf("%d",&x);
		if(ch=='Q'){
			printf("%d\n",tree.sum(r[x])-tree.sum(l[x]-1));
		}
		if(ch=='C'){
			if(f[x]){
				tree.updata(l[x],-1);
				f[x]=false;
			}
			else{
				tree.updata(l[x],1);
				f[x]=true;
			}
		}
	}
	return 0;
}
