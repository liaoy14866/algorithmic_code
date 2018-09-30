#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const double eps=1e-6;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
int n,k;
int A[1010],B[1010];
double tmpB[1010];
bool init(){
	int vi;
	read(n); read(k); if(!n&&!k)return 0;
	for(vi=1;vi<=n;vi++)read(A[vi]);
	for(vi=1;vi<=n;vi++)read(B[vi]);
	return 1;
}
bool check(double d){
	//如果<0返回0，否则返回1 
	int vi; double all=0;
	for(vi=1;vi<=n;vi++){
		tmpB[vi]=B[vi]*d-A[vi]; all+=tmpB[vi]; push_heap(tmpB+1,tmpB+vi+1);
	}
	for(vi=n;vi>=n-k+1;vi--)all-=tmpB[1],pop_heap(tmpB+1,tmpB+vi+1);
	return all>=0;
}
double handle(){
	double tl=0,tr=1,tmid;
	while(tr-tl>=eps){
		tmid=(tl+tr)/2;
		if(check(tmid))tr=tmid;else tl=tmid;
	}
	return tr;
}
double ans;
int ANS;
int main(){
	for(;;){
		if(!init())return 0;
		ans=handle();
		ANS=round(ans*100);
		printf("%d\n",ANS);
	}
}