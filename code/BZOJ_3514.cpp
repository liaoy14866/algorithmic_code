#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
const int none=1e9+7;
int n,m,q,type;
int lastans;
struct LCT{/*LCT计算ntr数组*/
	struct node{
		int s[2];
		int val,minp;
		bool inv;
	}Btr[410000];
	int fa[410000];
	inline int minpos(int a,int b){
		if(Btr[a].val<Btr[b].val)return a;else return b;
	}
	void unite(int p){
		Btr[p].minp=minpos(minpos(p,Btr[Btr[p].s[0]].minp),Btr[Btr[p].s[1]].minp);
	}
	int f,gf,s,v;
	void rot(int p){
		f=fa[p];gf=fa[f];v=Btr[f].s[0]!=p;
		s=Btr[p].s[v^1]; Btr[p].s[v^1]=f; Btr[f].s[v]=s; fa[s]=f; fa[p]=gf; fa[f]=p; unite(f); unite(p);
		//发现这里好像不需要用unite(p)，因为p就是f的位置。可不可以直接把f的信息给p
		if(gf){if(Btr[gf].s[0]==f)Btr[gf].s[0]=p;else if(Btr[gf].s[1]==f)Btr[gf].s[1]=p;} 
	}
	inline bool Beroot(int p){return Btr[fa[p]].s[0]!=p&&Btr[fa[p]].s[1]!=p;}
	int stk[410000]; int stktop;
	void flip(int p){
		if(Btr[p].inv){
			std::swap(Btr[p].s[0],Btr[p].s[1]);Btr[p].inv^=1; Btr[Btr[p].s[0]].inv^=1; Btr[Btr[p].s[1]].inv^=1;
		}
	}
	void Splay(int p){
		for(v=p;!Beroot(v);v=fa[v])stk[++stktop]=v; stk[++stktop]=v; for(;stktop;stktop--)flip(stk[stktop]);
		for(;!Beroot(p)&&!Beroot(fa[p]);rot(p)){
			if((Btr[fa[fa[p]]].s[0]!=fa[p])^(Btr[fa[p]].s[0]!=p))rot(p);else rot(fa[p]);
		}
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
	void Link(int x,int y){
		Make_root(x); fa[x]=y;
	}
	void Cut(int x,int y){
		Make_root(x); Access(y); Splay(x);
		Btr[x].s[1]=0; fa[y]=0; unite(x);
	}
	int Getmin(int x,int y){
		Make_root(x); Access(y); Splay(y); return Btr[y].minp;
	}
	int Find_root(int x){
		Access(x); Splay(x);
		for(flip(x);Btr[x].s[0];x=Btr[x].s[0])flip(x);
		//这里的Splay就真心不必要了吧常数已经超载了 
		return x;
	}
}T;
struct rec{
	int u,v;
}linked[210000];
int ntr[210000];
struct node{
	int l,r,m,s[2];
	int sum;
}Seg[210000*22];/*主席树用于求答案*/
int top;
int root[210000];
int Segbuild(int l,int r){
	int p=++top; Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1; if(l==r)return p;
	Seg[p].s[0]=Segbuild(l,Seg[p].m); Seg[p].s[1]=Segbuild(Seg[p].m+1,r);
	return p;
}
int update(int x,int k){
	int p=++top; Seg[p]=Seg[x]; Seg[p].sum++; if(Seg[x].l==Seg[x].r)return p;
	if(k<=Seg[x].m)Seg[p].s[0]=update(Seg[x].s[0],k);else Seg[p].s[1]=update(Seg[x].s[1],k);
	return p;
}
int Getsum(int x,int y,int l,int r){
	if(Seg[x].l==l&&Seg[x].r==r)return Seg[y].sum-Seg[x].sum;
	if(r<=Seg[x].m)return Getsum(Seg[x].s[0],Seg[y].s[0],l,r);
	else
	if(Seg[x].m+1<=l)return Getsum(Seg[x].s[1],Seg[y].s[1],l,r);
	else return
	Getsum(Seg[x].s[0],Seg[y].s[0],l,Seg[x].m)+Getsum(Seg[x].s[1],Seg[y].s[1],Seg[x].m+1,r);
}
int main(){
	int i,li,ri,u,v,tmp;
	read(n); read(m); read(q); read(type);
	for(i=1;i<=n;i++)T.Btr[i].val=none,T.Btr[i].minp=i; T.Btr[0].val=none+1;
	for(i=n+1;i<=n+m;i++)T.Btr[i].val=i-n;
	for(i=1;i<=m;i++){
		read(u); read(v); if(u==v){
			ntr[i]=i; continue;
		}
		linked[i].u=u; linked[i].v=v;
		if(T.Find_root(u)==T.Find_root(v)){
			tmp=T.Getmin(u,v); T.Cut(tmp,linked[tmp-n].u); T.Cut(tmp,linked[tmp-n].v); ntr[i]=tmp-n;
		}
		T.Link(i+n,u); T.Link(i+n,v);
	}
	root[0]=Segbuild(0,m);
	for(i=1;i<=m;i++)root[i]=update(root[i-1],ntr[i]);
	for(i=1;i<=q;i++){
		read(li); read(ri); li=li^lastans; ri=ri^lastans;
		tmp=ri-li+1-Getsum(root[li-1],root[ri],li,ri); lastans=n-tmp;
		printf("%d\n",lastans); lastans*=type;//输出
	}
}