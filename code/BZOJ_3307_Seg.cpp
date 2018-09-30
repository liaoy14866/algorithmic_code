#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int n,m;
struct rec{
	int x,ne;
}Arre[200010];
int Arrmap[100010];
int top;
inline void ins(const int &f,const int &s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
int PIH[100010],Depth[100010],Fa[100010],Wson[100010],Size[100010],Top[100010];
int hi,ti;
int Arr[100010],stk[100010],Fin[100010]; int stktop;
void BFS1(){
	hi=0; ti=1; Arr[1]=1; Depth[1]=1; int v,p,sum,maxn; bool leaf;
	while(hi!=ti){
		hi++; leaf=1; Fin[Fa[Arr[hi]]]++; Size[Arr[hi]]=1;
		for(v=Arrmap[Arr[hi]];v;v=Arre[v].ne)if(Arre[v].x!=Fa[Arr[hi]]){
			ti++; Arr[ti]=Arre[v].x; leaf=0;
			Depth[Arr[ti]]=Depth[Arr[hi]]+1; Fa[Arr[ti]]=Arr[hi];
		}
		if(leaf)stk[++stktop]=Arr[hi]; 
	}
	Fin[0]=0;
	while(stk[stktop]){
		p=stk[stktop--]; Size[Fa[p]]+=Size[p]; Fin[Fa[p]]--; if(!Fin[Fa[p]])stk[++stktop]=Fa[p]; maxn=0;
		for(v=Arrmap[p];v;v=Arre[v].ne)if(Arre[v].x!=Fa[p]&&maxn<Size[Arre[v].x]){
			maxn=Size[Arre[v].x]; Wson[p]=Arre[v].x;
		}
	}
	hi=0; ti=1; Arr[1]=1; Top[1]=1;
	while(hi!=ti){
		hi++; PIH[Arr[hi]]++; sum=0;
		if(Wson[Arr[hi]]){
			Top[Wson[Arr[hi]]]=Top[Arr[hi]]; Arr[++ti]=Wson[Arr[hi]]; PIH[Wson[Arr[hi]]]+=PIH[Arr[hi]]+sum; sum+=Size[Wson[Arr[hi]]];
		}
		for(v=Arrmap[Arr[hi]];v;v=Arre[v].ne)if(Arre[v].x!=Fa[Arr[hi]]&&Arre[v].x!=Wson[Arr[hi]]){
			Top[Arre[v].x]=Arre[v].x; Arr[++ti]=Arre[v].x; PIH[Arre[v].x]+=PIH[Arr[hi]]+sum; sum+=Size[Arre[v].x];
		}
	}
}
struct opt{
	int x,op;
};
vector<opt> O[100010];
int maxn;
struct inf{
	int x,p;
}P[100010];
inline bool Acmp(const inf &a,const inf &b){
	return a.x<b.x;
}
int B[100010],I[100010];
struct ope{
	int u,v;
}H[100010];
void Change(int u,int v,const int &z){
	int fu,fv;
	while(Top[u]!=Top[v]){
		fu=Top[u]; fv=Top[v];
		if(Depth[Fa[fu]]<Depth[Fa[fv]]){
			swap(u,v); swap(fu,fv);
		}
		/*区间是[PIH[fu]..PIH[u]]*/
		O[PIH[fu]].push_back((opt){z,1}); O[PIH[u]+1].push_back((opt){z,-1}); u=Fa[fu];
	}
	if(PIH[u]>PIH[v])swap(u,v);
	O[PIH[u]].push_back((opt){z,1}); O[PIH[v]+1].push_back((opt){z,-1});
}
struct node{
	int l,r,m,maxn[2];
	/*maxn[0]是最大值，maxn[1]是最大值的节点的编号*/
}Seg[100010<<2];
void equal(const int &x,const int &y){
	Seg[x].maxn[0]=Seg[y].maxn[0]; Seg[x].maxn[1]=Seg[y].maxn[1];
}
void unite(const int &p){
	if(Seg[p<<1|1].maxn[0]>Seg[p<<1].maxn[0])equal(p,p<<1|1);else equal(p,p<<1);
}
void Segbuild(const int &p,const int &l,const int &r){
	Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1; if(l==r){Seg[p].maxn[1]=l;return;}
	Segbuild(p<<1,l,Seg[p].m); Segbuild(p<<1|1,Seg[p].m+1,r);
	unite(p);
}
void SegChange(const int &p,const int &k,const int &w){
	if(Seg[p].l==Seg[p].r){
		Seg[p].maxn[0]+=w; return;
	}
	if(k<=Seg[p].m)SegChange(p<<1,k,w);else SegChange(p<<1|1,k,w);
	unite(p);
}
int Ans[100010];
int main(){
	int i,j,u,v;
	read(n); read(m);
	for(i=1;i<=n-1;i++){
		read(u); read(v); ins(u,v); ins(v,u);
	}
	top=0; BFS1();
	for(i=1;i<=m;i++){
		read(H[i].u); read(H[i].v); read(P[i].x); P[i].p=i;
	}
	sort(P+1,P+m+1,Acmp);
	for(i=1;i<=m;i++)B[P[i].p]=B[P[i-1].p]+(P[i].x!=P[i-1].x); maxn=B[P[m].p];
	top=0;
	for(i=1;i<=m;i++){
		if(P[i].x==P[i-1].x&&i!=m)continue;
		I[++top]=P[i].x;
	}
	for(i=1;i<=m;i++)
	Change(H[i].u,H[i].v,B[i]);
	Segbuild(1,1,maxn);
	for(i=1;i<=n;i++){
		for(j=0;j<O[i].size();j++)SegChange(1,O[i][j].x,O[i][j].op);
		if(Seg[1].maxn[0])Ans[i]=Seg[1].maxn[1];else Ans[i]=0;
	}
	for(i=1;i<=n;i++)printf("%d\n",I[Ans[PIH[i]]]);
}