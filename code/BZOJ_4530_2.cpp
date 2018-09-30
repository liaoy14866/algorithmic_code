#include<cstdio>
#include<algorithm>
using namespace std;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
struct node{
	int s[2];
	int vsize,asize;
	//注意，vsize是所有虚儿子的信息和，asize是总的信息和 
	bool inv;
}Btr[100010];
int Fa[100010];
void aunite(int x){
	Btr[x].asize=Btr[x].vsize+Btr[Btr[x].s[0]].asize+Btr[Btr[x].s[1]].asize+1;
}
void vchange(int x,int fr,int to){
	Btr[x].vsize+=Btr[fr].asize-Btr[to].asize;
}
bool Beroot(int x){
	return Btr[Fa[x]].s[0]!=x&&Btr[Fa[x]].s[1]!=x;
}
void rot(int p){
	int f=Fa[p],gf=Fa[f],v=Btr[f].s[0]!=p,s=Btr[p].s[v^1];
	Btr[p].s[v^1]=f; Btr[f].s[v]=s; Fa[p]=gf; Fa[s]=f; Fa[f]=p; aunite(f); aunite(p);
	if(gf){
		if(Btr[gf].s[0]==f)Btr[gf].s[0]=p;else if(Btr[gf].s[1]==f)Btr[gf].s[1]=p; aunite(gf);
	}
}
void flip(int x){
	if(!Btr[x].inv)return;
	swap(Btr[x].s[0],Btr[x].s[1]);
	Btr[Btr[x].s[0]].inv^=1; Btr[Btr[x].s[1]].inv^=1; Btr[x].inv=0;
}
int stk[100010]; int stktop;
void Splay(int p){
	int v; for(v=p;!Beroot(v);v=Fa[v])stk[++stktop]=v; stk[++stktop]=v;
	for(;stktop;stktop--)flip(stk[stktop]);
	for(;!Beroot(Fa[p])&&!Beroot(p);rot(p))
	rot((Btr[Fa[Fa[p]]].s[0]!=Fa[p])^(Btr[Fa[p]].s[0]!=p)?p:Fa[p]);
	if(!Beroot(p))rot(p);
}
void Access(int x){
	for(int t=0;x;t=x,x=Fa[x]){
		Splay(x); vchange(x,Btr[x].s[1],t); Btr[x].s[1]=t; aunite(x);
	}
}
void Make_root(int x){
	Access(x); Splay(x); Btr[x].inv^=1;
}
void Link(int x,int y){
	Make_root(x); Access(y); Splay(y); Fa[x]=y; Btr[y].vsize+=Btr[x].asize; aunite(y);
}
int n,m;
int main(){
	int i,u,v,x,y; long long s; bool opt;
	read(n); read(m);
	for(i=1;i<=n;i++)Btr[i].asize=1;
	for(i=1;i<=m;i++){
		for(ch=getchar();ch!='A'&&ch!='Q';ch=getchar()); opt=(ch=='A'); read(u); read(v);
		if(opt==1)Link(u,v);
		else{
			Make_root(u); Access(v); x=Btr[v].vsize+1;
			Make_root(v); Access(u); y=Btr[u].vsize+1;
			s=(long long)x*y; printf("%lld\n",s);
		}
	}
}