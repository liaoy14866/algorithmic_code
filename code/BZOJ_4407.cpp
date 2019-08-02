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
const int intp=1e9+7;
int n[2010],m[2010];
int k;
int Prime[5000010];
int Pow[5000010];
int top;
bool flag[5000010];
int h[5000010];
inline int power(int a,int b) {
	LL s=1,w=a;
	for(; b; b>>=1) {
		if(b&1)s=s*w%intp;
		w=w*w%intp;
	}
	return s;
}
void Sieve(int Up) {
	int vi,vj;
	flag[1]=1;
	h[1]=1;
	for(vi=2; vi<=Up; vi++) {
		if(!flag[vi]) {
			Prime[++top]=vi;
			Pow[top]=power(vi,k);
			h[vi]=Pow[top]-1;
		}
		for(vj=1; vi*Prime[vj]<=Up; vj++) {
			flag[vi*Prime[vj]]=1;
			if(vi%Prime[vj]!=0) {
				h[vi*Prime[vj]]=(LL)h[vi]*h[Prime[vj]]%intp;
			} else {
				h[vi*Prime[vj]]=(LL)h[vi]*Pow[vj]%intp;
				break;
			}

		}
	}
}
int maxn;
inline int upvi(int vi,int a,int b) {
	return min(a/(a/vi),b/(b/vi));
}
int ans;
void Count(int n,int m) {
	int t,tne;
	ans=0;
	for(t=1,tne=upvi(t,n,m);; t=tne+1,tne=upvi(t,n,m)) {
		ans=(((LL)(n/t)*(m/t)%intp)*(LL)(h[tne]-h[t-1])%intp+ans)%intp;
		if(tne==n)break;
	}
}
int T;
int main() {
	read(T);
	read(k);
	int vi;
	for(vi=1; vi<=T; vi++) {
		read(n[vi]),read(m[vi]);
		if(n[vi]>m[vi])swap(n[vi],m[vi]);
		maxn=max(maxn,n[vi]);
	}
	Sieve(maxn);
	for(vi=1; vi<=maxn; vi++)h[vi]=(h[vi]+h[vi-1])%intp;
	for(vi=1; vi<=T; vi++) {
		Count(n[vi],m[vi]);
		if(ans<0)ans+=intp;
		printf("%d\n",ans);
	}
}

