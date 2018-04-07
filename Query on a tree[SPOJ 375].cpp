#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#define LL long long
#define N 100010
#define MAXSIZE 50000007
#define lc (o<<1)
#define rc (o<<1 | 1)
using namespace std;

struct Edge{
	LL from,to,dist,ne;
	Edge():from(0),to(0),dist(0),ne(0){}
	Edge(LL from,LL to,LL dist,LL ne)
		:from(from),to(to),dist(dist),ne(ne){}
} e[N*2];

struct treeNode{
	LL fa,son,tid,top,dep,Size;
	LL v;
	treeNode(){
		fa=son=tid=top=dep=Size=v=0;
	}
	void clear(){
		fa=son=tid=top=dep=Size=v=0;
	}
} a[N];

char buf[MAXSIZE];LL bufpos;
LL g[N],Index=0,real[N],n,m,cnt,x,y;
LL sum[N<<2];
/*
inline LL readLL(){
	char ch;
	long long p=0,t;
	for(ch=getchar();ch!='-' && !isdigit(ch);ch=getchar());
	if(ch=='-'){
		t=-1;
	}
	else{
		t=1;
	}
	for(;!isdigit(ch);ch=getchar());
	for(;isdigit(ch);ch=getchar()){
		p=p*10+ch-48;
	}
	return t*p;
}

inline char readch(){
	char ch;
	for(;ch!='Q' && ch!='D' && ch!='C';ch=getchar());
	return ch;
}
*/
void init(){
	#ifdef LOCAL
		freopen("in.in","r",stdin);
	#endif
	buf[fread(buf,1,MAXSIZE,stdin)]='\0';
	bufpos=0;
}

inline LL readLL(){
	bool isneg;
	LL val=0;
	for(;!isdigit(buf[bufpos]) && buf[bufpos]!='-';bufpos++);
	bufpos+=(isneg=buf[bufpos]=='-');
	for(;isdigit(buf[bufpos]);bufpos++)
		val=val*10+buf[bufpos]-'0';
	return isneg?-val:val;
}

inline char readch(){
    for(;buf[bufpos]!='Q' && buf[bufpos]!='C' && buf[bufpos]!='D';bufpos++);
    return buf[bufpos++];
}
 
void dfs_find(LL t,LL father,LL depth){
	a[t].fa=father;
	a[t].dep=depth;
	a[t].Size=1;
	LL maxsize=0;
	a[t].son=0;
	for(LL i=g[t];i!=-1;i=e[i].ne){
		if(e[i].to!=father){
			dfs_find(e[i].to,t,depth+1);
			a[t].Size+=a[e[i].to].Size;
			a[e[i].to].v=e[i].dist;
			if(a[e[i].to].Size>maxsize){
				a[t].son=e[i].to;
				maxsize=a[e[i].to].Size;
			}
		}
	}
}

void dfs_connect(LL t,LL ancestor){
	a[t].tid=++Index;
	real[a[t].tid]=t;
	a[t].top=ancestor;
	if(a[t].son!=0){
		dfs_connect(a[t].son,ancestor);
	}
	for(LL i=g[t];i!=-1;i=e[i].ne){
		if(e[i].to!=a[t].fa && e[i].to!=a[t].son){
			dfs_connect(e[i].to,e[i].to);
		}
	}
}

void maintain(LL o,LL L,LL R){
	if(L==R) sum[o]=a[real[L]].v;
	if(L<R) sum[o]=max(sum[lc],sum[rc]);
}

void build(LL o,LL L,LL R){
	if(L>R) return;
	if(L==R){
		sum[o]=a[real[L]].v;
	}
	else{
		LL mid=(L+R)>>1;
		build(lc,L,mid);
		build(rc,mid+1,R);
		maintain(o,L,R);
	}
}

void updata(LL o,LL L,LL R,LL x1,LL x2,LL x3){
	if(L>=x1 && R<=x2){
		sum[o]=x3;
		return;
	}
	LL mid=(L+R)>>1;
	if(x1<=mid) updata(lc,L,mid,x1,x2,x3);
	if(x2>mid) updata(rc,mid+1,R,x1,x2,x3);
	maintain(o,L,R);
}

LL query(LL o,LL L,LL R,LL x1,LL x2){
	if(x1<=L && x2>=R) return sum[o];
	LL ret=-1e9;
	LL mid=(L+R)>>1;
	if(x1<=mid) ret=max(ret,query(lc,L,mid,x1,x2));
	if(x2> mid) ret=max(ret,query(rc,mid+1,R,x1,x2));
	return ret;
}

void change(LL x,LL y,LL d){
	if(a[x].dep>a[y].dep) swap(x,y);
	updata(1,1,n,a[y].tid,a[y].tid,d);
}

LL getans(LL x,LL y){
	LL ans=-1e9;
	while(a[x].top!=a[y].top){
		if(a[a[x].top].dep<a[a[y].top].dep) swap(x,y);
		ans=max(ans,query(1,1,n,a[a[x].top].tid,a[x].tid));
		x=a[a[x].top].fa;
	}
	if (x==y) return ans;
	if(a[x].dep>a[y].dep) swap(x,y);
	ans=max(ans,query(1,1,n,a[a[x].son].tid,a[y].tid));
	return ans;
}

int main()
{
	init();
	LL item=readLL();
	while(item--){
		n=readLL();
		memset(g,-1,sizeof g);
		cnt=0;
		for(LL i=1;i<=n;i++) a[i].clear();
		for(LL i=1;i<n;i++){
			LL x=readLL();
			LL y=readLL();
			LL z=readLL();
			e[cnt]=Edge(x,y,z,g[x]);
			g[x]=cnt++;
			e[cnt]=Edge(y,x,z,g[y]);
			g[y]=cnt++;
		}
		Index=0;
		dfs_find(1,0,1);
		dfs_connect(1,1);
		a[1].v=-1e9;
		build(1,1,n);
		for(;;){
		//	printf("#\t%lld\n",query(1,1,n,2,2));
			char D=readch();
			if(D=='D'){
				break;
			}
			if(D=='C'){
				LL x;LL y;
				x=(readLL()-1)*2;
				y=readLL();
				change(e[x].from,e[x].to,y);
			}
			if(D=='Q'){
				LL x=readLL();
				LL y=readLL();
				printf("%lld\n",getans(x,y));
			}
		}
	}
	return 0;
}
