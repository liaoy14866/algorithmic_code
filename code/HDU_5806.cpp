#include<cstdio>
#include<algorithm>
using namespace std;
const int none=1e9+7;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
int T;
int n,m,k;
int A[200010];
struct inf{
	int sum,num;
	bool operator <(const inf &x)const{
		return sum<x.sum;
	}
}S[200010];
long long ans;
void init(){
	int vi; ans=0;
	read(n); read(m); read(k);
	for(vi=1;vi<=n;vi++)read(A[vi]);
	for(vi=1;vi<=n;vi++)S[vi].sum=S[vi-1].sum+(A[vi]>=m),S[vi].num=vi; S[n+1].sum=none; S[n+1].num=n+1;
}
void slove(){
	int vi,uplen,pos;
	for(vi=1;vi<=n;vi++){
		uplen=k+S[vi-1].sum;
		pos=lower_bound(S+vi,S+n+2,(inf){uplen,0})->num;
		ans+=(n-pos+1);
	}
	printf("%lld\n",ans);
} 
int main(){
	read(T);
	for(int al=1;al<=T;al++){
		init();
		slove();
	}
}