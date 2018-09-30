/*
题目大意：
给出一个长度为n的序列，要求支持：
1.区间加
2.查询区间比w大的数字有多少个
个人解法：
分块+二分即可
时间复杂度O(msqrt(n)log(sqrt(n)))
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
	int T[1100];
	int top,tag;
}B[1100];
int n,m,Threshold,Num;
int A[1100000];
void Restruct(int p){
	int l=(p-1)*Threshold+1,r=p*Threshold; if(r>n)r=n;
	for(int vi=l;vi<=r;vi++)B[p].T[vi-l+1]=A[vi];
	std::sort(B[p].T+1,B[p].T+B[p].top+1);
}
void Plus(int l,int r,int w){
	int pl=l/Threshold+(l%Threshold?1:0),pr=r/Threshold+(r%Threshold?1:0),vi;
	for(vi=pl+1;vi<=pr-1;vi++)B[vi].tag+=w;
	if(pl!=pr){
		for(vi=l;vi<=pl*Threshold;vi++)A[vi]+=w;
		for(vi=(pr-1)*Threshold+1;vi<=r;vi++)A[vi]+=w;
		Restruct(pl); Restruct(pr);
	}else{
		for(vi=l;vi<=r;vi++)A[vi]+=w;
		Restruct(pl);
	}
}
int Getsum(int l,int r,int w){
	int pl=l/Threshold+(l%Threshold?1:0),pr=r/Threshold+(r%Threshold?1:0),vi,sum=0,line,tl,tr,mid;
	for(vi=pl+1;vi<=pr-1;vi++){
		line=w-B[vi].tag; tl=1; tr=B[vi].top; if(B[vi].T[B[vi].top]<line)continue;
		while(tl!=tr){
			mid=((tl+tr)>>1);
			if(B[vi].T[mid]>=line)tr=mid;else tl=mid+1;
		}
		sum+=B[vi].top-tr+1;
	}
	if(pl!=pr){
		for(vi=l;vi<=pl*Threshold;vi++)sum+=(A[vi]+B[pl].tag>=w);
		for(vi=(pr-1)*Threshold+1;vi<=r;vi++)sum+=(A[vi]+B[pr].tag>=w);
	}else{
		for(vi=l;vi<=r;vi++)sum+=(A[vi]+B[pl].tag>=w);
	}
	return sum;
}
int main(){
	int i,j,l,r,w; char c;
	read(n); read(m); Threshold=ceil(sqrt(n)); Num=n/Threshold; if(Num*Threshold<n)Num++;
	for(i=1;i<=n;i++)read(A[i]);
	for(i=1;i<=Num;i++){
		l=(i-1)*Threshold+1; r=i*Threshold; if(r>n)r=n;
		for(j=l;j<=r;j++)B[i].T[++B[i].top]=A[j];
		std::sort(B[i].T+1,B[i].T+B[i].top+1);
	}
	for(i=1;i<=m;i++){
		for(c=getchar();c!='A'&&c!='M';c=getchar());
		read(l); read(r); read(w);
		if(c=='M')Plus(l,r,w);else{
			w=Getsum(l,r,w); printf("%d\n",w);
		}
	}
}