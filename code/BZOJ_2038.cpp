#include<cstdio>
#include<algorithm>
#include<cmath>
struct num{
	int A,P;
};
struct inf{
	int l,r,num;
	long long ans,len;
};
int n,m,Threshold,nowl,nowr;
long long nowans;
num A[52000];
int B[52000],Bucket[52000];
inf Que[52000];

inline bool Acmp(const num &a,const num &b){return a.A<b.A;}
inline bool Bcmp(const inf &a,const inf &b){
	return (a.l/Threshold==b.l/Threshold)?a.r<b.r:a.l/Threshold<b.l/Threshold;
}
inline bool Ccmp(const inf &a,const inf &b){return a.num<b.num;}//三个排序的指针

void Moarr(int l,int r){//莫队转移
/*
如果是去除元素，那么先更新Bucket，再更新答案，再移动指针
如果是增加元素，那么先移动指针，在更新答案，再更新Bucket
*/
	while(nowl>l){
		nowl--; nowans+=Bucket[B[nowl]]; Bucket[B[nowl]]++;
	}
	while(nowr>r){
		Bucket[B[nowr]]--; nowans-=Bucket[B[nowr]]; nowr--;
	}
	while(nowr<r){
		nowr++; nowans+=Bucket[B[nowr]]; Bucket[B[nowr]]++;
	}
	while(nowl<l){
		Bucket[B[nowl]]--; nowans-=Bucket[B[nowl]]; nowl++;
	}
}
long long gcd(long long a,long long b){
	long long c=a%b;
	while(c){a=b;b=c;c=a%b;}
	return b;
}
int main(){
	scanf("%d%d",&n,&m); Threshold=ceil(sqrt(n));
	for(int i=1;i<=n;i++)scanf("%d",&A[i].A),A[i].P=i;
	std::sort(A+1,A+n+1,Acmp);//离散排序
	for(int i=1;i<=n;i++)B[A[i].P]=(A[i].A==A[i-1].A)?B[A[i-1].P]:B[A[i-1].P]+1;
	for(int i=1;i<=m;i++)scanf("%d%d",&Que[i].l,&Que[i].r),Que[i].num=i;
	std::sort(Que+1,Que+m+1,Bcmp);//莫队排序
	nowl=1; nowr=1; Bucket[B[1]]++;
	for(int i=1;i<=m;i++){
		Moarr(Que[i].l,Que[i].r);//莫队转移
		Que[i].ans=nowans;
	}
	std::sort(Que+1,Que+m+1,Ccmp);//时间排序
	for(int i=1;i<=m;i++){
		Que[i].len=(long long)(Que[i].r-Que[i].l+1)*(long long)(Que[i].r-Que[i].l)/2;
		long long gys=gcd(Que[i].ans,Que[i].len);
		Que[i].ans/=gys; Que[i].len/=gys;
		printf("%lld/%lld\n",Que[i].ans,Que[i].len);
	}
}