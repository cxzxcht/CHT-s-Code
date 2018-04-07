#include<bits/stdc++.h>
#define N 30010
#define blockL 175
 
using namespace std;
 
/*int getint()
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
}*/
 
//double blockL;
int n,sum,f[1000010],a[N],q,ans[200010];
 
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
 
void addv(int x){
    f[x]++;
    if(f[x]==1){
        sum++;
    }
}
 
void moRemove(int x){
    f[x]--;
    if(f[x]==0){
        sum--;
    }
}
 
int main()
{
    scanf("%d",&n);
//  blockL=sqrt(1.0*n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        scanf("%d%d",&Q[i].l,&Q[i].r);
        Q[i].d=i;
    }
    sort(Q+1,Q+q+1);
    memset(ans,0,sizeof(ans));
    int L=0,R=0;
    sum=0;
    for(int i=1;i<=q;i++){
        while(R<Q[i].r && R<n) addv(a[++R]);
        while(R>Q[i].r && R>0) moRemove(a[R--]);
        while(L>Q[i].l && L>1) addv(a[--L]);
        while(L<Q[i].l && L<=n) moRemove(a[L++]);
        ans[Q[i].d]=sum;
    }
    for(int i=1;i<=q;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}
