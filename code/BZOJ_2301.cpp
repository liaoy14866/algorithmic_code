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
bool flag[50010];
int Mu[50010];
int Prime[50010];
int top;
int T;
int a,b,c,d,k;
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
LL Count(int n,int m,int k) {
	if(n>m)swap(n,m);
	int d,dne;
	int nk=n/k,mk=m/k;
	if(nk<1)return 0;
	LL s=0;
	for(d=1,dne=upvi(1,nk,mk);; d=dne+1,dne=upvi(d,nk,mk)) {
		s+=(LL)(Mu[dne]-Mu[d-1])*(nk/d)*(mk/d);
		if(dne==nk)break;
	}
	return s;
}
LL ans;
int main() {
	Sieve(50000);
	int vi;
	for(vi=1; vi<=50000; vi++)Mu[vi]+=Mu[vi-1];
	read(T);
	for(; T; T--) {
		read(a),read(b),read(c),read(d),read(k);
		ans=Count(b,d,k)-Count(a-1,d,k)-Count(b,c-1,k)+Count(a-1,c-1,k);
		printf("%lld\n",ans);
	}
}

