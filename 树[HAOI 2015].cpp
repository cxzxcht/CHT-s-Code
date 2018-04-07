#include <cstdio>
#include <algorithm>
#include <cstring>
#define LL long long
#define N 100010
#define lc (o<<1)
#define rc (o<<1 | 1)
using namespace std;

struct Edge{
	int from,to,ne;
	Edge():from(0),to(0),ne(0){}
	Edge(int from,int to,int ne)
		:from(from),to(to),ne(ne){}
} e[N*2];

struct treeNode{
	int fa,son,tid,top,dep,Size;
	LL v;
	treeNode(){
		fa=son=tid=top=dep=Size=v=0;
	}
} a[N];

int g[N],Index=0,real[N],n,m,cnt,x,y;
LL sum[N<<2],add[N<<2];

void dfs_find(int t,int father,int depth){
	a[t].fa=father;
	a[t].dep=depth;
	a[t].Size=1;
	int maxsize=0;
	a[t].son=0;
	for(int i=g[t];i!=-1;i=e[i].ne){
		if(e[i].to!=father){
			dfs_find(e[i].to,t,depth+1);
			a[t].Size+=a[e[i].to].Size;
			if(a[e[i].to].Size>maxsize){
				a[t].son=e[i].to;
				maxsize=a[e[i].to].Size;
			}
		}
	}
}

void dfs_connect(int t,int ancestor){
	a[t].tid=++Index;
	real[a[t].tid]=t;
	a[t].top=ancestor;
	if(a[t].son!=0){
		dfs_connect(a[t].son,ancestor);
	}
	for(int i=g[t];i!=-1;i=e[i].ne){
		if(e[i].to!=a[t].fa && e[i].to!=a[t].son){
			dfs_connect(e[i].to,e[i].to);
		}
	}
}

void maintain(int o,int L,int R){
	if(L==R) sum[o]=a[real[L]].v;
	if(L<R) sum[o]=sum[lc]+sum[rc];
	sum[o]+=add[o]*(R-L+1);
}

void build(int o,int L,int R){
	if(L>R) return;
	if(L==R){
		sum[o]=a[real[L]].v;
	}
	else{
		int mid=(L+R)>>1;
		build(lc,L,mid);
		build(rc,mid+1,R);
		maintain(o,L,R);
	}
}

void pushdown(int o,int L,int R){
	if(add[o]!=0){
		add[lc]+=add[o];
		add[rc]+=add[o];
		int mid=(L+R)>>1;
		sum[lc]+=add[o]*(mid-L+1);
		sum[rc]+=add[o]*(R-mid);
		add[o]=0;
	}
}

void updata(int o,int L,int R,int x1,int x2,LL x3){
	if(L>=x1 && R<=x2){
		sum[o]+=x3*(R-L+1);
		add[o]+=x3;
		return;
	}
	int mid=(L+R)>>1;
	pushdown(o,L,R);
	if(x1<=mid) updata(lc,L,mid,x1,x2,x3);
	if(x2>mid) updata(rc,mid+1,R,x1,x2,x3);
	maintain(o,L,R);
}

LL query(int o,int L,int R,int x1,int x2){
	if(x1<=L && x2>=R) return sum[o];
	pushdown(o,L,R);
	LL ret=0;
	int mid=(L+R)>>1;
	if(x1<=mid) ret+=query(lc,L,mid,x1,x2);
	if(x2> mid) ret+=query(rc,mid+1,R,x1,x2);
	return ret;
}

void change(int x,int y,LL d){
	while(a[x].top!=a[y].top){
		if(a[a[x].top].dep<a[a[y].top].dep){
			swap(x,y);
		}
		updata(1,1,n,a[a[x].top].tid,a[x].tid,d);
		x=a[a[x].top].fa;
	}
	if(a[x].dep>a[y].dep) swap(x,y);
	updata(1,1,n,a[x].tid,a[y].tid,d);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i].v);
	}
	memset(g,-1,sizeof g);
	cnt=0;
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		e[cnt]=Edge(x,y,g[x]);
		g[x]=cnt++;
		e[cnt]=Edge(y,x,g[y]);
		g[y]=cnt++;
	}
	dfs_find(1,0,1);
	dfs_connect(1,1);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int D;
		scanf("%d",&D);
		if(D==1){
			int x;LL y;
			scanf("%d%lld",&x,&y);
			updata(1,1,n,a[x].tid,a[x].tid,y);
		}
		if(D==2){
			int x;LL y;
			scanf("%d%lld",&x,&y);
			updata(1,1,n,a[x].tid,a[x].tid+a[x].Size-1,y);
		}
		if(D==3){
			int u;
			scanf("%d",&u);
			int tu=a[u].top;
			LL ans=0;
			while(tu!=1){
				ans+=query(1,1,n,a[tu].tid,a[u].tid);
				u=a[tu].fa;
				tu=a[u].top;
			}
			ans+=query(1,1,n,a[1].tid,a[u].tid);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
