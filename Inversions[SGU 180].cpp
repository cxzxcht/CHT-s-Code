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

struct Node{
	int a,b;
	Node():a(0),b(0){}
	Node(int a,int b):a(a),b(b){}
	bool operator <(const Node &o)const{
		return a<o.a;
	}
};

long long countMoves(const vector<int> &A,int n){
	fenwickTree tree(N);
	long long ret=0;
	for(register int i=0;i<n;i++){
	//	cout<<A[i]<<endl;
		ret+=tree.sum(N-100)-tree.sum(A[i]);
		tree.updata(A[i],1);
	}
	return ret;
}

int main()
{
	int n;
	scanf("%d",&n);
	vector<Node> a(n+2);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].a);
		a[i].b=i;
	}
	stable_sort(a.begin()+1,a.begin()+n+1);
	vector<int> k(n+1);
	vector<int> k2(n+1);
	k[0]=1;
	k2[a[1].b-1]=1;
	for(register int i=2;i<=n;i++){
		if(a[i].a==a[i-1].a){
			k[i-1]=k[i-2];
		}
		else{
			k[i-1]=k[i-2]+1;
		}
	//	cout<<k[i-1]<<endl;
		k2[a[i].b-1]=k[i-1];
	}
/*	for(int i=0;i<n;i++){
 *		cout<<k2[i]<<endl;
 *	}
 */	printf("%lld\n",countMoves(k2,n));
	return 0;
}
