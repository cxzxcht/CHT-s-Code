#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<vector>
#include<cstdlib>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<list>
#include<ctime>
#include<string>
#include<sstream>
#include<fstream>
#include<cmath>
#include<climits>
#define N 300010
using namespace std;

inline int getint()
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

long long f[N],a[N];
double d[N];
int n,m;

bool check(double x){
	double mind=1e8;
	d[0]=0;
	for(int i=1;i<=n;i++){
		d[i]=(double)f[i]-x*i;
		if(m==1&&d[i]>=0) return true;
	}
	int j=0;
	for(int i=m;i<=n;i++){
		if(d[j]<mind) mind=d[j];
		j++;
		if(d[i]-mind>0) return true;
	}
	return false;
}

int main()
{
    n=getint();
    m=getint();
    f[0]=0;
    for(int i=1;i<=n;i++){
    	a[i]=getint();
    	f[i]=a[i]+f[i-1];
	}
	double L=0,R=1e7,mid;
//	cout<<check(3.99999999)<<endl;
	while(abs(R-L)>1e-10){
		mid=(L+R)/2;
		if(check(mid)){
			L=mid;
		}
		else{
			R=mid;
		}
	}
	printf("%.10lf",L);
    return 0;
}
