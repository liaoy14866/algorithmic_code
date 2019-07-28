#include<cstdio>
#include<algorithm>
#include<vector>
#define ULL unsigned long long
#define LL long long
#define LD long double
using namespace std;
char ch; bool fh;
inline void read(LL &a){
	for(fh=0,ch=getchar();ch<'0'||ch>'9';ch=getchar())if(ch=='-')fh=1;
	for(a=0;ch>='0'&&ch<='9';ch=getchar())(a*=10)+=ch-'0'; if(fh)a=-a;
}
LL intp;
LL a,b;
inline LL mul(LL a,LL b){
	return ((ULL)(a*b)-(ULL)((LD)a/intp*b+1e-3)*intp+intp)%intp;
}
inline LL power(LL a,LL b){
	LL s=1,w=a;
	for(;b;b>>=1){
		if(b&1)s=mul(s,w);
		w=mul(w,w);
	}
	return s;
}
int main(){
	read(a); read(b); read(intp);
	if(a==1&&b==0&&intp==1)printf("1^0 mod 1=0");else
	printf("%lld^%lld mod %lld=%lld",a,b,intp,power(a,b));
}

