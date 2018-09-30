#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
int n,m,Threshold;
int nowl,nowr;
long long nowans;
struct inf{
	int x,p;
}P[100010];
inline bool Bcmp(const inf &a,const inf &b){
	return a.x<b.x;
}
int A[100010];
struct que{
	int l,r,num;
}Q[100010];
inline bool Acmp(const que &a,const que &b){
	return a.l/Threshold!=b.l/Threshold?a.l<b.l:a.r<b.r;
}
int Bucket[100010];
long long Ans[100010];
long long SQQ(int x){
	return (long long)x*x*x;
}
void Moarr(int l,int r){
	while(nowl>l){
		nowl--; nowans-=SQQ(Bucket[A[nowl]]); Bucket[A[nowl]]++; nowans+=SQQ(Bucket[A[nowl]]);
	}
	while(nowr>r){
		nowans-=SQQ(Bucket[A[nowr]]); Bucket[A[nowr]]--; nowans+=SQQ(Bucket[A[nowr]]); nowr--;
	}
	while(nowr<r){
		nowr++; nowans-=SQQ(Bucket[A[nowr]]); Bucket[A[nowr]]++; nowans+=SQQ(Bucket[A[nowr]]);
	}
	while(nowl<l){
		nowans-=SQQ(Bucket[A[nowl]]); Bucket[A[nowl]]--; nowans+=SQQ(Bucket[A[nowl]]); nowl++;
	}
}
int main(){
	int i;
	while(scanf("%d",&n)!=EOF){
		for(i=1;i<=n;i++)read(P[i].x),P[i].p=i;
		sort(P+1,P+n+1,Bcmp);
		A[P[1].p]=1; for(i=2;i<=n;i++)A[P[i].p]=A[P[i-1].p]+(P[i].x!=P[i-1].x);
		read(m);
		for(i=1;i<=m;i++)read(Q[i].l),read(Q[i].r),Q[i].num=i;
		Threshold=n/ceil(sqrt((double)m)); if(!Threshold)Threshold=1;//不换double就判编译错误……
		sort(Q+1,Q+m+1,Acmp);
		memset(Bucket,0,sizeof(Bucket));
		nowl=1; nowr=1; Bucket[A[1]]++; nowans=1;
		for(i=1;i<=m;i++){
			Moarr(Q[i].l,Q[i].r);
			Ans[Q[i].num]=nowans;
		}
		for(i=1;i<=m;i++)printf("%I64d\n",Ans[i]);
	}
}