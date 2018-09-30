#include<cstdio>
#include<algorithm>
#include<cmath>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,Threshold;
int A[210000];
struct inf{//分块维护桶
	int num;
	int Bucket[470];
	void change(int p,int data){
		Bucket[p]+=data;
		if(data==-1&&!Bucket[p])num--;
		else if(data==1&&Bucket[p]==1)num++;
	}
	int getans(){
		for(int vi=1;vi<=Threshold;vi++)if(!Bucket[vi])return vi;
		return 0;
	}
}B[470];
void Change(int p,int data){//修改
	int po=p/Threshold+(p%Threshold?1:0); B[po].change(p-(po-1)*Threshold,data);
}
int Getans(){//查询
	int p,v;
	for(p=1;B[p].num==Threshold;p++);
	v=B[p].getans(); return (p-1)*Threshold+v;
}
struct que{
	int l,r,num,ans;
}Q[210000];
inline bool Acmp(const que &a,const que &b){
	return a.l/Threshold==b.l/Threshold?a.r<b.r:a.l/Threshold<b.l/Threshold;
}
int nowl,nowr;//莫队
void Moarr(int l,int r){
	while(nowl>l){
		nowl--; Change(A[nowl],1);
	}
	while(nowr>r){
		Change(A[nowr],-1); nowr--;
	}
	while(nowr<r){
		nowr++; Change(A[nowr],1);
	}
	while(nowl<l){
		Change(A[nowl],-1); nowl++;
	}
}
int Ans[210000];
int main(){
	int i;
	read(n); read(m); Threshold=ceil(n/sqrt(m));
	for(i=1;i<=n;i++){
		read(A[i]); A[i]++; if(A[i]>n+2)A[i]=n+2;//先把A[i]++，避免0的问题。由于n+1以上的不可能成为答案，于是不管它就好了
	}
	for(i=1;i<=m;i++){
		read(Q[i].l); read(Q[i].r); Q[i].num=i;
	}
	std::sort(Q+1,Q+m+1,Acmp);//排序
	Threshold=ceil(sqrt(n));
	nowl=1; nowr=1; Change(A[1],1);
	for(i=1;i<=m;i++){
		Moarr(Q[i].l,Q[i].r);
		Q[i].ans=Getans(); Q[i].ans--;//注意把答案减回来
	}
	for(i=1;i<=m;i++)Ans[Q[i].num]=Q[i].ans;
	for(i=1;i<=m;i++)printf("%d\n",Ans[i]);//输出
}