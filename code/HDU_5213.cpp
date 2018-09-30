#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
char c;
inline void read(int &a){
	c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,k,Threshold,Num;
int A[30010];
void init(){
	int vi;
	/*尽量在处理的时候就把数组清空，这样初始化就不必专门清空数组了*/
	read(k); Threshold=ceil(sqrt(n)); Num=n/Threshold; if(Num*Threshold<n)Num++;
	for(vi=1;vi<=n;vi++)read(A[vi]);
	read(m);
}
int SumF[180][180];
int G[180][30010];
int Bucket[30010];
/*SumF[x][y]表示第一个数字在块x，第二个数字在块[1..y]的方案数。G[x][y]表示[1..x]的块中y的个数*/
int Count(const int &r,const int &x,const int &y){
	/*进来的时候Bucket是空的，出去的时候也要一样*/
	if(!r)return 0;
	int pr=r/Threshold+(r%Threshold!=0),px=x/Threshold+(x%Threshold!=0),py=y/Threshold+(y%Threshold!=0),sum=0,vi;
	int prl=(pr-1)*Threshold+1,pxr=px*Threshold,pyl=(py-1)*Threshold+1;
	/*块与块*/
	if(py-px>=2)for(vi=1;vi<=pr-1;vi++)sum+=SumF[vi][py-1]-SumF[vi][px];
	/*零散与块*/
	if(py-px>=2)for(vi=prl;vi<=r;vi++)if(1<=k-A[vi]&&k-A[vi]<=n)sum+=G[py-1][k-A[vi]]-G[px][k-A[vi]];
	if(px!=py){
		for(vi=x;vi<=pxr;vi++)if(1<=k-A[vi]&&k-A[vi]<=n)sum+=G[pr-1][k-A[vi]];
		for(vi=pyl;vi<=y;vi++)if(1<=k-A[vi]&&k-A[vi]<=n)sum+=G[pr-1][k-A[vi]];
	}else for(vi=x;vi<=y;vi++)if(1<=k-A[vi]&&k-A[vi]<=n)sum+=G[pr-1][k-A[vi]];
	/*零散与零散*/
	for(vi=prl;vi<=r;vi++)Bucket[A[vi]]++;
	if(px!=py){
		for(vi=x;vi<=pxr;vi++)if(1<=k-A[vi]&&k-A[vi]<=n)sum+=Bucket[k-A[vi]];
		for(vi=pyl;vi<=y;vi++)if(1<=k-A[vi]&&k-A[vi]<=n)sum+=Bucket[k-A[vi]];
	}else for(vi=x;vi<=y;vi++)if(1<=k-A[vi]&&k-A[vi]<=n)sum+=Bucket[k-A[vi]];
	for(vi=prl;vi<=r;vi++)Bucket[A[vi]]--;
	/*返回sum，并清空了Bucket*/
	return sum;
}
void slove(){
	int vi,vj,vk,l,r,x,y;
	for(vi=1;vi<=Num;vi++){
		l=(vi-1)*Threshold+1; r=vi*Threshold; if(r>n)r=n;
		for(vj=l;vj<=r;vj++)Bucket[A[vj]]++;
		for(vj=1;vj<=Num;vj++){
			x=(vj-1)*Threshold+1; y=vj*Threshold; if(y>n)y=n; SumF[vj][vi]=0;
			for(vk=x;vk<=y;vk++)if(1<=k-A[vk]&&k-A[vk]<=n)SumF[vj][vi]+=Bucket[k-A[vk]];
		}
		for(vj=1;vj<=n;vj++)G[vi][vj]=Bucket[vj];
	}
	memset(Bucket,0,sizeof(Bucket));
	for(vi=1;vi<=m;vi++){
		read(l); read(r); read(x); read(y);
		vk=Count(r,x,y)-Count(l-1,x,y);
		printf("%d\n",vk);
	}
}
int main(){
	while(scanf("%d",&n)!=EOF){
		init();
		slove();
	}
}