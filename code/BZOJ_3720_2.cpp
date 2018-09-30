#include<cstdio>
#include<cmath>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,Threshold;
struct graph{
	int top;
	struct rec{
		int x,ne;
	}E[121000];
	int F[61000];
	inline void ins(int f,int s){
		top++; E[top].x=s; E[top].ne=F[f]; F[f]=top;
	}
}
G;
struct LCT{
	//LCT用来维护Size 
	struct node{
		int s[2];
		int val,tag;
		bool inv;
	}Btr[61000];
	int Fa[61000],Size[61000];
	void down(int p){
		if(Btr[p].tag){
			Btr[p].val+=Btr[p].tag;
			Btr[Btr[p].s[0]].tag+=Btr[p].tag; Btr[Btr[p].s[1]].tag+=Btr[p].tag; Btr[p].tag=0;
		}
		if(Btr[p].inv){
			std::swap(Btr[p].s[0],Btr[p].s[1]); Btr[p].inv^=1; Btr[Btr[p].s[0]].tag^=1; Btr[Btr[p].s[1]].tag^=1;
		}
	}
	inline bool Beroot(int p){return Btr[Fa[p]].s[0]!=p&&Btr[Fa[p]].s[1]!=p;}
	int f,gf,v,s;
	void rot(int p){
		f=Fa[p],gf=Fa[f]; 
		down(f); down(Btr[f].s[0]); down(Btr[f].s[1]); down(p); down(Btr[p].s[0]); down(Btr[p].s[1]);
		v=Btr[f].s[0]!=p;
		s=Btr[p].s[v^1]; Btr[p].s[v^1]=f; Btr[f].s[v]=s; Fa[s]=f; Fa[p]=gf; Fa[f]=p;
		if(gf){if(Btr[gf].s[0]==f)Btr[gf].s[0]=p;else if(Btr[gf].s[1]==f)Btr[gf].s[1]=p;}
	}
	void Splay(int p){while(!Beroot(p))rot(p);}
	int t;
	void Access(int x){
		for(t=0;x;t=x,x=Fa[x]){
			Splay(x); down(x); down(Btr[x].s[0]);
			Size[x]+=Size[t]-Size[Btr[x].s[1]]; Btr[x].s[1]=t;
		}
	}
	void Make_root(int x){
		Access(x); Splay(x); Btr[x].inv^=1;
	}
	void Link(int x,int y){
		Make_root(x); Fa[x]=y;
	}
	void Add(int x,int y){
		Make_root(x); Access(y); Splay(x); Btr[x].tag++;
	}
}
T;
struct Btree{
	//Splay用来维护在DFS序中的位置 
	int root;
	struct node{
		int s[2];
	}Btr[61000];
	int Fa[61000],Size[61000];
	int mid;
	void unite(int p){
		Size[p]=Size[Btr[p].s[0]]+Size[Btr[p].s[1]]+1;
	}
	int f,gf,v,s;
	void rot(int p){
		f=Fa[p],gf=Fa[f],v=Btr[f].s[0]!=p;
		s=Btr[p].s[v^1]; Btr[p].s[v^1]=f; Btr[f].s[v]=s; Fa[s]=f; Fa[p]=gf; Fa[f]=p; unite(f); unite(p);
		if(gf){v=Btr[gf].s[0]!=f;Btr[gf].s[v]=p;}
	}
	void Splay(int p){while(Fa[p])rot(p);root=p;}
	void ins(int p,int v){
		//这个函数表示v要插入在p的后面
		Splay(p); s=Btr[p].s[1];
		Btr[p].s[1]=v; Fa[v]=p; Btr[v].s[1]=s; Fa[s]=v;
		Size[v]=Size[s]+1; Size[p]++; rot(v); root=v;
	}
}
B;
struct block{
	int tot;
	struct inf{
		int top;
		int T[620],For[620];
		int ne;
		int vi;
		//这个里面的ins都是表示把w插入到p这个位置（而不是Splay中的插入到p的下一个）
		void add(int p,int w){
			top++; for(vi=top;vi>=p+1;vi--)For[vi]=For[vi-1]; For[p]=w;
			T[top]=w; for(vi=top;T[vi]<T[vi-1]&&vi>1;vi--)std::swap(T[vi],T[vi-1]);
		}
		void change(int p,int w){
			for(vi=1;vi<=top;vi++)if(T[vi]==For[p])break; T[vi]=w;
			for(;T[vi]<T[vi-1]&&vi>1;vi--)std::swap(T[vi],T[vi-1]);
			for(;T[vi]>T[vi+1]&&vi<top;vi++)std::swap(T[vi],T[vi+1]);
			For[p]=w;
		}
		int tl,tr,mid;
		int bigger(int w){
			tl=1; tr=top; if(T[top]<=w)return 0;
			while(tl!=tr){
				mid=(tl+tr)>>1;
				if(T[mid]>w)tr=mid;else tl=mid+1;
			}
			return top-tr+1;
		}
	}Bl[620];
	int vj,step;
	void split(int p){
		tot++; Bl[tot].ne=Bl[p].ne; Bl[p].ne=tot;
		for(vj=Threshold+1;vj<=Bl[p].top;vj++)Bl[tot].For[++Bl[tot].top]=Bl[p].For[vj]; Bl[p].top=Threshold;
		for(vj=1;vj<=Bl[p].top;vj++)Bl[p].T[vj]=Bl[p].For[vj]; std::sort(Bl[p].T+1,Bl[p].T+Bl[p].top+1);
		for(vj=1;vj<=Bl[tot].top;vj++)Bl[tot].T[vj]=Bl[tot].For[vj]; std::sort(Bl[tot].T+1,Bl[tot].T+Bl[tot].top+1);
	}
	void ins(int p,int w){
		for(vj=1,step=0;step+Bl[vj].top<p&&Bl[vj].ne;vj=Bl[vj].ne)step+=Bl[vj].top;
		p-=step; Bl[vj].add(p,w);
		if(Bl[vj].top>Threshold<<1)split(vj);
	}
	void change(int p,int w){
		for(vj=1,step=0;step+Bl[vj].top<p&&Bl[vj].ne;vj=Bl[vj].ne)step+=Bl[vj].top;
		p-=step; Bl[vj].change(p,w);
	}
	int pl,pr,sum;
	int bigger(int l,int r,int w){
		sum=0;
		for(pl=1,step=0;step+Bl[pl].top<l&&Bl[pl].ne;pl=Bl[pl].ne)step+=Bl[pl].top; l-=step;
		for(pr=pl;step+Bl[pr].top<r&&Bl[pr].ne;pr=Bl[pr].ne)step+=Bl[pr].top; r-=step;
		if(pl!=pr){
			for(vj=Bl[pl].ne;vj!=pr;vj=Bl[vj].ne)sum+=Bl[vj].bigger(w);
			for(vj=l;vj<=Bl[pl].top;vj++)sum+=Bl[pl].For[vj]>w;
			for(vj=1;vj<=r;vj++)sum+=Bl[pr].For[vj]>w;
		}else{
			for(vj=l;vj<=r;vj++)sum+=Bl[pl].For[vj]>w;
		}
		return sum;
	}
}
L;
int cnt;
int Arr[61000],Size[61000];
void DFS(int f,int x){
	Size[x]=1; Arr[++cnt]=x;
	for(int v=G.F[x];v;v=G.E[v].ne){
		if(G.E[v].x!=f){
			DFS(x,G.E[v].x);
			Size[x]+=Size[G.E[v].x];
		}
	}
}
int val[61000];
int lastans=0;
int main(){
	int i,u,v,w,opt,posu,sizeu;
	read(n);
	for(i=1;i<=n;i++)T.Size[i]=1;
	for(i=1;i<=n-1;i++){
		read(u); read(v); G.ins(u,v); G.ins(v,u); T.Link(u,v);
	}
	for(i=1;i<=n;i++)read(val[i]);
	DFS(0,1);
	for(i=1;i<=n;i++)T.Btr[i].val=Size[i];
	B.root=Arr[1]; B.Size[Arr[1]]=1;
	for(i=2;i<=n;i++)B.ins(Arr[i-1],Arr[i]);
	read(m); Threshold=ceil(sqrt(n+m));
	L.tot=1; L.Bl[1].T[1]=val[Arr[1]]; L.Bl[1].For[1]=val[1]; L.Bl[1].top=1;
	for(i=2;i<=n;i++)L.ins(i,val[Arr[i]]);
	for(i=1;i<=m;i++){
		read(opt); read(u); read(w); u^=lastans; w^=lastans;
		switch(opt){
			case 0:{
				T.Splay(u); T.down(u); sizeu=T.Btr[u].val; B.Splay(u); posu=B.Size[B.Btr[u].s[0]]+1;
				lastans=L.bigger(posu,posu+sizeu-1,w); printf("%d\n",lastans);
				break;
			}
			case 1:{
				B.Splay(u); posu=B.Size[B.Btr[u].s[0]]+1; L.change(posu,w);
				break;
			}
			case 2:{
				n++;
				T.Size[n]=1; T.Link(n,u); T.Add(1,n);
				B.Size[n]=1; B.ins(u,n);
				B.Splay(u); posu=B.Size[B.Btr[u].s[0]]+1; L.ins(posu+1,w);
				break;
			}
		}
	}
}