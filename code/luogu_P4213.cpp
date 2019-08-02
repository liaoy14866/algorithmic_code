#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#include<unordered_map>
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
const int TIME=6;
int T;
int n[12];
int maxn,maxn32;
bool flag[1700000*TIME];
LL PhiS[1700000*TIME];
int MuS[1700000*TIME];
int Prime[1700000*TIME];
int top;
void Sieve(int Up) {
	int vi,vj;
	flag[1]=1;
	PhiS[1]=1;
	MuS[1]=1;
	for(vi=2; vi<=Up; vi++) {
		if(!flag[vi]) {
			PhiS[vi]=vi-1;
			MuS[vi]=-1;
			Prime[++top]=vi;
		}
		for(vj=1; vi*Prime[vj]<=Up; vj++) {
			flag[vi*Prime[vj]]=1;
			if(vi%Prime[vj]!=0) {
				PhiS[vi*Prime[vj]]=PhiS[vi]*PhiS[Prime[vj]];
				MuS[vi*Prime[vj]]=-MuS[vi];
			} else {
				PhiS[vi*Prime[vj]]=PhiS[vi]*Prime[vj];
				MuS[vi*Prime[vj]]=0;
				break;
			}

		}
	}
}
inline int upvi(int vi,int a) {
	return (a/(a/vi));
}
unordered_map<int,int> MuSum;
unordered_map<int,LL> PhiSum;
LL ans;
LL DuPhiS(int n) {
	if(n<=maxn32)return PhiS[n];
	if(PhiSum.find(n)!=PhiSum.end())return PhiSum[n];
	LL s=(LL)n*(n+1)>>1;
	int vi,vine;
	for(vi=2,vine=upvi(vi,n);; vi=vine+1,vine=upvi(vi,n)) {
		s-=(LL)(vine-vi+1)*DuPhiS(n/vi);
		if(vine==n)break;
	}
	PhiSum[n]=s;
	return s;
}
int DuMuS(int n) {
	if(n<=maxn32)return MuS[n];
	if(MuSum.find(n)!=MuSum.end())return MuSum[n];
	int s=1;
	int vi,vine;
	for(vi=2,vine=upvi(vi,n);; vi=vine+1,vine=upvi(vi,n)) {
		s-=(vine-vi+1)*DuMuS(n/vi);
		if(vine==n)break;
	}
	MuSum[n]=s;
	return s;
}
int main() {
	freopen("T.in","r",stdin);
	read(T);
	int vi;
	for(vi=1; vi<=T; vi++)read(n[vi]),maxn=max(maxn,n[vi]);
	maxn32=ceil(exp(2.0/3.0*log(maxn)))*TIME;
	Sieve(maxn32);
	for(vi=1; vi<=maxn32; vi++)MuS[vi]+=MuS[vi-1],PhiS[vi]+=PhiS[vi-1];
	for(vi=1; vi<=T; vi++) {
		ans=DuPhiS(n[vi]);
		printf("%lld ",ans);
		ans=DuMuS(n[vi]);
		printf("%lld\n",ans);
	}
}

