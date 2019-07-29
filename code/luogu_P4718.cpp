#include<cstdio>
#include<algorithm>
#include<vector>
#include<ctime>
#define ULL unsigned long long
#define LL long long
#define LD long double
using namespace std;
char ch;
bool fh;
inline void read(int &a) {
	for(fh=0,ch=getchar(); ch<'0'||ch>'9'; ch=getchar())if(ch=='-')fh=1;
	for(a=0; ch>='0'&&ch<='9'; ch=getchar())(a*=10)+=ch-'0';
	if(fh)a=-a;
}
inline void read(LL &a) {
	for(fh=0,ch=getchar(); ch<'0'||ch>'9'; ch=getchar())if(ch=='-')fh=1;
	for(a=0; ch>='0'&&ch<='9'; ch=getchar())(a*=10)+=ch-'0';
	if(fh)a=-a;
}
inline LL mul(LL a,LL b,LL p) {
	return ((ULL)(a*b)-(ULL)((LD)a/p*b+1e-3)*p+p)%p;
}
inline LL power(LL a,LL b,LL p) {
	LL s=1,w=a;
	for(; b; b>>=1) {
		if(b&1)s=mul(s,w,p);
		w=mul(w,w,p);
	}
	return s;
}
inline LL randx(LL x) {
	return 1+mul(rand()*rand(),rand()*rand(),x);
}
inline LL randlr(LL l,LL r) {
	return l+randx(r-l+1)-1;
}
inline bool Miller(LL x) {
	if(x==1)return 0;
	if(x==2)return 1;
	LL u=x-1;
	int t;
	for(t=0; !(u&1); t++,u>>=1);
	int vi,vk;
	LL vj,vl;
	for(vi=1; vi<=8; vi++) {
		vj=randlr(2,x-1);
		vj=power(vj,u,x);
		for(vk=1; vk<=t; vk++) {
			vl=mul(vj,vj,x);
			if(vl==1&&vj!=1&&vj!=x-1)return 0;
			vj=vl;
		}
		if(vj!=1)return 0;
	}
	return 1;
}
inline LL gcd(LL a,LL b) {
	for(LL c=a%b; c; a=b,b=c,c=a%b);
	return b;
}
LL pollard(LL n,LL c) {
	LL x,y,s,t,d;
	LL Mu;
	s=1,t=2;
	Mu=1;
	x=y=randx(n-2);
	for(;;) {
		x=(mul(x,x,n)+c)%n;
		if(x==y) {
			d=gcd(Mu,n);
			if(d!=1&&d!=n)return d;
			else return n;
		}
		Mu=mul(Mu,abs(x-y),n);
		if(!Mu) {
			d=gcd(abs(x-y),n);
			return d;
		}
		if(!(s%127)) {
			d=gcd(Mu,n);
			if(d!=1&&d!=n)return d;
		}

		s++;
		if(s==t)y=x,t<<=1;
	}
}
LL Stk[1000010];
int top;
void Decompose(LL x) {
	LL y;
	if(Miller(x)) {
		Stk[++top]=x;
		return;
	}
	for(y=x; y>=x; y=pollard(x,randlr(2,x-1)));
	Decompose(y);
	Decompose(x/y);
}
int T;
int main() {
	freopen("T.in","r",stdin);
	freopen("T.out","w",stdout);
//	srand(time(NULL));
	read(T);
	LL x;
	for(; T; T--) {
		read(x);
		if(Miller(x))printf("Prime\n");
		else {
			top=0;
			Decompose(x);
			sort(Stk+1,Stk+top+1);
			printf("%lld\n",Stk[top]);
		}
	}
}

