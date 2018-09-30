#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>

struct num{
	long long x;
	int p;
};
long long intp;
long long S[120000],mode[120000];
num mods[120000];
long long Sum2[120000],Sum5[120000];
int n,m,Threshold;
char c;
int B[120000],Bucket[120000];
struct inf{
	int l,r,num;
	long long ans;
};
inf Que[120000];
int nowl,nowr;
long long nowans;
char an[120000];

void Handle2(){//处理模数为2
	for(int i=n;i>=1;i--)Sum2[i]=Sum2[i+1]+(!(S[i]&1));
	for(int i=n;i>=1;i--)Sum2[i]+=Sum2[i+1];
	long long ans,drag;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int l,r;scanf("%d%d",&l,&r);
		drag=(S[r]&1)?Sum2[r]-Sum2[r+1]:Sum2[r]-Sum2[r+1]-1;
		ans=Sum2[l]-Sum2[r+1]-drag*(r-l+1); printf("%lld\n",ans);
	}
}
void Handle5(){//处理模数为5
	for(int i=n;i>=1;i--)Sum5[i]=Sum5[i+1]+(S[i]==0||S[i]==5);
	for(int i=n;i>=1;i--)Sum5[i]+=Sum5[i+1];
	long long ans,drag;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int l,r; scanf("%d%d",&l,&r);
		drag=(S[r]==0||S[r]==5)?Sum5[r]-Sum5[r+1]-1:Sum5[r]-Sum5[r+1];
		ans=Sum5[l]-Sum5[r+1]-drag*(r-l+1); printf("%lld\n",ans);
	}
}

inline bool Acmp(const num &a,const num &b){return a.x<b.x;}
inline bool Bcmp(const inf &a,const inf &b){
	return (a.l/Threshold==b.l/Threshold)?a.r<b.r:a.l/Threshold<b.l/Threshold;
}
inline bool Ccmp(const inf &a,const inf &b){return a.num<b.num;}
void Moarr(int l,int r){//莫队转移
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
void Handle(){//处理其他的情况
	scanf("%d",&m);
	n++; mods[n].p=n; Threshold=ceil(sqrt(n));
	std::sort(mods+1,mods+n+1,Acmp);
	for(int i=1;i<=m;i++)scanf("%d%d",&Que[i].l,&Que[i].r),Que[i].r++,Que[i].num=i;
	B[mods[1].p]=1;
	for(int i=2;i<=n;i++)B[mods[i].p]=(mods[i].x==mods[i-1].x)?B[mods[i-1].p]:B[mods[i-1].p]+1;
	std::sort(Que+1,Que+m+1,Bcmp);
	nowl=1;nowr=1;Bucket[B[1]]++;
	for(int i=1;i<=m;i++){
		Moarr(Que[i].l,Que[i].r);
		Que[i].ans=nowans;
	}
	std::sort(Que+1,Que+m+1,Ccmp);
	for(int i=1;i<=m;i++)printf("%lld\n",Que[i].ans);
}

int main(){
	scanf("%lld",&intp);
	scanf("%s",an+1);n=strlen(an+1);//刚开始用getchar，结果无限WA。后来看到别的大佬都是用scanf，于是就用了scanf
	for(int i=1;i<=n;i++)S[i]=an[i]-'0';
	for(int i=1;i<=n;i++)mods[i].p=i;
	mode[n]=1; mods[n].x=S[n]%intp;
	for(int i=n-1;i>=1;i--)mode[i]=mode[i+1]*10%intp,mods[i].x=(mods[i+1].x+mode[i]*S[i])%intp;
	if(intp==2)Handle2();//处理
	else
	if(intp==5)Handle5();
	else
	Handle();
}