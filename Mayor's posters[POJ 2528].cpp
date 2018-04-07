#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
#define N 20010
#define mp make_pair
#define lc (o*2)
#define rc (o*2+1)
#define MID ((L+R)>>1)
using namespace std;
int n,m,x,y,x1,x2;
pair<int,int> a[N<<2];
bool d[N<<2],lazy[N<<2];
struct Node{
	int x,y;bool f;
	Node():x(0),y(0),f(false){}
	Node(int x,int y,bool f) :x(x),y(y),f(f){}
	inline bool operator <(const Node &o) const
	{
		return (x<o.x);
	}
};

void maintain(int o,int L,int R)
{
//	cout<<o<<' '<<L<<' '<<R<<endl;
	if(L==R) d[o]=false;
	if(L<R){
		d[o]=(d[lc]|d[rc]);
	}
}

void updata(int o,int L,int R)
{
//	printf("%d ",o);
	if(L>=x1&&R<=x2){
		d[o]=false;
		lazy[o]=true;
	}
	else
	if(L<R){
		if(x1<=MID){
			updata(lc,L,MID);
		}
		if(x2>MID){
			updata(rc,MID+1,R);
		}
		if(!lazy[o]) d[o]=d[lc]|d[rc];
	}
}

bool ans;
void query(int o,int L,int R)
{
//	printf("%d\n",o);
	if(!d[o]){
		return;
	}
	if(L>=x1&&R<=x2) ans|=d[o];
	else{
		if(x1<=MID) query(lc,L,MID);
		if(x2>MID) query(rc,MID+1,R);
	}
}

int main()
{
	scanf("%d",&n);
	while(n--){
		scanf("%d",&m);
		vector<Node> q;
		for(int i=1;i<=m;i++){
			scanf("%d%d",&x,&y);
			q.push_back(Node(x,i,true));
			q.push_back(Node(y,i,false));
		}
		sort(q.begin(),q.end());
		vector<Node> g(q);
		q[0].x=1;
		for(register unsigned int i=1;i<q.size();i++){
			if(q[i].x==g[i-1].x){
				q[i].x=q[i-1].x;
			}
			else q[i].x=q[i-1].x+1;
		}
		for(register unsigned int i=0;i<q.size();i++){
			if(q[i].f){
				a[q[i].y].first=q[i].x;
			}
			else{
				a[q[i].y].second=q[i].x;
			}
		}
	//	for(int i=1;i<=m;i++) printf("%d %d\n",a[i].first,a[i].second);
		int M=q[q.size()-1].x;
	//	printf("%d\n",M);
		memset(d,true,sizeof(d));
		memset(lazy,false,sizeof(lazy));
		int sum=0;
		for(int i=m;i>=1;i--){
			ans=false;
			x1=a[i].first;
			x2=a[i].second;
		//	printf("%d %d\n",x1,x2);
			query(1,1,M);
			if(ans) ++sum;
		//	cout<<ans<<endl;
			updata(1,1,M);
		//	puts("");
		//	for(int i=1;i<=10;i++) cout<<d[i]<<' ';
		//	cout<<endl;
		}
		printf("%d\n",sum);
	}
	return 0;
}
