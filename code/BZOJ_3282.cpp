/*
裸LCT
*/
#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m;
struct LCT{
	struct node{
		int s[2];
		int val,sum;
		bool inv;
	}Btr[310000];
	int fa[310000];
	int f,gf,s,v;
	bool Beroot(int p){
		return Btr[fa[p]].s[0]!=p&&Btr[fa[p]].s[1]!=p;
	}
	void unite(int p){
		Btr[p].sum=Btr[Btr[p].s[0]].sum^Btr[Btr[p].s[1]].sum^Btr[p].val;
	}
	void rot(int p){
		f=fa[p];gf=fa[f];v=Btr[f].s[0]!=p;
		s=Btr[p].s[v^1]; Btr[p].s[v^1]=f; Btr[f].s[v]=s; fa[s]=f; fa[p]=gf; fa[f]=p; unite(f); unite(p);
		if(gf){if(Btr[gf].s[0]==f)Btr[gf].s[0]=p;else if(Btr[gf].s[1]==f)Btr[gf].s[1]=p;}
	}
	int stk[310000]; int stktop;
	void flip(int p){
		if(Btr[p].inv){std::swap(Btr[p].s[0],Btr[p].s[1]);Btr[Btr[p].s[0]].inv^=1;Btr[Btr[p].s[1]].inv^=1;Btr[p].inv^=1;}
	}
	void Splay(int p){
		for(v=p;!Beroot(v);v=fa[v])stk[++stktop]=v; stk[++stktop]=v; for(;stktop;stktop--)flip(stk[stktop]);
		for(;!Beroot(p)&&!Beroot(fa[p]);rot(p))
		if((Btr[fa[fa[p]]].s[0]!=fa[p])^(Btr[fa[p]].s[0]!=p))rot(p);else rot(fa[p]);
		if(!Beroot(p))rot(p);
	}
	void Access(int x){
		for(int t=0;x;t=x,x=fa[x]){
			Splay(x); Btr[x].s[1]=t; unite(x);
		}
	}
	void Make_root(int x){
		Access(x); Splay(x); Btr[x].inv^=1;
	}
	int Find_root(int x){
		Access(x); Splay(x);
		for(flip(x);Btr[x].s[0];flip(x))x=Btr[x].s[0]; return x;
	}
	void Link(int x,int y){
		if(Find_root(x)==Find_root(y))return; Make_root(x); fa[x]=y;
	}
	void Cut(int x,int y){
		Make_root(x); Access(y); Splay(x); if(Btr[x].s[1]==y){
			Btr[x].s[1]=0; fa[y]=0;
		}
	}
	void Change(int x,int val){
		Splay(x); Btr[x].val=val; unite(x);
	}
	int Getsum(int x,int y){
		Make_root(x); Access(y); Splay(y); return Btr[y].sum;
	}
}T;
int main(){
	int i,u,v,opt,w;
	read(n); read(m);
	for(i=1;i<=n;i++)read(T.Btr[i].val),T.Btr[i].sum=T.Btr[i].val;
	for(i=1;i<=m;i++){
		read(opt);
		switch(opt){
			case 0:{
				read(u); read(v); w=T.Getsum(u,v); printf("%d\n",w); break;
			}
			case 1:{
				read(u); read(v); T.Link(u,v); break;
			}
			case 2:{
				read(u); read(v); T.Cut(u,v); break;
			}
			case 3:{
				read(u); read(w); T.Change(u,w); break;
			}
		}
	}
}