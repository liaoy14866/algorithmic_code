#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
#define ULL unsigned long long
#define LL long long
using namespace std;
//2^60>1e18 
struct inf{
	LL x;
	int val;
}A[1010];
int n;
inline bool Acmp(const inf &a,const inf &b){return a.val>b.val;}
int ans;
LL r[62];
void linearsubset(int len){
	int vi,vj; LL tmp;
	for(vi=1;vi<=n;vi++){
		tmp=A[vi].x;
		for(vj=len-1;vj>=0;vj--){
			if((tmp>>vj)&1){
				if(r[vj])tmp^=r[vj];
				else {r[vj]=tmp;ans+=A[vi].val;break;}
			}
		}
	}
}
int main(){
	int vi,leng; LL maxx=0;
	freopen("T.in","r",stdin);
	scanf("%d",&n);
	for(vi=1;vi<=n;vi++)scanf("%lld%d",&A[vi].x,&A[vi].val),maxx=max(maxx,A[vi].x);
	sort(A+1,A+n+1,Acmp);
	leng=ceil(log2(maxx));
	linearsubset(leng);
	printf("%d\n",ans);
}

