#include<cstdio>
#include<algorithm>
using namespace std;
const int none=1e9+7;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
int T;
int n,m;
struct inf{
	int v,d;
}A[20010];
struct que{
	int l,r,c,sum,num;
}Q[100010],TEMP[100010];
bool Ans[100010];
void init(){
	int vi;
	read(n); read(m);
	for(vi=1;vi<=n;vi++)read(A[vi].v);
	for(vi=1;vi<=n;vi++)read(A[vi].d);
	for(vi=1;vi<=m;vi++)read(Q[vi].l),read(Q[vi].r),read(Q[vi].c),read(Q[vi].sum),Q[vi].num=vi;
}
int F[20010][110],G[20010][110];
void Div(int nl,int nr,int ql,int qr){
	int vi,vj,mid=(nl+nr)>>1,tl,tr,mind;
	if(ql>qr)return;
	if(nl==nr){
		for(vi=ql;vi<=qr;vi++)Ans[Q[vi].num]=(A[nl].d<=Q[vi].c&&A[nl].v==Q[vi].sum);
		return;
	}
	
	for(vi=nl;vi<=nr;vi++)
	for(vj=1;vj<=100;vj++)F[vi][vj]=G[vi][vj]=none;
	
	F[mid][A[mid].v]=A[mid].d;
	for(vi=mid-1;vi>=nl;vi--)//注意F[][0]与G[][0]是0，初始化 
	for(vj=1;vj<=100;vj++){
		F[vi][vj]=F[vi+1][vj];
		if(vj-A[vi].v>=0)F[vi][vj]=min(F[vi][vj],max(F[vi+1][vj-A[vi].v],A[vi].d));
	}
	
	G[mid+1][A[mid+1].v]=A[mid+1].d;
	for(vi=mid+2;vi<=nr;vi++)
	for(vj=1;vj<=100;vj++){
		G[vi][vj]=G[vi-1][vj];
		if(vj-A[vi].v>=0)G[vi][vj]=min(G[vi][vj],max(G[vi-1][vj-A[vi].v],A[vi].d));
	}
	
	for(tl=ql,tr=qr,vi=ql;vi<=qr;vi++)
	if(Q[vi].r<=mid)TEMP[tl++]=Q[vi];
	else
	if(Q[vi].l>=mid+1)TEMP[tr--]=Q[vi];
	else{
		mind=min(F[Q[vi].l][Q[vi].sum],G[Q[vi].r][Q[vi].sum]);
		for(vj=1;vj<=Q[vi].sum-1;vj++)mind=min(mind,max(F[Q[vi].l][vj],G[Q[vi].r][Q[vi].sum-vj]));
		Ans[Q[vi].num]=(mind<=Q[vi].c);
	}
	tl--; tr++;
	for(vi=ql;vi<=tl;vi++)Q[vi]=TEMP[vi];
	for(vi=tr;vi<=qr;vi++)Q[vi]=TEMP[vi];
	Div(nl,mid,ql,tl);
	Div(mid+1,nr,tr,qr);
}
void Show(){
	int vi;
	for(vi=1;vi<=m;vi++)if(Ans[vi])printf("0");else printf("1");
	printf("\n");
}
int main(){
	read(T);
	for(int al=1;al<=T;al++){
		init();
		Div(1,n,1,m);
		Show();
	}
}