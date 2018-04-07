#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<ctime>
#include<map>
#include<set>
#include<cctype>
#include<cstdlib>
#include<string>
#include<iostream>
#define mp make_pair
using namespace std;

int f[100010];
char T[22][100010],P[100010],k[100010],s[100010];

void getFail(char *P,int *f){
	int m=strlen(P);
	f[0]=0;f[1]=0;
	for(int i=1;i<m;i++){
		int j=f[i];
		while(j && P[j]!=P[i]) j=f[j];
		f[i+1]=(P[i]==P[j] ? j+1 : 0);
	}
}

void KMP(char *T,char *P,int *f){
//	getFail(P,f);
	int n=strlen(T),m=strlen(P);
	register int j=0;
	int u=0,cnt=0;
	memset(s,0,sizeof s);
	for(register int i=0;i<n;i++){
		while(j && T[i]!=P[j]) j=f[j];
		if(T[i]==P[j]) j++;
//		printf("%d\n",j);
		if(j==m){
			for(register int o=u;o<i-j+1;o++){
				s[cnt++]=T[o];
			}
			int lk=strlen(k);
			for(register int o=i-j+1;o<i-j+1+lk;o++){
				s[cnt++]=k[o-(i-j+1)];
			}
	/*		for(int o=i-j+1+strlen(k);o<=i;o++){
				s[cnt++]=T[o];
			}*/
			j=0;
			u=i+1;
		}
	}
	for(int o=u;o<n;o++){
		s[cnt++]=T[o];
	}
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%s",T[i]);
	}
//	map<int,int> S[n+1];
//	vector<int> ans;
	for(int i=0;i<m;i++){
		scanf("%s%s",P,k);
		getFail(P,f);
		for(int j=0;j<n;j++){
			KMP(T[j],P,f);
			strcpy(T[j],s);
//			for(unsigned int o=0;o<ans[i].size();o++){
//				S[j].insert(mp(ans[i][o],i));
//			}
		}
	}
	for(int i=0;i<n;i++){
		printf("%s\n",T[i]);
	}
/*	string s("");
	int h=0,u;
	bool flag=false;
	for(int o=0;o<n;o++){
		s="";
		for(unsigned int i=0;i<strlen(T[o]);i++){
			if(!flag)
				if(S[o].find(i)!=S[o].end()){
					flag=true;
					h=0;
					u=S[o][i];
				}
			if(flag){
				if(h<strlen(k[u])) s+=k[u][h];
				h++;
				if(h>=strlen(P[u])) flag=false;
			}
			else{
				s+=T[o][i];
			}
		}
		cout<<s<<endl;
	}*/
	return 0;
}
