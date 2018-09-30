#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
const int intp=51061;
struct LCT{
	struct node{
		int s[2];
		bool inv;//这个标记是表示当前这个节点的儿子要换 
		long long val,sum,tag[2];//0是+，1是* 
		/*tag是记录当前儿子没有被更新的标记，inv是记录当前节点没有被更新的标记，全部在Splay中下放
		记录当前节点没有被更新的标记用一个栈下放，记录当前儿子没有被更新的标记在rot里面直接下放*/
	}Btr[110000];
	int size[110000],fa[110000];
	void update(int r,int p,int w){//更新
		if(!r){
			(Btr[p].sum+=size[p]*(long long)w)%=intp; (Btr[p].val+=w)%=intp; (Btr[p].tag[0]+=w)%=intp;
		}else{
			(Btr[p].sum*=w)%=intp; (Btr[p].val*=w)%=intp; (Btr[p].tag[0]*=w)%=intp; (Btr[p].tag[1]*=w)%=intp;
		}
	}
	void down(int p){//下传标记
		if(Btr[p].tag[1]!=1){
			update(1,Btr[p].s[0],Btr[p].tag[1]); update(1,Btr[p].s[1],Btr[p].tag[1]); Btr[p].tag[1]=1;
		}
		if(Btr[p].tag[0]){
			update(0,Btr[p].s[0],Btr[p].tag[0]); update(0,Btr[p].s[1],Btr[p].tag[0]); Btr[p].tag[0]=0;
		}
		if(Btr[p].inv){std::swap(Btr[p].s[0],Btr[p].s[1]); Btr[Btr[p].s[0]].inv^=1; Btr[Btr[p].s[1]].inv^=1; Btr[p].inv^=1;}
	}
	void unite(int p){//合并
		size[p]=size[Btr[p].s[0]]+size[Btr[p].s[1]]+1;
		Btr[p].sum=(Btr[Btr[p].s[0]].sum+Btr[Btr[p].s[1]].sum+Btr[p].val)%intp;
	}
	int f,gf,v,s;
	void rot(int p){
		f=fa[p]; gf=fa[f]; v=Btr[f].s[0]!=p;/*Splay中只需要下传2次*/
		s=Btr[p].s[v^1]; Btr[p].s[v^1]=f; Btr[f].s[v]=s; fa[s]=f; fa[p]=gf; fa[f]=p; unite(f); unite(p);
		if(gf){if(Btr[gf].s[0]==f)Btr[gf].s[0]=p;else if(Btr[gf].s[1]==f)Btr[gf].s[1]=p;}
	}
	bool Beroot(int p){return Btr[fa[p]].s[0]!=p&&Btr[fa[p]].s[1]!=p;}
	int stk[110000]; int stktop;
	void Splay(int p){
		for(v=p;!Beroot(v);v=fa[v])stk[++stktop]=v; stk[++stktop]=v; for(;stktop;stktop--)down(stk[stktop]);//栈下放inv
		for(f=fa[p],gf=fa[f];!Beroot(f)&&!Beroot(p);rot(p),f=fa[p],gf=fa[f]){
			if((Btr[gf].s[0]!=f)^(Btr[f].s[0]!=p))rot(f);else rot(p);
		}
		if(!Beroot(p))rot(p);
	}
	void Access(int x){
		for(int t=0;x;t=x,x=fa[x]){
			Splay(x); down(x); Btr[x].s[1]=t; unite(x);//在这里要下放记录儿子没有被更新的标记，并且合并
		}
	}
	void Make_root(int x){
		Access(x); Splay(x); Btr[x].inv^=1;//更新inv只需要打标记
	}
	void Link(int x,int y){
		Make_root(x); fa[x]=y;
	}
	void Cut(int x,int y){
		Make_root(x); Access(y); Splay(x); Btr[x].s[1]=0; fa[y]=0; unite(x);
	}
	void Change(int r,int x,int y,int w){
		Make_root(x); Access(y); Splay(y); update(r,y,w);//更新tag需要重新更新当前节点的值
	}
	int Getsum(int x,int y){
		Make_root(x); Access(y); Splay(y); return Btr[y].sum;
	}
}T;
int n,q;
int main(){
	int i,u,v,w; char c;
	read(n); read(q);
	for(i=1;i<=n;i++)T.size[i]=1,T.Btr[i].val=1,T.Btr[i].tag[1]=1;
	for(i=1;i<=n-1;i++){
		read(u); read(v); T.Link(u,v);
	}
	for(i=1;i<=q;i++){
		for(c=getchar();c!='+'&&c!='-'&&c!='*'&&c!='/';c=getchar());
		switch(c){
			case '+':{
				read(u); read(v); read(w); T.Change(0,u,v,w); break;
			}
			case '-':{
				read(u); read(v); T.Cut(u,v); read(u); read(v); T.Link(u,v); break;
			}
			case '*':{
				read(u); read(v); read(w); T.Change(1,u,v,w); break;
			}
			case '/':{
				read(u); read(v); w=T.Getsum(u,v); printf("%d\n",w); break;
			}
		}
	}
}