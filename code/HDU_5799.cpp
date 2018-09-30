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
long long tmc;
long long gcd(long long x,long long y){
	if(!x)return y; if(!y)return x;
	for(tmc=x%y;tmc;x=y,y=tmc,tmc=x%y);
	return y;
}
int T;
int n,m,Threshold,logn;
struct inf{
	int x,p;
}P[100010];
int val[100010];
inline bool Bcmp(const inf &a,const inf &b){
	return a.x<b.x;
}
int S[100010];
struct rec{
	int x,ne;
}Arre[200010];
int Arrmap[100010];
int top,cnt;
void ins(int f,int s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
int Fm[100010][18],Depth[100010];
int Size[100010],PIH[100010],A[100010],BIA[100010];
/*A是按照DFS序处理的权值*/
void DFS(int f,int x,int d){
	int v; Size[x]=1; Fm[x][0]=f; Depth[x]=d; cnt++; A[cnt]=S[x]; PIH[x]=cnt;
	for(v=Arrmap[x];v;v=Arre[v].ne)if(Arre[v].x!=f){
		DFS(x,Arre[v].x,d+1); Size[x]+=Size[Arre[v].x];
	}
}
int Subtop,Pathtop;
struct que{
	int x,y,a,b,num;
}SubQ[100010],PathQ[100010];
inline bool Acmp(const que &a,const que &b){
	return a.x/Threshold!=b.x/Threshold?a.x<b.x:a.y<b.y;
}
void init(){
	int vi,u,v,opt;
	for(vi=1;vi<=top;vi++)Arre[vi].x=Arre[vi].ne=0;
	for(vi=1;vi<=n;vi++)Arrmap[vi]=0;
	top=cnt=Subtop=Pathtop=0;
	read(n); read(m);
	for(vi=1;vi<=n;vi++)read(P[vi].x),P[vi].p=vi,val[vi]=P[vi].x;
	sort(P+1,P+n+1,Bcmp);
	S[P[1].p]=1; for(vi=2;vi<=n;vi++)S[P[vi].p]=S[P[vi-1].p]+(P[vi].x!=P[vi-1].x);
	for(vi=1;vi<=n-1;vi++){
		read(u); read(v); ins(u,v); ins(v,u);
	}
	cnt=0; DFS(0,1,1);
	for(vi=1;vi<=n;vi++)BIA[PIH[vi]]=vi;
	for(vi=1;vi<=m;vi++){
		read(opt);
		if(opt==1){
			Subtop++; read(SubQ[Subtop].x); read(SubQ[Subtop].y); read(SubQ[Subtop].a); read(SubQ[Subtop].b);
			SubQ[Subtop].y=PIH[SubQ[Subtop].x]+Size[SubQ[Subtop].x]-1; SubQ[Subtop].x=PIH[SubQ[Subtop].x]; 
			SubQ[Subtop].num=vi;
		}else{
			Pathtop++; read(PathQ[Pathtop].x); read(PathQ[Pathtop].y); read(PathQ[Pathtop].a); read(PathQ[Pathtop].b);
			if(PIH[PathQ[Pathtop].x]>PIH[PathQ[Pathtop].y])swap(PathQ[Pathtop].x,PathQ[Pathtop].y);
			PathQ[Pathtop].num=vi;
		}
	}
	Threshold=n/ceil(sqrt(Subtop)); if(!Threshold)Threshold=1;
	sort(SubQ+1,SubQ+Subtop+1,Acmp);
	Threshold=n/ceil(sqrt(Pathtop)); if(!Threshold)Threshold=1;
	sort(PathQ+1,PathQ+Pathtop+1,Acmp);
}
long long Ans[100010];
int nowl,nowr;
int Bucket[100010];
long long Sum[100010];
void SubIN(int x){
	Sum[Bucket[A[x]]]-=val[BIA[x]];
	Bucket[A[x]]++;
	Sum[Bucket[A[x]]]+=val[BIA[x]];
}
void SubOU(int x){
	Sum[Bucket[A[x]]]-=val[BIA[x]];
	Bucket[A[x]]--;
	Sum[Bucket[A[x]]]+=val[BIA[x]];
}
void SubMoarr(int l,int r){
	while(nowl>l){
		nowl--; SubIN(nowl);
	}
	while(nowr>r){
		SubOU(nowr); nowr--;
	}
	while(nowr<r){
		nowr++; SubIN(nowr);
	}
	while(nowl<l){
		SubOU(nowl); nowl++;
	} 
}
void Subhandle(){
	int vi;
	for(vi=1;vi<=n;vi++)Bucket[vi]=Sum[vi]=0;
	nowl=1; nowr=1; SubIN(1);
	for(vi=1;vi<=Subtop;vi++){
		SubMoarr(SubQ[vi].x,SubQ[vi].y);
		Ans[SubQ[vi].num]=gcd(Sum[SubQ[vi].a],Sum[SubQ[vi].b]);
	}
}
void lcainit(){
	int vi,vj; logn=ceil(log2(n));
	for(vj=1;vj<=logn;vj++)
	for(vi=1;vi<=n;vi++)Fm[vi][vj]=Fm[Fm[vi][vj-1]][vj-1];
}
int lca(int u,int v){
	int vk,vl;
	if(Depth[u]<Depth[v])swap(u,v); vk=Depth[u]-Depth[v];
	for(vl=0;vk;vk>>=1,vl++)if(vk&1)u=Fm[u][vl];
	if(u==v)return u; if(Fm[u][0]==Fm[v][0])return Fm[u][0];
	for(;;){
		for(vk=1;;vk++)if(Fm[u][vk]==Fm[v][vk])break; vk--;
		u=Fm[u][vk]; v=Fm[v][vk]; if(Fm[u][0]==Fm[v][0])return Fm[u][0];
	}
}
int vis[100010];
void Reverse(int x){
	Sum[Bucket[S[x]]]-=val[x];
	Bucket[S[x]]+=1-(vis[x]<<1);
	vis[x]^=1;
	Sum[Bucket[S[x]]]+=val[x];
}
void PathMoarr(int x,int y){
	while(x!=y)
	if(Depth[x]>Depth[y])Reverse(x),x=Fm[x][0];else Reverse(y),y=Fm[y][0];
}
void Pathhandle(){
	int vi,vt;
	for(vi=1;vi<=n;vi++)Sum[vi]=Bucket[vi]=0;
	if(!Pathtop)return;
	for(vi=1;vi<=n;vi++)vis[vi]=0;
	PathMoarr(PathQ[1].x,PathQ[1].y);
	vt=lca(PathQ[1].x,PathQ[1].y); Reverse(vt);
	Ans[PathQ[1].num]=gcd(Sum[PathQ[1].a],Sum[PathQ[1].b]);
	Reverse(vt);
	for(vi=2;vi<=Pathtop;vi++){
		PathMoarr(PathQ[vi-1].x,PathQ[vi].x);
		PathMoarr(PathQ[vi-1].y,PathQ[vi].y);
		vt=lca(PathQ[vi].x,PathQ[vi].y); Reverse(vt);
		Ans[PathQ[vi].num]=gcd(Sum[PathQ[vi].a],Sum[PathQ[vi].b]);
		Reverse(vt);
	}
}
void Show(){
	int vi;
	for(vi=1;vi<=m;vi++)printf("%I64d\n",Ans[vi]);
}
int main(){
	read(T);
	for(int al=1;al<=T;al++){
		init();
		Subhandle();
		lcainit();
		Pathhandle();
		printf("Case #%d:\n",al);
		Show();
	}
}