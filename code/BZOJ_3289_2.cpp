#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int n,m,maxn,nowl,nowr,nowsum,Threshold;
long long nowans;
struct inf{
	int x,p;
}P[100010];
inline bool Acmp(const inf &a,const inf &b){
	return a.x<b.x;
}
int A[100010];
int BIT[100010];
void Change(int p,int w){
	for(;p<=maxn;p+=p&-p)BIT[p]+=w;
}
int Getsum(int p){
	int sum=0; for(;p;p-=p&-p)sum+=BIT[p]; return sum;
}
struct ope{
	int l,r,num;
}O[100010];
inline bool Bcmp(const ope &a,const ope &b){
	return a.l/Threshold!=b.l/Threshold?a.l<b.l:a.r<b.r;
}
int tmpw;
void Moarr(int l,int r){
	while(nowl>l){
		nowl--; tmpw=Getsum(A[nowl]-1); nowsum++; nowans+=tmpw; Change(A[nowl],1);
	}
	while(nowr>r){
		tmpw=nowsum-Getsum(A[nowr]); nowsum--; nowans-=tmpw; Change(A[nowr],-1); nowr--;
	}
	while(nowr<r){
		nowr++; tmpw=nowsum-Getsum(A[nowr]); nowsum++; nowans+=tmpw; Change(A[nowr],1);
	}
	while(nowl<l){
		tmpw=Getsum(A[nowl]-1); nowsum--; nowans-=tmpw; Change(A[nowl],-1); nowl++;
	}
}
long long Ans[100010];
int main(){
	int i;
	read(n);
	for(i=1;i<=n;i++)read(P[i].x),P[i].p=i;
	sort(P+1,P+n+1,Acmp);
	for(i=1;i<=n;i++)A[P[i].p]=A[P[i-1].p]+(P[i].x!=P[i-1].x); maxn=A[P[n].p];
	read(m); Threshold=n/ceil(sqrt(m)); if(!Threshold)Threshold=1;
	for(i=1;i<=m;i++)read(O[i].l),read(O[i].r),O[i].num=i;
	sort(O+1,O+m+1,Bcmp);
	nowl=1; nowr=1; Change(A[1],1); nowsum=1;
	for(i=1;i<=m;i++){
		Moarr(O[i].l,O[i].r);
		Ans[O[i].num]=nowans;
	}
	for(i=1;i<=m;i++)printf("%lld\n",Ans[i]);
}