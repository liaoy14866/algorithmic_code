#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#include<unordered_map>
#define LD long double
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
struct func {
	LL m,c;//x=c(mod m)
};
func res;
func A[40];
int e[40];//e[0]记录2的个数，e[1]记录3的个数
LL pi[40];
int etop;
LL g;
unordered_map<LL,int> Ma;
unordered_map<LL,int>::iterator it;
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
LL exgcd(LL a,LL b,LL &x,LL &y) {
	if(!b) {
		x=1,y=0;
		return a;
	}
	LL g=exgcd(b,a%b,x,y),tmp;
	tmp=y,y=x-(a/b)*y,x=tmp;
	return g;
}
inline bool axcmodb(LL a,LL &x,LL c,LL b,LL &t) {
	//ax=c(mod b),x+kt是解。return 0表示无解
	LL gys=exgcd(a,b,x,t),cg;//t只是临时使用
	if(c%gys)return 0;
	else cg=c/gys;
	t=b/gys;
	x%=t;
	if(x<0)x+=t;
	//要注意，x要先变成正的
	x=mul(x,cg,t);
	return 1;
}
void unite(func a,func b) {
	LL c,d;
	if(b.c<a.c)swap(a,b);
	axcmodb(a.m,c,b.c-a.c,b.m,d);
	res.m=a.m*d;
	res.c=(mul(a.m,c,res.m)+a.c)%res.m;
}
void excrt(int len) {
	//[1..len]的方程组
	int vi;
	res.c=0;
	res.m=1;
	for(vi=1; vi<=len; vi++)unite(res,A[vi]);
}
inline bool order(LL g,LL p) {
	//检验 p-1 是不是g在mod p意义下的阶
	int vi;
	for(vi=1; vi<=etop; vi++)
		if(power(g,(p-1)/pi[vi],p)==1)return 0;
	return 1;
}
void Decompose(LL k) {
	//对k质因数分解
	if(k==2) {
		etop=1,e[1]=1,pi[1]=2;
		return;
	}
	LL maxn=ceil(sqrt(k)),vi;
	for(vi=2; vi<=maxn; vi++)
		if(!(k%vi)) {
			pi[++etop]=vi,e[etop]=0;
			for(; !(k%vi); k/=vi)e[etop]++;
		}
	if(k!=1) {
		pi[++etop]=k,e[etop]=1;
	}
}
LL findg(LL p) {
	//return p的原根
	for(LL k=2;; k++)if(order(k,p))return k;
}
void BSGS(LL a,LL &x,LL b,LL p,LL pi) {
	//解a^x=b(mod p)
	Ma.clear();
	LL m=ceil(sqrt(pi));
	LL i,s;
	s=mul(b,power(a,p-m,p),p);
	Ma[s]=m-1;
	for(i=m-2; i>=0; i--) {
		s=mul(s,a,p);
		Ma[s]=i;
	}
	s=1;
	a=power(a,m,p);
	x=p;
	for(i=0; i*m<=pi; i++) {
		it=Ma.find(s);
		if(it!=Ma.end())x=min(x,i*m+it->second);
		s=mul(s,a,p);
	}
}
void F(LL a,LL &n,LL b,LL p,LL pi) {
	//枚举计算a^n=b(mod p)
	//n2被限制在[0..pi-1]
	//如果pi很小，则用枚举，否则用BSGS
	if(pi<=100) {
		LL s=1;
		for(n=0;; n++,s=mul(s,a,p))if(s==b)return;
	} else BSGS(a,n,b,p,pi);
}
void Hellman(LL g,LL &n,LL h,LL pi,LL ei,LL p) {
	//计算g^(n mod pi^ei)=h(mod p)，递推求解
	LL m=p-1;
	LL gmpi=power(g,m/pi,p),mpil=p-1,pil=1,nmodpi=0,n2;
	int l;
	for(l=1; l<=ei; l++) {
		mpil/=pi;
		F(gmpi,n2,mul(power(h,mpil,p),power(g,p-1-mpil*nmodpi,p),p),p,pi);
		nmodpi+=n2*pil;
		pil*=pi;
	}
	n=nmodpi;
}
void Pohlig(LL g,LL &n,LL h,LL p) {
	//计算g^n=h(mod p)，无解n=-1
	if(h==1) {
		n=p-1;
		return;
	}
	int vi;
	for(vi=1; vi<=etop; vi++) {
		Hellman(g,A[vi].c,h,pi[vi],e[vi],p);
		A[vi].m=power(pi[vi],e[vi],p);
	}
	excrt(etop);
	LL t;
	if(axcmodb(1,n,res.c,res.m,t)) {
		n%=t;
		if(n<0)n+=t;
	} else n=-1;
}
void anbmodp(LL a,LL &n,LL b,LL p) {
	//求a^n=b(mod p)，无解n=-1
	LL n1,n2;
	if(b==0) {
		n=-1;
		return;
	}
	Pohlig(g,n1,a,p);
	Pohlig(g,n2,b,p);
	if(n1==-1||n2==-1) {
		n=-1;
		return;
	}
	LL t;
	if(axcmodb(n1,n,n2,p-1,t)) {
		n%=t;
		if(n<0)n+=t;
	} else n=-1;
}
LL B,L,N,P;
//B^L=N(mod P)
void init() {
	etop=0;
	Decompose(P-1);
	g=findg(P);
}
int main() {
	freopen("T.in","r",stdin);
	freopen("T.out","w",stdout);
	for(; scanf("%lld%lld%lld",&P,&B,&N)!=EOF;) {
		init();
		anbmodp(B,L,N,P);
		if(L==-1)printf("no solution\n");
		else printf("%lld\n",L);
	}
}

