/*
题目大意：给出一个长度为n的序列，给出m次询问，查询区间逆序对的个数
个人解法：莫队+树状数组即可。
树状数组维护当前的桶
*/
#include<cstdio>
#include<algorithm>
#include<cmath>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,Threshold,maxn;
struct inf{
	int x,p;
}B[51000];
inline bool Acmp(const inf &a,const inf &b){
	return a.x<b.x;
}
int C[51000];
void Change(int p,int w){
	for(;p<=maxn;p+=p&-p)C[p]+=w;
}
int Getsum(int p){
	int sum=0; for(;p;p-=p&-p)sum+=C[p]; return sum;
}
struct que{
	int l,r,num;
	long long ans;
}Q[51000];
inline bool Bcmp(const que &a,const que &b){
	return a.l/Threshold==b.l/Threshold?a.r<b.r:a.l/Threshold<b.l/Threshold;
}
inline bool Ccmp(const que &a,const que &b){
	return a.num<b.num;
}
int A[51000];
int nowl,nowr;
long long ans;
void Moarr(int l,int r){
	while(nowl>l){
		nowl--; ans+=Getsum(A[nowl]-1); Change(A[nowl],1);
	}
	while(nowr>r){
		Change(A[nowr],-1); ans-=Getsum(maxn)-Getsum(A[nowr]); nowr--;
	}
	while(nowr<r){
		nowr++; ans+=Getsum(maxn)-Getsum(A[nowr]); Change(A[nowr],1);
	}
	while(nowl<l){
		Change(A[nowl],-1); ans-=Getsum(A[nowl]-1); nowl++;
	}
}
int main(){
	int i;
	read(n);
	for(i=1;i<=n;i++){
		read(B[i].x); B[i].p=i;
	}
	std::sort(B+1,B+n+1,Acmp);
	A[B[1].p]=1; for(i=2;i<=n;i++)A[B[i].p]=A[B[i-1].p]+(B[i].x!=B[i-1].x); maxn=A[B[n].p]+1;
	read(m); Threshold=n/ceil(sqrt(m)); if(!Threshold)Threshold=1;
	for(i=1;i<=m;i++){
		read(Q[i].l); read(Q[i].r); Q[i].num=i;
	}
	std::sort(Q+1,Q+m+1,Bcmp);
	nowl=1; nowr=1; Change(A[1],1);
	for(i=1;i<=m;i++){
		Moarr(Q[i].l,Q[i].r);
		Q[i].ans=ans;
	}
	std::sort(Q+1,Q+m+1,Ccmp);
	for(i=1;i<=m;i++)printf("%lld\n",Q[i].ans);
}