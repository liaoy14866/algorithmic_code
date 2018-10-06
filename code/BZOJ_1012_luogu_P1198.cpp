#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
int m,intp;
int tot;
inline void pl(int &a,int b){a=(long long)(a+b)%intp;}
const int CM=1<<18;
int zk,zm;
int Seg[CM<<1];
inline void Change(int p,int w){
	for(p+=zm,Seg[p]=w,p>>=1;p;p>>=1)Seg[p]=max(Seg[p<<1],Seg[p<<1|1]);
}
inline int Getsum(int l,int r){
	int maxn=0;
	for(l=l+zm-1,r=r+zm+1;l^r^1;l>>=1,r>>=1){
		if(!(l&1))maxn=max(maxn,Seg[l^1]); if(r&1)maxn=max(maxn,Seg[r^1]);
	}
	return maxn;
}
int main(){
	int vi,ans=0,vx; char an[5];
	freopen("T.in","r",stdin); freopen("T.out","w",stdout);
	scanf("%d%d",&m,&intp);
	zk=ceil(log2(m+2)); zm=1<<zk;
	for(vi=1;vi<=m;vi++){
		scanf("%s%d",an,&vx);
		if(an[0]=='A'){
			pl(vx,ans); tot++; Change(tot,vx);
		}else{
			ans=Getsum(tot-vx+1,tot); printf("%d\n",ans);
		}
	}
}
