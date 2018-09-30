/*
题目大意：
给出一个长度为n的序列，依次给出m个操作，每次操作交换两个数字。
输出原序列逆序对的个数与每次操作之后逆序对的个数。

可以尝试分块+二分
*/
#include<cstdio>
#include<algorithm>
#include<cmath>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
struct inf{
	int T[160];
	int top;
}B[160];
int A[21000];
int n,m,Threshold,Num;
int smaller(int l,int r,int w){
	if(l>r)return 0;
	int pl=(l/Threshold)+(l%Threshold?1:0),pr=(r/Threshold)+(r%Threshold?1:0),vi,sum=0,tl,tr,mid;
	for(vi=pl+1;vi<=pr-1;vi++){
		tl=1,tr=B[vi].top; if(B[vi].T[1]>=w)continue;
		while(tl!=tr){
			mid=((tl+tr)>>1)+1;
			if(B[vi].T[mid]<w)tl=mid;else tr=mid-1;
		}
		sum+=tl;
	}
	if(pl!=pr){
		for(vi=l;vi<=pl*Threshold;vi++)sum+=(A[vi]<w);
		for(vi=(pr-1)*Threshold+1;vi<=r;vi++)sum+=(A[vi]<w);
	}else for(vi=l;vi<=r;vi++)sum+=(A[vi]<w);
	return sum;
}
int bigger(int l,int r,int w){
	if(l>r)return 0;
	int pl=(l/Threshold)+(l%Threshold?1:0),pr=(r/Threshold)+(r%Threshold?1:0),vi,sum=0,tl,tr,mid;
	for(vi=pl+1;vi<=pr-1;vi++){
		tl=1;tr=B[vi].top; if(B[vi].T[B[vi].top]<=w)continue;
		while(tl!=tr){
			mid=(tl+tr)>>1;
			if(B[vi].T[mid]>w)tr=mid;else tl=mid+1;
		}
		sum+=B[vi].top-tr+1;
	}
	if(pl!=pr){
		for(vi=l;vi<=pl*Threshold;vi++)sum+=(A[vi]>w);
		for(vi=(pr-1)*Threshold+1;vi<=r;vi++)sum+=(A[vi]>w);
	}else for(vi=l;vi<=r;vi++)sum+=(A[vi]>w);
	return sum;
}
void Restruct(int p){
	p=p/Threshold+(p%Threshold?1:0); int l=(p-1)*Threshold+1,r=p*Threshold; if(r>n)r=n;
	for(int vi=l;vi<=r;vi++)B[p].T[vi-l+1]=A[vi];
	std::sort(B[p].T+1,B[p].T+B[p].top+1);
}
long long ans;
int main(){
	int i,j,l,r,u,v,wu,wv;
	read(n); Threshold=ceil(sqrt(n)); Num=n/Threshold; if(Num*Threshold<n)Num++;
	for(i=1;i<=n;i++)read(A[i]);
	for(i=1;i<=Num;i++){
		l=(i-1)*Threshold+1; r=i*Threshold; if(r>n)r=n;
		for(j=l;j<=r;j++)B[i].T[++B[i].top]=A[j];
		std::sort(B[i].T+1,B[i].T+B[i].top+1);
	}
	for(i=2;i<=n;i++)ans+=bigger(1,i-1,A[i]);
	printf("%lld\n",ans);
	read(m);
	for(i=1;i<=m;i++){
		read(u); read(v); wu=A[u]; wv=A[v];
		ans-=bigger(1,u-1,wu); ans-=smaller(u+1,n,wu);
		A[u]=wv; Restruct(u);
		ans+=bigger(1,u-1,wv); ans+=smaller(u+1,n,wv);
		ans-=bigger(1,v-1,wv); ans-=smaller(v+1,n,wv);
		A[v]=wu; Restruct(v);
		ans+=bigger(1,v-1,wu); ans+=smaller(v+1,n,wu);
		printf("%lld\n",ans);
	}
}