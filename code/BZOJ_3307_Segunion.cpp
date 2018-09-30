#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int top;
struct rec{
	int x,ne;
}Arre[200010];
int Arrmap[100010];
inline void ins(const int &f,const int &s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
int Fm[100010][18],Fin[100010],Depth[100010];
int Arr[100010]; int hi,ti;
void BFS(){
	int v;
	Arr[1]=1; hi=0; ti=1; Depth[1]=1;
	while(hi!=ti){
		hi++;
		for(v=Arrmap[Arr[hi]];v;v=Arre[v].ne)if(Arre[v].x!=Fm[Arr[hi]][0]){
			ti++; Arr[ti]=Arre[v].x; Fm[Arr[ti]][0]=Arr[hi]; Fin[Arr[hi]]++; Depth[Arr[ti]]=Depth[Arr[hi]]+1;
		}
	}
	Fin[0]=0;
}
int n,m,logn;
struct opt{
	int u,v;
}O[100010];
int maxn;
struct inf{
	int x,p;
}P[100010];
inline bool Acmp(const inf &a,const inf &b){
	return a.x<b.x;
}
int B[100010],I[100010];
struct ope{
	int x,op;
};
vector<ope> T[100010];
void lcainit(){
	int vi,vj; logn=ceil(log2(n));
	for(vj=1;vj<=logn;vj++)
	for(vi=1;vi<=n;vi++)
	Fm[vi][vj]=Fm[Fm[vi][vj-1]][vj-1];
}
int lca(int u,int v){
	if(Depth[u]<Depth[v])swap(u,v); int k=Depth[u]-Depth[v],l=0;
	for(;k;k>>=1,l++)if(k&1)u=Fm[u][l];
	if(u==v)return u; if(Fm[u][0]==Fm[v][0])return Fm[u][0];
	for(;;){
		for(k=1;;k++)if(Fm[u][k]==Fm[v][k])break; k--; u=Fm[u][k]; v=Fm[v][k]; if(Fm[u][0]==Fm[v][0])return Fm[u][0];
	}
}
int root[100010];
struct node{
	int s[2];
	int maxn[2];
	/*maxn[0]是最大值，maxn[1]是最大值是谁（l==r时的l）*/
}Seg[100010*18];
void Segcopy(const int &x,const int &y){
	Seg[x].maxn[0]=Seg[y].maxn[0]; Seg[x].maxn[1]=Seg[y].maxn[1];
}
void Segunite(const int &p){
	if(Seg[Seg[p].s[1]].maxn[0]>Seg[Seg[p].s[0]].maxn[0])Segcopy(p,Seg[p].s[1]);else Segcopy(p,Seg[p].s[0]);
}
int Seginsert(int p,const int &k,const int &l,const int &r,const int &w){
	if(!p)p=++top;
	if(l==r){
		Seg[p].maxn[0]+=w; Seg[p].maxn[1]=l; return p;
	}
	int m=(l+r)>>1;
	if(k<=m)Seg[p].s[0]=Seginsert(Seg[p].s[0],k,l,m,w);else Seg[p].s[1]=Seginsert(Seg[p].s[1],k,m+1,r,w);
	Segunite(p); return p;
}
int Segmerge(const int &x,const int &y,const int &l,const int r){
	if(!x)return y; if(!y)return x;
	if(l==r){
		Seg[x].maxn[0]+=Seg[y].maxn[0]; return x;
	}
	int m=(l+r)>>1;
	Seg[x].s[0]=Segmerge(Seg[x].s[0],Seg[y].s[0],l,m); Seg[x].s[1]=Segmerge(Seg[x].s[1],Seg[y].s[1],m+1,r);
	Segunite(x);
	return x;
}
int Ans[100010];
int stk[100010]; int stktop;
void Union(){
	int vx,vi,v;
	for(vi=1;vi<=n;vi++)if(!Fin[vi])stk[++stktop]=vi;
	while(stktop){
		vx=stk[stktop]; stk[stktop--]=0;
		for(v=Arrmap[vx];v;v=Arre[v].ne)if(Arre[v].x!=Fm[vx][0])root[vx]=Segmerge(root[vx],root[Arre[v].x],1,maxn);
		for(vi=0;vi<T[vx].size();vi++)root[vx]=Seginsert(root[vx],T[vx][vi].x,1,maxn,T[vx][vi].op);
		if(Seg[root[vx]].maxn[0])Ans[vx]=Seg[root[vx]].maxn[1];
		Fin[Fm[vx][0]]--; if(!Fin[Fm[vx][0]]&&vx!=1)stk[++stktop]=Fm[vx][0];
	}
}
int main(){
	int i,u,v,l;
	read(n); read(m);
	for(i=1;i<=n-1;i++){
		read(u); read(v); ins(u,v); ins(v,u);
	}
	BFS();
	for(i=1;i<=m;i++){
		read(O[i].u); read(O[i].v); read(P[i].x); P[i].p=i;
	}
	sort(P+1,P+m+1,Acmp);
	for(i=1;i<=m;i++)B[P[i].p]=B[P[i-1].p]+(P[i].x!=P[i-1].x); maxn=B[P[m].p];
	top=0;
	for(i=1;i<=m;i++){
		if(P[i].x==P[i+1].x&&i!=m)continue;
		I[++top]=P[i].x;
	}
	lcainit();
	for(i=1;i<=m;i++){
		l=lca(O[i].u,O[i].v); T[O[i].u].push_back((ope){B[i],1}); T[O[i].v].push_back((ope){B[i],1});
		T[l].push_back((ope){B[i],-1}); T[Fm[l][0]].push_back((ope){B[i],-1});
	}
	top=0;
	Union();
	for(i=1;i<=n;i++)printf("%d\n",I[Ans[i]]);
}