#include<algorithm>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#define N 10010
using namespace std;
void getFail(char *P,int *f){
	int m=strlen(P);
	f[0]=0;f[1]=0;
	for(int i=1;i<m;i++){
		int j=f[i];
		while(j && P[j]!=P[i]) j=f[j];
		f[i+1]=(P[i]==P[j] ? j+1 : 0);
	}
}

int KMP(char *T,char *P,int *f){
	getFail(P,f);
	int n=strlen(T),m=strlen(P),ret=0;
	register int j=0;
	for(register int i=0;i<n;i++){
		while(j && T[i]!=P[j]) j=f[j];
		if(T[i]==P[j]) j++;
		if(j==m){
			++ret;
			printf("%d\n",i-j+2);
		}
	}
	return ret;
}

int item,f[1000010];
char P[1000010],T[1000010];
int main()
{
	item=1;
	while(item--){
		scanf("%s",T);
		scanf("%s",P);
		KMP(T,P,f);
	}
	int lp=strlen(P);
	for(int i=1;i<=lp;i++) printf("%d ",f[i]);
	puts("");
	return 0;
}
