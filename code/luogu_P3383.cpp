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
int p;
int n,m;
int Prime[3000010],Phi[3000010],Inv[3000010],Mu[3000010];
int top;
bool flag[3000010];

int power(int a,int b,int p) {
	LL s=1,w=a;
	for(; b; b>>=1) {
		if(b&1)s=s*w%p;
		w=w*w%p;
	}
	return s;
}

void Sieve(int Up) {
	int vi,vj;
	flag[1]=1;
	Phi[1]=1;
	Inv[1]=1;
	Mu[1]=1;
	for(vi=2; vi<=n; vi++) {
		if(!flag[vi]) {
			Phi[vi]=vi-1;
			Mu[vi]=-1;
			Inv[vi]=power(vi,p-2,p);
			Prime[++top]=vi;
		}
		for(vj=1; vi*Prime[vj]<=Up; vj++) {
			flag[vi*Prime[vj]]=1;
			Inv[vi*Prime[vj]]=(LL)Inv[vi]*Inv[Prime[vj]]%p;
			if(vi%Prime[vj]!=0) {
				Phi[vi*Prime[vj]]=Phi[vi]*Phi[Prime[vj]];
				Mu[vi*Prime[vj]]=-Mu[vi];
			} else {
				Phi[vi*Prime[vj]]=Phi[vi]*Prime[vj];
				Mu[vi*Prime[vj]]=0;
				break;
			}

		}
	}
}
int main() {
	read(n);
	read(p);
	Sieve(n);
	int vi;
	for(vi=1; vi<=n; vi++)printf("%d\n",Inv[vi]);
}
