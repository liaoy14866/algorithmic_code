#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int n,m,k,Threshold;
int nowl,nowr;
long long nowans;
int A[50010],Bucket[50010];
struct que{
	int l,r,num;
}Q[50010];
inline bool Acmp(const que &a,const que &b){
	return a.l/Threshold!=b.l/Threshold?a.l<b.l:a.r<b.r;
}
long long Ans[50010];
void Moarr(const int &l,const int &r){
	while(nowr<r){
		nowr++; nowans+=Bucket[A[nowr]]<<1|1; Bucket[A[nowr]]++;
	}
	while(nowl<l){
		nowans+=1-(Bucket[A[nowl]]<<1); Bucket[A[nowl]]--; nowl++;
	}
	while(nowl>l){
		nowl--; nowans+=Bucket[A[nowl]]<<1|1; Bucket[A[nowl]]++;
	}
	while(nowr>r){
		nowans+=1-(Bucket[A[nowr]]<<1); Bucket[A[nowr]]--; nowr--;
	}
}
int main(){
	int i;
	read(n); read(m); read(k); Threshold=n/ceil(sqrt(m)); if(!Threshold)Threshold=1;
	for(i=1;i<=n;i++)read(A[i]);
	for(i=1;i<=m;i++)read(Q[i].l),read(Q[i].r),Q[i].num=i;
	sort(Q+1,Q+m+1,Acmp);
	nowl=1; nowr=1; nowans=1; Bucket[A[1]]++;
	for(i=1;i<=m;i++){
		Moarr(Q[i].l,Q[i].r);
		Ans[Q[i].num]=nowans;
	}
	for(i=1;i<=m;i++)printf("%lld\n",Ans[i]);
}