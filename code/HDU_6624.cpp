#include<cstdio>
#include<algorithm>
#include<vector>
#define ULL unsigned long long
#define LL long long
#define I128 __int128_t
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
const LL none=1e15+7;
inline LL gcd(LL a,LL b) {
	for(LL c=a%b; c; a=b,b=c,c=a%b);
	return b;
}
struct frac {
	LL a,b;// a/b
	LL A[240];
	LL tmp;
	int step;
	void sim() {
		//分数化为最简形式
		tmp=gcd(a,b);
		a/=tmp;
		b/=tmp;
	}
	void utc() {
		//分数转为连分数（末尾不为1式）
		for(step=1; b; tmp=a%b,a=b,b=tmp,step++) {
			A[step]=a/b;
		}
		A[step]=none;
	}
	void ch1() {
		//换成末尾为1式
		A[step-1]--;
		A[step]=1;
		A[++step]=none;
	}
	void ch2() {
		//换成末尾不为1式
		A[step-2]++;
		A[--step]=none;
	}
	void ctu() {
		//连分数转为分数
		a=A[step-1],b=1;
		for(step-=2; step; step--) {
			swap(a,b);
			a+=b*A[step];
		}
	}

	int find(const frac &a,const frac &b) {
		for(step=1; a.A[step]==b.A[step]; step++)
			A[step]=a.A[step];
		A[step]=min(a.A[step],b.A[step])+1;
		A[++step]=none;
		return a.A[step]-b.A[step];
	}

	bool operator <(const frac &x) {
		return b!=x.b?b<x.b:a<x.a;
	}
};
frac l,r,ans,tmp[5];
LL p,x;
int T;
int main() {
	read(T);
	int vi,fl;
	for(; T; T--) {
		read(p);
		read(x);
		l.a=x-1,l.b=p;
		r.a=x,r.b=p;
		l.sim(),l.utc();//2式
		r.sim(),r.utc();//2式

		fl=tmp[1].find(l,r);
		if(abs(fl)>=2) {
			if(fl>0){
				r.ch1();
				tmp[2].find(l,r);
			}else{
				l.ch1();
				tmp[2].find(l,r);
			}
			fl=2;
		} else {
			r.ch1();
			tmp[2].find(l,r);
			l.ch1();
			tmp[3].find(l,r);
			r.ch2();
			tmp[4].find(l,r);
			fl=4;
		}

		for(vi=1; vi<=fl; vi++) {
			tmp[vi].ctu();
			tmp[vi].sim();
			tmp[vi].a=(I128)tmp[vi].b*x-(I128)p*tmp[vi].a;
		}
		ans.b=0;
		for(vi=1; vi<=fl; vi++)
			if(ans<tmp[vi])ans.a=tmp[vi].a,ans.b=tmp[vi].b;

		printf("%lld/%lld\n",ans.a,ans.b);
	}
}

