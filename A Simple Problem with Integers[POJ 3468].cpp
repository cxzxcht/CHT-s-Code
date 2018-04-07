#include<algorithm>
#include<cctype>
#include<cstdio>
#include<cstring>
#define N 100010
#define lc (o*2)
#define rc (o*2+1)
#define MID ((L+R)>>1)
#define ll long long
using namespace std;

long long n,q,a[N];long long sum[N<<2],add[N<<2],x1,x2,x3;
inline long long getint()
{
	char ch;long long p=1;
	for(ch=getchar();ch!='-' && !isdigit(ch);ch=getchar());
	if(ch=='-'){
		p=-1;
		ch=getchar();
	}
	long long t=0;
	for(;isdigit(ch);ch=getchar()){
		t=t*10+(ch-48);
	}
	return t*p;
}

void maintain(long long o,ll L,ll R)
{
	if(L==R) sum[o]=a[L];
//	sum[o]=0;
	if(L<R){
		sum[o]=sum[lc]+sum[rc];
	}
	sum[o]+=add[o]*(R-L+1);
}

void build(ll o,ll L,ll R)
{
	if(L==R) sum[o]=a[L];
	else{
		if(MID>=L) build(lc,L,MID);
		if(MID<R) build(rc,MID+1,R);
		maintain(o,L,R);
	}
}

void updata(ll o,ll L,ll R)
{
	if(L>=x1&&R<=x2) add[o]+=x3;
	else
	if(L<R){
		if(x1<=MID) updata(lc,L,MID);
		if(x2>MID) updata(rc,MID+1,R);
	}
	maintain(o,L,R);
}

long long ans;
void query(ll o,ll L,ll R,ll _add)
{
	if(L>=x1&&R<=x2) ans+=sum[o]+_add*(R-L+1);
	else{
		if(x1<=MID) query(lc,L,MID,_add+add[o]);
		if(x2>MID) query(rc,MID+1,R,_add+add[o]);
	}
}

int main()
{
	n=getint();
	q=getint();
	for(int i=1;i<=n;i++) a[i]=getint();
	build(1,1,n);
	while(q--){
		char ch;
		for(ch=getchar();ch!='Q'&&ch!='C';ch=getchar());
		if(ch=='Q'){
			x1=getint();
			x2=getint();
			ans=0;
			query(1,1,n,0);
			printf("%lld\n",ans);
		}
		else if(ch=='C'){
			x1=getint();
			x2=getint();
			x3=getint();
			updata(1,1,n);
		}
	}
	return 0;
}
