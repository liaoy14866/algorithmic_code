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
int T;
int n[50010],m[50010];
int maxn;
int Prime[50010];
int top;
int Mu[50010];
int flag[50010];
void Sieve(int Up) {
	int vi,vj;
	flag[1]=1;
	Mu[1]=1;
	for(vi=2; vi<=Up; vi++) {
		if(!flag[vi]) {
			Mu[vi]=-1;
			Prime[++top]=vi;
		}
		for(vj=1; vi*Prime[vj]<=Up; vj++) {
			flag[vi*Prime[vj]]=1;
			if(vi%Prime[vj]!=0) {
				Mu[vi*Prime[vj]]=-Mu[vi];
			} else {
				Mu[vi*Prime[vj]]=0;
				break;
			}
		}
	}
}
inline int upvi(int vi,int a,int b) {
	return min(a/(a/vi),b/(b/vi));
}
inline int upvi(int vi,int a) {
	return a/(a/vi);
}
LL s[50010];
inline LL Counts(int x) {
	if(s[x])return s[x];
	int vi,vine;
	for(vi=1,vine=upvi(vi,x);; vi=vine+1,vine=upvi(vi,x)) {
		s[x]+=(LL)(vine-vi+1)*(x/vi);
		if(vine==x)break;
	}
	return s[x];
}
LL ans;
inline void Count(int n,int m) {
	int d,dne;
	ans=0;
	for(d=1,dne=upvi(d,n,m);; d=dne+1,dne=upvi(d,n,m)) {
		ans+=(LL)(Mu[dne]-Mu[d-1])*Counts(n/d)*Counts(m/d);
		if(dne==n)break;
	}
}
int main() {
	read(T);
	int vi;
	for(vi=1; vi<=T; vi++) {
		read(n[vi]);
		read(m[vi]);
		if(n[vi]>m[vi])swap(n[vi],m[vi]);
		maxn=max(maxn,m[vi]);
	}
	Sieve(maxn);
	for(vi=1; vi<=maxn; vi++)Mu[vi]+=Mu[vi-1];
	for(vi=1; vi<=T; vi++) {
		if(!n[vi]) {
			printf("0\n");
			continue;
		}
		Count(n[vi],m[vi]);
		printf("%lld\n",ans);
	}
}

