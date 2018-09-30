#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,maxn;
struct cir{
	int I,O,H;
}B[210000],A[210000];
inline bool Bcmp(const cir &a,const cir &b){
	return (a.O!=b.O?a.O>b.O:a.I>b.I);
}
struct inf{
	int x,p;
}ci[210000];
inline bool Acmp(const inf &a,const inf &b){
	return a.x<b.x;
}
int di[210000];
int top;
long long F[210000],C[210000];
void Change(int p,long long w){
	for(int vi=p;vi<=maxn;vi+=vi&-vi)C[vi]=std::max(C[vi],w);
}
long long Getmax(int p){
	long long sum=0;
	for(int vi=p;vi;vi-=vi&-vi)sum=std::max(sum,C[vi]);
	return sum;
}
long long ans;
int main(){
	int i;
	read(n);
	for(i=1;i<=n;i++){
		top++; read(ci[top].x); ci[top].p=top; top++; read(ci[top].x); ci[top].p=top; read(B[i].H);
	}
	std::sort(ci+1,ci+top+1,Acmp);
	di[ci[1].p]=1;
	for(i=2;i<=top;i++)di[ci[i].p]=di[ci[i-1].p]+(ci[i].x!=ci[i-1].x); maxn=di[ci[top].p]+1;
	for(i=1;i<=n;i++)B[i].I=di[(i-1)<<1|1],B[i].O=di[i<<1];
	std::sort(B+1,B+n+1,Bcmp);
	top=0;
	for(i=1;i<=n;i++){
		if(B[i].O==B[i+1].O&&i!=n){
			B[i+1].H+=B[i].H; continue;
		}
		top++; A[top]=B[i];
	}
	for(i=1;i<=top;i++){
		F[i]=Getmax(A[i].O-1)+A[i].H;
		Change(A[i].I,F[i]);
	}
	ans=Getmax(maxn);
	printf("%lld\n",ans);
}