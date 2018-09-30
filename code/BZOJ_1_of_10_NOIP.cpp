#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
const int none=1e9+7;
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int n,m;
struct rec{
	int u,v,minn,maxn,num;
}E[70010];
int L[70010],R[70010];
struct que{
	int q,num;
	bool operator <(const que &a)const{
		return q<a.q;
	}
}Q[70010],ftmp;
struct inf{
	int x,ne;
}Arre[70010*2];
int Arrmap[70010];
int top;
inline void ins(int f,int s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
int ST[70010*2],PIS[70010],Depth[70010];
void DFS(int f,int x,int d){
	ST[++top]=Depth[x]=d; PIS[x]=top; int v;
	for(v=Arrmap[x];v;v=Arre[v].ne)if(Arre[v].x!=f){
		DFS(x,Arre[v].x,d+1); ST[++top]=d;
	}
}
int Lmin[70010*2][18],Rmin[70010*2][18];
void lcainit(){
	int logtop=ceil(log2(top)); int vi,vj;
	for(vi=1;vi<=top;vi++)Lmin[vi][0]=Rmin[vi][0]=ST[vi];
	for(vj=1;vj<=logtop;vj++)
	for(vi=1;vi<=top;vi++){
		if(vi+(1<<vj)-1<=top)Lmin[vi][vj]=min(Lmin[vi][vj-1],Lmin[vi+(1<<(vj-1))][vj-1]);
		if(vi-(1<<vj)+1>=1)Rmin[vi][vj]=min(Rmin[vi][vj-1],Rmin[vi-(1<<(vj-1))][vj-1]);
	}
}
int tmpl,tmpr,loglen;
int mindepth(int u,int v){
	tmpl=PIS[u]; tmpr=PIS[v]; if(tmpl>tmpr)swap(tmpl,tmpr); loglen=floor(log2(tmpr-tmpl+1));
	return min(Lmin[tmpl][loglen],Rmin[tmpr][loglen]);
}
int dis(int u,int v){
	return Depth[u]+Depth[v]-(mindepth(u,v)<<1);
}
int nowans;
int Fa[70010],Size[70010];
int Getfa(int u){
	for(;u!=Fa[u];u=Fa[u]); return u;
}
struct fur{
	int u,v;
}U[70010];
struct opt{
	int x,y,u,v,ans;
	//把x的父亲变为了y，x的U（直径的点）还是原来的，y的U应该是{u,v}（结构体里面记录的玩意），记录做此操作前的ans 
	//特别的，如果x为0表示没有操作，或者是操作失败 
}O[70010];
int fu,fv,tmpu,tmpv,tmpdis;
void diameter(int u1,int v1,int u2,int v2){
	tmpdis=0; tmpu=u1; tmpv=v1;
	if(dis(u1,v1)>=tmpdis){tmpdis=dis(u1,v1),tmpu=u1,tmpv=v1;}
	if(dis(u1,v2)>=tmpdis){tmpdis=dis(u1,v2),tmpu=u1,tmpv=v2;}
	if(dis(u2,v1)>=tmpdis){tmpdis=dis(u2,v1),tmpu=u2,tmpv=v1;}
	if(dis(u2,v2)>=tmpdis){tmpdis=dis(u2,v2),tmpu=u2,tmpv=v2;}
	if(dis(u1,u2)>=tmpdis){tmpdis=dis(u1,u2),tmpu=u1,tmpv=u2;}
	if(dis(v1,v2)>=tmpdis){tmpdis=dis(v1,v2),tmpu=v1,tmpv=v2;}
}
void Union(int p,int u,int v){
	fu=Getfa(u),fv=Getfa(v); if(fu==fv)return;
	if(Size[fu]>Size[fv])swap(fu,fv);
	O[p].x=fu; O[p].y=fv; O[p].u=U[fv].u; O[p].v=U[fv].v; O[p].ans=nowans;
	Fa[fu]=fv; Size[fv]+=Size[fu];
	diameter(U[fu].u,U[fu].v,U[fv].u,U[fv].v); U[fv].u=tmpu; U[fv].v=tmpv; nowans=max(nowans,tmpdis);
}
void Cancel(int p){
	if(!O[p].x)return;
	Fa[O[p].x]=O[p].x; Size[O[p].y]-=Size[O[p].x]; U[O[p].y].u=O[p].u; U[O[p].y].v=O[p].v; nowans=O[p].ans;
	O[p].x=O[p].y=O[p].u=O[p].v=O[p].ans=0;
}
struct node{
	int l,r,m;
	vector<rec> E;
}Seg[70010<<2];
void Segbuild(int p,int l,int r){
	Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1;
	if(l==r)return;
	Segbuild(p<<1,l,Seg[p].m); Segbuild(p<<1|1,Seg[p].m+1,r);
}
void Segput(int p,int l,int r,const rec &x){
	if(Seg[p].l==l&&Seg[p].r==r){
		Seg[p].E.push_back(x);
		return;
	}
	if(r<=Seg[p].m)Segput(p<<1,l,r,x);
	else
	if(Seg[p].m+1<=l)Segput(p<<1|1,l,r,x);
	else
	Segput(p<<1,l,Seg[p].m,x),Segput(p<<1|1,Seg[p].m+1,r,x);
}
int Ans[70010];
void SegDiv(int p,int l,int r){
	int vi;
	for(vi=0;vi<Seg[p].E.size();vi++)Union(Seg[p].E[vi].num,Seg[p].E[vi].u,Seg[p].E[vi].v);
	if(l==r){
		Ans[l]=nowans;
	}else{
		SegDiv(p<<1,l,Seg[p].m);
		SegDiv(p<<1|1,Seg[p].m+1,r);
	}
	for(vi=Seg[p].E.size()-1;vi>=0;vi--)Cancel(Seg[p].E[vi].num);
}
int main(){
	int i;
	read(n); read(m);
	for(i=1;i<=n-1;i++){
		read(E[i].u); read(E[i].v); read(E[i].minn); read(E[i].maxn); E[i].num=i; ins(E[i].u,E[i].v); ins(E[i].v,E[i].u);
	}
	for(i=1;i<=n;i++){
		Fa[i]=i; U[i].u=U[i].v=i; Size[i]=1;
	}
	top=0; DFS(0,1,1);
	lcainit();
	for(i=1;i<=m;i++){
		read(Q[i].q); Q[i].num=i;
	}
	Segbuild(1,1,m);
	sort(Q+1,Q+m+1); Q[m+1].num=m+1; Q[m+1].q=none;
	for(i=1;i<=n-1;i++){
		ftmp.q=E[i].minn; L[i]=lower_bound(Q+1,Q+m+2,ftmp)->num;
		ftmp.q=E[i].maxn; R[i]=upper_bound(Q+1,Q+m+2,ftmp)->num-1;
		if(L[i]<=R[i])Segput(1,L[i],R[i],E[i]);
	}
	SegDiv(1,1,m);
	for(i=1;i<=m;i++)printf("%d\n",Ans[Q[i].num]);
}