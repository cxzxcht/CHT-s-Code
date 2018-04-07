#include<bits/stdc++.h>
#define N 200010
 
using namespace std;
 
int getint()
{
    char ch;
    int p=0,t;
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
 
int blockL;int blockLen;
int n,f[N],F[N],a[N],q,ans[N];

struct question{
    int l,r,d;
    question(){
        l=r=d=0;
    }
    question(int l,int r,int d):l(l),r(r),d(d){}
    bool operator <(const question x) const{
        if(l/blockL!=x.l/blockL){
            return l<x.l;
        }
        return r<x.r;
    }
} Q[200010];
 
inline void addv(int x){
	if(x<0) return;
	F[x/blockLen]+=!f[x];
	f[x]++;
}
 
inline void moRemove(int x){
	if(x<0) return;
	F[x/blockLen]-=(f[x]==1);
	f[x]--;
}
 
int main()
{
	n=getint();
	q=getint();
    for(int i=1;i<=n;i++){
		a[i]=getint();
		if (a[i]>n) a[i]=n;
    }
	blockL=(int)n/(sqrt(q*2/3));
	blockLen=(int)sqrt(n+1);
    for(int i=1;i<=q;i++){
		Q[i].l=getint();
		Q[i].r=getint();
        Q[i].d=i;
    }
    sort(Q+1,Q+q+1);
    memset(ans,0,sizeof(ans));
    memset(f,0,sizeof f);
    memset(F,0,sizeof F);
    register int L=0,R=0;
    a[0]=-1;
    for(int i=1;i<=q;i++){
		while(R<Q[i].r) addv(a[++R]);
		while(R>Q[i].r) moRemove(a[R--]);
		while(L>Q[i].l) addv(a[--L]);
		while(L<Q[i].l) moRemove(a[L++]);
		register int j;
		for(j=0;j<=n/blockLen && F[j]==blockLen;j++);
		j*=blockLen;
		while(f[j]) j++;
		ans[Q[i].d]=j;
    }
    for(int i=1;i<=q;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}
