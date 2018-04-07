#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#define M 200010
#define N 20010
using namespace std;
struct Edge{
    int from,to,len,next;
    Edge(){
        from=to=len=next=0;
    }
    Edge(int from,int to,int len):from(from),to(to),len(len){}
    bool operator <(const Edge x) const{
        return len<x.len;
    }
};

vector<Edge> e(M),k(M),tree(M);
int anc[N][30],c[N][30],g[N],f[N],h[N];
int cnt=0,n,m,x,y,z,s,Q;
 
int find(int x)
{
    return (x==f[x] ? x : f[x]=find(f[x]));
}
 
void Union(int x,int y){
    f[find(x)]=find(y);
}
 
void dfs(int t,int fa,int height){
    h[t]=height;
    anc[t][0]=fa;
    for(int x=g[t];x!=-1;x=tree[x].next){
        if(tree[x].to==fa){
            c[t][0]=tree[x].len;
    //      printf("%d %d %d\n",t,fa,c[t][0]);
            break;
        }
    }
    for(int i=1;(1<<i)<height;i++){
        c[t][i]=max(c[t][i-1],c[anc[t][i-1]][i-1]);
        anc[t][i]=anc[anc[t][i-1]][i-1];
    }
    for(int x=g[t];x!=-1;x=tree[x].next){
        if(tree[x].to!=fa){
            dfs(tree[x].to,t,height+1);
        }
    }
}
 
int LCA(int a,int b)
{
    if(h[a]>h[b]) swap(a,b);
    int ret=0;
    for(int i=h[b]-h[a],j=0;i>0;i>>=1,j++){
        if(i&1){
            ret=max(ret,c[b][j]);
            b=anc[b][j];
        }
    }
    if(a==b) return ret;
    int k;
    for(k=0;(1<<k)<=h[a];k++);
    for(;k>=0;k--){
        if((1<<k)<=h[a] && anc[a][k]!=anc[b][k]){
            ret=max(ret,c[a][k]);
            ret=max(ret,c[b][k]);
    //      printf("%d %d %d\n",a,b,ret);
            a=anc[a][k];
            b=anc[b][k];
        }
    }
    ret=max(ret,c[a][0]);
    ret=max(ret,c[b][0]);
    if(anc[a][0]==0) return -1;
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%d",&Q);
    memset(g,-1,sizeof(g));
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&x,&y,&z);
        e[i].from=x;
        e[i].to=y;
        e[i].len=z;
    }
    sort(e.begin(),e.begin()+m);
    for(int i=1;i<=n;i++) f[i]=i;
    s=0;
    for(int i=0;i<m;i++){
        if(find(e[i].from)!=find(e[i].to)){
            Union(e[i].from,e[i].to);
            tree[cnt].from=e[i].from;
            tree[cnt].to=e[i].to;
            tree[cnt].len=e[i].len;
            tree[cnt].next=g[e[i].from];
            g[e[i].from]=cnt++;
            tree[cnt].from=e[i].to;
            tree[cnt].to=e[i].from;
            tree[cnt].len=e[i].len;
            tree[cnt].next=g[e[i].to];
            g[e[i].to]=cnt++;
            s++;
        }
        if (s==n-1) break;
    }
//  for(int i=1;i<=n;i++){
//      for(int j=g[i];j!=-1;j=tree[j].next){
//          printf("%d %d %d\n",tree[j].from,tree[j].to,tree[j].len);
//      }
//  }
    memset(anc,0,sizeof anc);
    memset(c,0,sizeof(c));
    memset(h,0,sizeof h);
    for(int i=1;i<=n;i++){
        if(f[i]==i){
            dfs(i,0,1);
        }
    }
//  for(int i=1;i<=n;i++){
//      for(int j=0;j<=3;j++){
//          printf("%d ",c[i][j]);
//      }
//      printf("\n");
//  }
    while(Q--){
        scanf("%d%d",&x,&y);
        if(find(x)!=find(y)){
            printf("-1\n");
            continue;
        }
        printf("%d\n",LCA(x,y));
    }
    return 0;
}
