#include<cstdio>
#include<algorithm>
#include<vector>
#define ULL unsigned long long
#define LD long double
#define LL long long
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
	if(x<0)x+=t;//一定要注意，因为mul会转换为ULL，所以要保证x是正的
	x=mul(x,cg,t); 
	return 1;
}
struct func {
	LL m,c;//x=c(mod m)
};
func res;
void unite(func a,func b) {
	LL c,d;
	axcmodb(a.m,c,b.c-a.c,b.m,d);
	res.m=a.m*d;
	res.c=(mul(a.m,c,res.m)+a.c)%res.m;
}
int n;
func A[100010];
void excrt(int len){
	//[1..len]的方程组 
	int vi;
	res.c=0; res.m=1;
	for(vi=1;vi<=len;vi++)unite(res,A[vi]);
} 
int main() {
	freopen("T.in","r",stdin);
	read(n);
	int vi;
	for(vi=1;vi<=n;vi++)read(A[vi].m),read(A[vi].c);
	excrt(n);
	LL x,t;
	axcmodb(1,x,res.c,res.m,t);
	printf("%lld\n",(long long)x);
}

