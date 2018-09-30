#include<cstdio>
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
int n,m;
int top;
struct rec{
	int x,ne;
}Etree[50010];
int Tree[50010];
void ins(int f,int s){
	top++; Etree[top].x=s; Etree[top].ne=Tree[f]; Tree[f]=top;
}
struct inf{
	int a,b;
}A[50010],tmp[50010];
int DFA[50010],PID[50010],Size[50010];
void DFS(int x){
	top++; DFA[top]=x; PID[x]=top; Size[x]=1; int v;
	for(v=Tree[x];v;v=Etree[v].ne){
		DFS(Etree[v].x); Size[x]+=Size[Etree[v].x];
	}
}
void init(){
	int vi,fu;
	for(vi=1;vi<=n;vi++)Tree[vi]=0;
	for(vi=1;vi<=top;vi++)Etree[vi].x=Etree[vi].ne=0; top=0;
	read(n); read(m);
	for(vi=2;vi<=n;vi++){
		read(fu); fu++; ins(fu,vi); read(A[vi].a); read(A[vi].b);
	}
	top=0; DFS(1);
	for(vi=1;vi<=n;vi++)tmp[vi]=A[DFA[vi]];
	for(vi=1;vi<=n;vi++)A[vi]=tmp[vi];
}
int Threshold,Num;
struct block{
	int top;
	int T[900],SufT[900];
}B[60];
inline bool Acmp(int x,int y){
	return A[x].b<A[y].b;
}
int Getmax(int l,int r,const inf &x){
	/*序列已经全部转换为A*/
	int pl=(l-1)/Threshold+1,pr=(r-1)/Threshold+1,vi,anspos=0;
	int tl,tr,tmid;
	for(vi=pl+1;vi<=pr-1;vi++){
		if(A[B[vi].T[B[vi].top]].b<=x.b)continue;
		tl=1; tr=B[vi].top;
		while(tl!=tr){
			tmid=(tl+tr)>>1;
			if(A[B[vi].T[tmid]].b>x.b)tr=tmid;else tl=tmid+1;
		}
		if(A[B[vi].SufT[tr]].a>A[anspos].a)anspos=B[vi].SufT[tr];
	}
	if(pl!=pr){
		for(vi=l;vi<=pl*Threshold;vi++)if(A[vi].a>A[anspos].a&&A[vi].b>x.b)anspos=vi;
		for(vi=(pr-1)*Threshold+1;vi<=r;vi++)if(A[vi].a>A[anspos].a&&A[vi].b>x.b)anspos=vi;
	}else for(vi=l;vi<=r;vi++)if(A[vi].a>A[anspos].a&&A[vi].b>x.b)anspos=vi;
	return DFA[anspos]-1;
}
void handle(){
	int vi,vj,u,l,r,maxn;
	Threshold=ceil(sqrt(n*log2(n))); Num=n/Threshold; if(Num*Threshold<n)Num++;
	for(vi=1;vi<=Num;vi++){
		l=(vi-1)*Threshold+1; r=vi*Threshold; if(r>n)r=n; B[vi].top=r-l+1;
		for(vj=l;vj<=r;vj++)B[vi].T[vj-l+1]=vj;
		sort(B[vi].T+1,B[vi].T+B[vi].top+1,Acmp);
		maxn=0;
		for(vj=B[vi].top;vj>=1;vj--){
			B[vi].SufT[vj]=B[vi].SufT[vj+1];
			if(A[B[vi].T[vj]].a>maxn)B[vi].SufT[vj]=B[vi].T[vj],maxn=A[B[vi].T[vj]].a;
		}
	}
	for(vi=1;vi<=m;vi++){
		read(u); u++; l=PID[u]; r=PID[u]+Size[u]-1;
		maxn=Getmax(l,r,A[PID[u]]); if(maxn!=-1)printf("%d\n",maxn);else printf("-1\n");
	}
}
int main(){
	read(T);
	for(int al=1;al<=T;al++){
		init();
		handle();
	}
}