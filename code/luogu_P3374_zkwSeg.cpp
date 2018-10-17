#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
const int CM=1<<19; 
int n,m,zk,zm;
long long Seg[CM<<1];
/*
[1..n]->[2..n+1]->(1..n+2)->2^k>=n+2，即需要一个维护T数组，T[1]=0,T[n+2]=0,T[i]=A[i-1]
k=ceil(log2(n+2)),M=1<<k,其中M表示最小的不小于n+2的二次幂
线段树数组大小为Seg[M<<1]，即[0..M<<1-1]
A[i]对应的叶子节点是i+1(A变为T)+(M-1)(线段树叶子)=i+M
[l..r]对应的叶子区间是(l+M-1,r+M+1)
*/
inline void Change(int p,int w){
	for(p+=zm;p;p>>=1)Seg[p]+=w;
//	for(p+=zm,Seg[p]+=w,p>>=1;p;p>>=1)Seg[p]=Seg[p<<1]+Seg[p<<1|1];
}
inline long long Getsum(int l,int r){
	long long s=0;
	for(l=l+zm-1,r=r+zm+1;l^r^1;l>>=1,r>>=1){
		if(!(l&1))s+=Seg[l^1]; if(r&1)s+=Seg[r^1];
	}
	return s;
}
int main(){
	int vi,opt,x,y;
	freopen("T.in","r",stdin); freopen("T.out","w",stdout);
	scanf("%d%d",&n,&m); zk=ceil(log2(n+2)); zm=1<<zk;
	for(vi=1;vi<=n;vi++)scanf("%lld",&Seg[vi+zm]);
	for(vi=zm-1;vi;vi--)Seg[vi]=Seg[vi<<1]+Seg[vi<<1|1];
	for(vi=1;vi<=m;vi++){
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1)Change(x,y);else printf("%lld\n",Getsum(x,y));
	}
}
