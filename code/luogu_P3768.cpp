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
inline void read(LL &a) {
	for(fh=0,ch=getchar(); ch<'0'||ch>'9'; ch=getchar())if(ch=='-')fh=1;
	for(a=0; ch>='0'&&ch<='9'; ch=getchar())(a*=10)+=ch-'0';
	if(fh)a=-a;
}
const int TIME=4;
LL n,n32,p;
bool flag[10000000*TIME];
LL S[10000000*TIME];
int Prime[10000000*TIME];
int top;
void Sieve(int Up) {
	int vi,vj;
	flag[1]=1;
	S[1]=1;
	for(vi=2; vi<=Up; vi++) {
		if(!flag[vi]) {
			S[vi]=(LL)vi*vi%p*(vi-1)%p;
			Prime[++top]=vi;
		}
		for(vj=1; vi*Prime[vj]<=Up; vj++) {
			flag[vi*Prime[vj]]=1;
			if(vi%Prime[vj]!=0) {
				S[vi*Prime[vj]]=(LL)S[vi]*S[Prime[vj]]%p;
			} else {
				S[vi*Prime[vj]]=(LL)S[vi]*Prime[vj]%p*((LL)Prime[vj]*Prime[vj]%p)%p;
				break;
			}

		}
	}
}
inline LL upvi(LL vi,LL a) {
	return (a/(a/vi));
}
unordered_map<LL,LL> Sum;
LL tmpa,tmpb,tmpc;
inline LL pow1s(LL n){
	tmpa=n,tmpb=n+1;
	if(n&1)tmpb>>=1;else tmpa>>=1;
	tmpa%=p; tmpb%=p;
	return tmpa*tmpb%p;
}
inline LL pow2s(LL n) {
	//sum^{i=1}_{n}{i^2}
	tmpa=n,tmpb=n+1,tmpc=(n<<1)+1;
	if(tmpa&1)tmpb>>=1;
	else tmpa>>=1;
	if(tmpa%3==0)tmpa/=3;
	else if(tmpb%3==0)tmpb/=3;
	else tmpc/=3;
	tmpa%=p,tmpb%=p,tmpc%=p;
	return tmpa*tmpb%p*tmpc%p;
}
inline LL pow3s(LL n){
	tmpa=n,tmpb=n+1;
	if(tmpa&1)tmpb>>=1;else tmpa>>=1;
	tmpa%=p; tmpb%=p;
	tmpa=tmpa*tmpb%p;
	return tmpa*tmpa%p;
}
LL DuS(LL n) {
	//sum^{i=1}_{n}{i^2*phi(i)}
	if(n<=n32)return S[n];
	if(Sum.find(n)!=Sum.end())return Sum[n];
	LL s=pow3s(n);
	LL vi,vine;
	for(vi=2,vine=upvi(vi,n);; vi=vine+1,vine=upvi(vi,n)) {
		s=(s-(pow2s(vine)-pow2s(vi-1))*DuS(n/vi)%p)%p;
		if(vine==n)break;
	}
	if(s<0)s+=p;
	Sum[n]=s;
	return s;
}
LL ans;
int main() {
	read(p),read(n);
	n32=ceil(exp(2.0/3.0*log(n)))*TIME;
	Sieve(n32);
	int vi;
	for(vi=1;vi<=n32;vi++)S[vi]=(S[vi]+S[vi-1])%p;
	LL d,dne; LL tmp; LL now,last=0;
	for(d=1,dne=upvi(d,n);;d=dne+1,dne=upvi(d,n)){
		tmp=pow1s(n/d); tmp=tmp*tmp%p;
		now=DuS(dne);
		ans=(ans+(now-last)*tmp%p)%p;
		last=now;
		if(dne==n)break;
	}
	if(ans<0)ans+=p;
	printf("%lld\n",ans);
}
