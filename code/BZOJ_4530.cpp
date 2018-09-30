#include<cstdio>
#include<algorithm>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int n,m;
int Bfa[100010];
int Getfa(int u){
	int v=u,o; for(;u!=Bfa[u];u=Bfa[u]);
	for(;Bfa[v]!=u;o=Bfa[v],Bfa[v]=u,v=o);
	return u;
}
struct Ure{
	int u,v,tim;
}O[2][100010];
int top[2];
/*0为边，1为查询*/
struct rec{
	int x,ne;
}Arre[200010];
int Arrmap[100010];
bool vis[100010];
int tot;
inline void ins(const int &f,const int &s){
	tot++; Arre[tot].x=s; Arre[tot].ne=Arrmap[f]; Arrmap[f]=tot;
}
int Fa[100010],Size[100010],PIH[100010];
void DFS(const int &f,const int &x){
	PIH[x]=++tot; Size[x]=1; Fa[x]=f; int v,maxn=0;
	for(v=Arrmap[x];v;v=Arre[v].ne)if(Arre[v].x!=f)DFS(x,Arre[v].x),Size[x]+=Size[Arre[v].x];
}
struct node{
	int l,r,m,s[2];
	int sum;
}Seg[100010*18];
int root[100010];
int Seginsert(const int &l,const int &r,const int &k){
	int p=++tot; Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1; Seg[p].sum++;
	if(l==r)return p;
	if(k<=Seg[p].m)Seg[p].s[0]=Seginsert(l,Seg[p].m,k);else Seg[p].s[1]=Seginsert(Seg[p].m+1,r,k);
	return p;
}
void Segunite(const int &p){
	Seg[p].sum=Seg[Seg[p].s[0]].sum+Seg[Seg[p].s[1]].sum;
}
int Segmerge(const int &x,const int &y){
	if(!x)return y; if(!y)return x;
	Seg[x].s[0]=Segmerge(Seg[x].s[0],Seg[y].s[0]); Seg[x].s[1]=Segmerge(Seg[x].s[1],Seg[y].s[1]);
	Segunite(x);
	return x;
}
int SegGetsum(const int &p,const int &l,const int &r){
	if(!p)return 0;
	if(Seg[p].l==l&&Seg[p].r==r)return Seg[p].sum;
	if(r<=Seg[p].m)return SegGetsum(Seg[p].s[0],l,r);
	else
	if(Seg[p].m+1<=l)return SegGetsum(Seg[p].s[1],l,r);
	else
	return SegGetsum(Seg[p].s[0],l,Seg[p].m)+SegGetsum(Seg[p].s[1],Seg[p].m+1,r);
}
int L[100010],R[100010];
int main(){
	int i,j,fu,fv,v; long long ans;
	read(n); read(m);
	for(i=1;i<=n;i++)Bfa[i]=i;
	for(i=1;i<=m;i++){
		for(ch=getchar();ch!='Q'&&ch!='A';ch=getchar());
		v=(ch=='Q'); top[v]++; read(O[v][top[v]].u); read(O[v][top[v]].v); O[v][top[v]].tim=i;
	}
	for(i=1;i<=top[0];i++){
		ins(O[0][i].u,O[0][i].v); ins(O[0][i].v,O[0][i].u);
		fu=Getfa(O[0][i].u); fv=Getfa(O[0][i].v); Bfa[fu]=fv;
	}
	for(i=1;i<=n;i++){
		fu=Getfa(i); if(!vis[fu])ins(n+1,fu); vis[fu]=1;
	}
	tot=-1; DFS(0,n+1);
	tot=0;
	for(i=1;i<=n;i++){
		Bfa[i]=i;
		root[i]=Seginsert(1,n,PIH[i]);
	}
	j=1;
	for(i=1;i<=top[1];i++){
		while(O[0][j].tim<O[1][i].tim&&j<=top[0]){
			fu=Getfa(O[0][j].u); fv=Getfa(O[0][j].v); root[fu]=Segmerge(root[fu],root[fv]); Bfa[fv]=fu; j++;
		}
		if(Fa[O[1][i].u]==O[1][i].v)swap(O[1][i].u,O[1][i].v); v=O[1][i].v; fv=Getfa(v);
		L[i]=SegGetsum(root[fv],PIH[v],PIH[v]+Size[v]-1); R[i]=Seg[root[fv]].sum-L[i];
	}
	for(i=1;i<=top[1];i++)ans=(long long)L[i]*R[i],printf("%lld\n",ans);
}