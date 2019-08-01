#include<cstdio>
#include<algorithm>
#include<vector>
#define ULL unsigned long long
#define LL long long
using namespace std;
char ch;
bool fh;
inline void read(int &a) {
	for(fh=0,ch=getchar(); ch<'0'||ch>'9'; ch=getchar())if(ch=='-')fh=1;
	for(a=0; ch>='0'&&ch<='9'; ch=getchar())(a*=10)+=ch-'0';
	if(fh)a=-a;
}
/*
ans=sigma(T=[1..n]){T*G(T)*s(n/T)*s(m/T)}
ÆäÖÐs(n)=(1+n)n/2 G(T)=k*Mu(k)
*/
const int intp=20101009;
int Prime[10000010];
int top;
bool flag[10000010];
int G[10000010];
void Sieve(int Up) {
	int vi,vj;
	flag[1]=1;
	G[1]=1;
	for(vi=2; vi<=Up; vi++) {
		if(!flag[vi]) {
			G[vi]=1-vi;
			Prime[++top]=vi;
		}
		for(vj=1; vi*Prime[vj]<=Up; vj++) {
			flag[vi*Prime[vj]]=1;
			if(vi%Prime[vj]!=0) {
				G[vi*Prime[vj]]=(LL)G[vi]*G[Prime[vj]]%intp;
			} else {
				G[vi*Prime[vj]]=G[vi];
				break;
			}
		}
	}
}
int n,m;
inline int upvi(int vi,int a,int b) {
	return min(a/(a/vi),b/(b/vi));
}
inline int s(int x) {
	return (((LL)(1+x)*x)>>1)%intp;
}
int ans;
int main() {
	read(n),read(m);
	if(n>m)swap(n,m);
	Sieve(n);
	int T,Tne;
	int vi;
	for(vi=1; vi<=n; vi++) {
		G[vi]=(LL)G[vi]*vi%intp;
		G[vi]=(G[vi]+G[vi-1])%intp;
	}
	if(!n) {
		printf("0\n");
		return 0;
	}
	for(T=1,Tne=upvi(T,n,m);; T=Tne+1,Tne=upvi(T,n,m)) {
		ans=(ans+(LL)(G[Tne]-G[T-1])*((LL)s(n/T)*s(m/T)%intp)%intp)%intp;
		if(Tne==n)break;
	}
	if(ans<0)ans+=intp;
	printf("%d\n",ans);
}

