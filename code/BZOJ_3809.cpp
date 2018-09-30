#include<cstdio>
#include<cmath>
#include<algorithm>

struct inf1{
	int l,r,minn,maxn,ans,num;
};
int n,m,Threshold,Num,nowl,nowr;
int A[100005];
inf1 Que[1000005];
struct inf2{
	int sum;
};
int Bucket[100005],Belong[100005];
inf2 Block[350];
char c;

inline void read(int &a){//既然提醒了读优，就写一个好咯
	for(c=getchar();c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}

inline bool Acmp(const inf1 &a,const inf1 &b){
	return (a.l/Threshold==b.l/Threshold)?a.r<b.r:a.l/Threshold<b.l/Threshold;
}
inline bool Bcmp(const inf1 &a,const inf1 &b){
	return a.num<b.num;
}
inline void Change(int p,int w){//分块单点修改
	Bucket[p]+=w;
	if((w>0&&Bucket[p]==1)||(w<0&&Bucket[p]==0))Block[Belong[p]].sum+=w;
}

int Getsum(int l,int r){//分块区间查询
	int pl=Belong[l],pr=Belong[r],sum=0;
	for(int vi=pl+1;vi<=pr-1;vi++)sum+=Block[vi].sum;
	if(pl!=pr){
		for(int vi=l;vi<=pl*Threshold;vi++)sum+=(Bucket[vi]>0);
		for(int vi=(pr-1)*Threshold+1;vi<=r;vi++)sum+=(Bucket[vi]>0);
	}
	else for(int vi=l;vi<=r;vi++)sum+=(Bucket[vi]>0);
	return sum;
}

void Moarr(int l,int r){//莫队转移
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

int main(){
	read(n); read(m);//读入
	Threshold=ceil(sqrt(n)); Num=n/Threshold; if(Num*Threshold<n)Num++;
	for(int i=1;i<=n;i++)read(A[i]);
	for(int i=1;i<=m;i++)
	scanf("%d%d%d%d",&Que[i].l,&Que[i].r,&Que[i].minn,&Que[i].maxn),Que[i].num=i;
	std::sort(Que+1,Que+m+1,Acmp);//莫队排序
	for(int i=1;i<=Num;i++){//分块
		int l=(i-1)*Threshold+1,r=i*Threshold; if(r>n)r=n;
		for(int j=l;j<=r;j++)Belong[j]=i;
	}
	nowl=1; nowr=1; Change(A[1],1);
	for(int i=1;i<=m;i++){//莫队转移
		Moarr(Que[i].l,Que[i].r);
		Que[i].ans=Getsum(Que[i].minn,Que[i].maxn);
	}
	std::sort(Que+1,Que+m+1,Bcmp);//时间排序
	for(int i=1;i<=m;i++)printf("%d\n",Que[i].ans);//输出
}