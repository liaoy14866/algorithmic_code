#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#define ULL unsigned long long
#define LL long long
#define LD long double
using namespace std;
char ch; bool fh;
inline void LLread(LL &a){
	for(fh=0,ch=getchar();ch<'0'||ch>'9';ch=getchar())if(ch=='-')fh=1;
	for(a=0;ch>='0'&&ch<='9';ch=getchar())(a*=10)+=ch-'0'; if(fh)a=-a;
}
int T;
LL i,l,r,k,p,m;
LL Lmul(LL a,LL b){
	return ((ULL)(a*b)-(ULL)((LD)a/p*b+1e-3)*p+p)%p;
}
struct func{
	LL A[3][3];
};
func Aa,res;
int vi,vj,vk;
func Mul(const func &a,const func &b){
	for(vi=1;vi<=2;vi++)
	for(vj=1;vj<=2;vj++)res.A[vi][vj]=0;
	for(vk=1;vk<=2;vk++)
	for(vi=1;vi<=2;vi++)
	for(vj=1;vj<=2;vj++){
		res.A[vi][vj]+=Lmul(a.A[vi][vk],b.A[vk][vj]);
		if(res.A[vi][vj]>=p)res.A[vi][vj]-=p;
	}
	return res;
}
func s,w;
void Power(const func &a,ULL b){
	s.A[1][1]=s.A[2][2]=1; s.A[1][2]=s.A[2][1]=0; w=a;
	for(;b;b>>=1){
		if(b&1)s=Mul(s,w);
		w=Mul(w,w);
	}
}
LL x,y,t,tmp;
LL exgcd(LL a,LL b){
	if(!b){
		x=1; y=0; return a;
	}
	tmp=exgcd(b,a%b);
	t=y; y=x-(a/b)*y; x=t;
	return tmp;
}
LL c,q,gys;
int main(){
	freopen("T.in","r",stdin);
	scanf("%d",&T);
	for(;T;T--){
		LLread(i); LLread(l); LLread(r); LLread(k); LLread(p); LLread(m);
		Aa.A[1][1]=0; Aa.A[1][2]=1; Aa.A[2][1]=1; Aa.A[2][2]=1;
		Power(Aa,k-2);
		x=s.A[1][2]; y=s.A[2][2]; c=(m-Lmul(x,i))%p; if(c<0)c+=p;
		q=y; gys=exgcd(q,p);
		if(c%gys){
			printf("0\n"); continue;
		}
		x%=p; if(x<0)x+=p;
		x=Lmul(x,c/gys); y=p/gys; x%=y;
		l=ceil((LD)(l-x)/y); r=floor((LD)(r-x)/y);
		if(l>r)printf("0\n");else printf("%lld\n",r-l+1);
	}
}

