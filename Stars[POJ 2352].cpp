#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#define N 1e6
using namespace std;
struct fenwickTree{
	vector<int> c;//下标从1开始
	
	fenwickTree(){
		c.clear();
		c.push_back(0);
	}
	
	fenwickTree(int n):c(n+1){
		c[0]=0;
	}
	//a中必须为正整数 
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

int main()
{
	int n,x,y;
	scanf("%d",&n);
	fenwickTree tree(32010);
	vector<int> f(n+10);
	for(int i=0;i<n;i++){
		scanf("%d%d",&x,&y);
		tree.updata(x+1,1);
	//	printf("%d\n",tree.sum(x));
		f[tree.sum(x+1)]++;
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",f[i]);
	}
	return 0;
}
