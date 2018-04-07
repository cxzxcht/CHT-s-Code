#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
#define N 110
using namespace std;
struct Line1{
	double x,y,l;bool f;
	Line1(){
		x=y=l=0;
		f=false;
	}
	Line1(double x,double y,double l,bool f):x(x),y(y),l(l),f(f){}
	inline bool operator <(const Line1 &o) const{
		return y<o.y;
	}
};
struct Line2{
	double x,y,l;bool f;
	Line2(){
		x=y=l=0;
		f=false;
	}
	Line2(double x,double y,double l,bool f):x(x),y(y),l(l),f(f){}
	inline bool operator <(const Line2 &o) const{
		return x<o.x;
	}
};

vector<Line1> C;
vector<Line2> R;
int n;
double a,b,c,d;

int main()
{
	int it=0;
	while(scanf("%d",&n)&&n!=0){
		it++;
		C.clear();
		R.clear();
		for(int i=1;i<=n;i++){
			scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
			C.push_back(Line1(a,b,c-a,true));
			C.push_back(Line1(a,d,c-a,false));
			R.push_back(Line2(a,b,d-b,true));
			R.push_back(Line2(c,b,d-b,false));
		}
		sort(C.begin(),C.end());
		sort(R.begin(),R.end());
		double ans=0;
		int sum=1;
		for(register unsigned int i=1;i<R.size();i++){
			int cnt=1;
			register unsigned int j=0;
			for(;j<C.size() && !(C[j].x<R[i].x&&C[j].x+C[j].l>R[i-1].x);j++);
			Line2 pre=Line2(C[j].x,C[j].y,C[j].l,C[j].f);
			for(j=j+1;j<C.size();j++) if(C[j].x<R[i].x&&C[j].x+C[j].l>R[i-1].x){		
				if(cnt){
				//	if(C[j].x<=R[i].x&&C[j].x+C[j].l>=R[i-1].x&&C[j-1].x<=R[i].x&&C[j-1].x+C[j-1].l>=R[i-1].x)
				//	cout<<R[i].x<<' '<<C[j-1].x<<' '<<C[j-1].l<<' '<<C[j].x<<' '<<C[j].l<<endl;
				//	ans+=max((Min(R[i].x,C[j-1].x+C[j-1].l,C[j].x+C[j].l)-Max(R[i-1].x,C[j-1].x,C[j].x)),0)*(C[j].y-C[j-1].y);
					ans+=(C[j].y-pre.y)*(R[i].x-R[i-1].x);
				}
				if(C[j].f) cnt++;
				else cnt--;
				pre=Line2(C[j].x,C[j].y,C[j].l,C[j].f);
			}
			if(R[i].f) sum++;
			else sum--;
		}
		printf("Test case #%d\n",it);
		printf("Total explored area: %.2f\n",ans);
		printf("\n");
	}
	return 0;
}
