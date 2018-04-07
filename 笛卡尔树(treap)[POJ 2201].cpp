#include<cstdio>
#include<ctime>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>
#include<set>
#include<bitset>
#include<map>
#include<queue>
#define maxn 50010
using namespace std;
struct Node{
	int k,p,s,num;
	Node *ch[2];
	Node(){
		k=0;
		p=rand();
		s=1;
		ch[0]=NULL;
		ch[1]=NULL;
		num=0;
	}
	Node(const int _k){
		k=_k;
		p=rand();
		s=1;
		ch[0]=NULL;
		ch[1]=NULL;
		num=0;
	}
	Node(int x,int y,int num):k(x),p(y),num(num){
		s=1;
		ch[0]=NULL;
		ch[1]=NULL;
	}
	~Node(){
		k=0;
		p=0;
		s=0;
		ch[0]=NULL;
		ch[1]=NULL;
		num=0;
	}
	int cmp(int x) const{
		if(x==k) return -1;
		return x<k?0:1;
	}
	void maintain(){
		s=1;
		if(ch[0]!=NULL) s+=ch[0]->s;
		if(ch[1]!=NULL) s+=ch[1]->s;
	}
};

void rotate(Node *&o,int d){
	Node *k=o->ch[d^1];o->ch[d^1]=k->ch[d];k->ch[d]=o;
	o->maintain();k->maintain();o=k;
}
void putin(Node *&o,int x,int y,int z)
{
	if(o==NULL){
		o=new Node(x,y,z);
	//	printf("%d\n",o->num);
	//	o->ch[0]=null;
	//	o->ch[1]=null;
	}
	else{
		int d=o->cmp(x);
		putin(o->ch[d],x,y,z);
		if(o->ch[d]->p < o->p) rotate(o,d^1);
	}
	o->maintain();
}
void del(Node *&o,int x)
{
	int d=o->cmp(x);
	if(d==-1){
		if(o->ch[0]==NULL) o=o->ch[1];
		else if(o->ch[1]==NULL) o=o->ch[0];
		else{
			int d2=(o->ch[0]->p > o->ch[1]->p?1:0);
			rotate(o,d2);
			del(o->ch[d],x);
		}
	}
	else del(o->ch[d],x);
	if(o!=NULL) o->maintain();
}
bool find(Node *o,int x){
	while(o!=NULL){
		int d=o->cmp(x);
		if(d==-1) return true;
		else o=o->ch[d];
	}
	return 0;
}
int kth(Node *o,int k)//第K大的值 
{
	if(o==NULL||k<=0||k>o->s) return 0;
	int s=(o->ch[1]==NULL?0:o->ch[1]->s);
	if(k==s+1) return o->k;
	else if(k<=s) return kth(o->ch[1],k);
	else return kth(o->ch[0],k-s-1);
}
int a1[maxn],a2[maxn],a3[maxn];

void dfs(Node *o,int fa){
	a1[o->num]=fa;
	if(o->ch[0]!=NULL) a2[o->num]=o->ch[0]->num;
	else a2[o->num]=0;
	if(o->ch[1]!=NULL) a3[o->num]=o->ch[1]->num;
	else a3[o->num]=0;
//	printf("%d %d %d\n",a1[o->num],a2[o->num],a3[o->num]);
	if(o->ch[0]!=NULL) dfs(o->ch[0],o->num);
	if(o->ch[1]!=NULL) dfs(o->ch[1],o->num);
}

int main()
{
	srand((unsigned int)time(NULL));
	Node *root=new Node();
	int n,x[maxn],y[maxn],z[maxn];bool first=true;
	scanf("%d",&n);
	for(int i=0;i<n;i++){	
		scanf("%d%d",&x[i],&y[i]);
		z[i]=i+1;
	}
	for(int i=0;i<n;i++){
		int a=rand()%n,b=rand()%n;
		swap(x[a],x[b]);
		swap(y[a],y[b]);
		swap(z[a],z[b]);
	}
	for(int i=0;i<n;i++){
		if(first) root->k=x[i],root->p=y[i],root->num=z[i],first=false;
		else putin(root,x[i],y[i],z[i]);
	}
//	printf("*****\n");
	memset(a1,0,sizeof a1);
	memset(a2,0,sizeof a2);
	memset(a3,0,sizeof a3);
	dfs(root,0);
	printf("YES\n");
	for(int i=1;i<=n;i++){
		printf("%d %d %d\n",a1[i],a2[i],a3[i]);
	}
	return 0;
}
