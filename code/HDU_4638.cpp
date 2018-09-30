#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
int T;
int n,m,Threshold,Num;
int A[100010];
struct que{
	int l,r,num;
}Q[100010];
inline bool Acmp(const que &a,const que &b){
	return a.l/Threshold!=b.l/Threshold?a.l<b.l:a.r<b.r;
}
int Bucket[100010],Belong[100010];
bool R[100010],L[100010];
/*判断是否是块的边界*/
struct inf{
	bool fl[2];//fl[0]位1表示左端点是有值的，fl[1]表示右端点……
	int num,top;
}B[350];
int po;
inline void IN(int x){
	po=Belong[x];
	B[po].num++; Bucket[x]++;
	if(Bucket[x-1]&&!L[x])B[po].num--; if(Bucket[x+1]&&!R[x])B[po].num--;
	if(L[x])B[po].fl[0]=1; if(R[x])B[po].fl[1]=1;
}
inline void OUT(int x){
	po=Belong[x];
	B[po].num--; Bucket[x]--;
	if(Bucket[x-1]&&!L[x])B[po].num++; if(Bucket[x+1]&&!R[x])B[po].num++;
	if(L[x])B[po].fl[0]=0; if(R[x])B[po].fl[1]=0;
}
int nowl,nowr,nowans;
void Getsum(){
	nowans=0; int vi;
	for(vi=1;vi<Num;vi++)nowans+=B[vi].num-(B[vi].fl[1]&&B[vi+1].fl[0]);
	nowans+=B[Num].num;
}
void Moarr(int l,int r){
	while(nowl>l){
		nowl--; IN(A[nowl]);
	}
	while(nowr>r){
		OUT(A[nowr]); nowr--;
	}
	while(nowr<r){
		nowr++; IN(A[nowr]);
	}
	while(nowl<l){
		OUT(A[nowl]); nowl++;
	}
}
int Ans[100010];
int main(){
	int i,j,l,r;
	read(T);
	for(int al=1;al<=T;al++){	
		read(n); read(m);
		for(i=1;i<=n;i++)read(A[i]);
		for(i=1;i<=m;i++){
			read(Q[i].l); read(Q[i].r); Q[i].num=i;
		}
		Threshold=n/ceil(sqrt(m)); if(!Threshold)Threshold=1;
		sort(Q+1,Q+m+1,Acmp);
		Threshold=ceil(sqrt(n)); Num=n/Threshold; if(Num*Threshold<n)Num++;
		for(i=1;i<Num;i++){
			B[i].top=Threshold,L[(i-1)*Threshold+1]=1,R[i*Threshold]=1;
			l=(i-1)*Threshold+1; r=i*Threshold;
			for(j=l;j<=r;j++)Belong[j]=i;
		}
		B[Num].top=n-(Num-1)*Threshold; L[(Num-1)*Threshold+1]=1; R[n]=1;
		for(j=(Num-1)*Threshold+1;j<=n;j++)Belong[j]=Num;
		nowl=1; nowr=1; IN(A[1]);
		for(i=1;i<=m;i++){
			Moarr(Q[i].l,Q[i].r);
			Getsum();
			Ans[Q[i].num]=nowans;
		}
		for(i=1;i<=m;i++)printf("%d\n",Ans[i]);	
		memset(Bucket,0,sizeof(Bucket));
		for(i=1;i<=Num;i++){
			L[(i-1)*Threshold+1]=0; r=i*Threshold; if(r>n)r=n; R[r]=0;
			B[i].fl[0]=B[i].fl[1]=0;B[i].num=B[i].top=0;
		}
	}
}