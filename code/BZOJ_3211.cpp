#include<cstdio>
#include<algorithm>
#include<cmath>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,logn,q,top;
int val[510000];
struct Rec{
	int x,next;
};
Rec Etree[1100000];
int Tree[510000];
inline void ins(int f,int s){
	top++; Etree[top].x=s; Etree[top].next=Tree[f]; Tree[f]=top;
}
int IN[510000],OUT[510000],Depth[510000];
int Fm[510000][21];
struct inf{
	int v,x;
};
int cnt;
inf stk[510000];
inline void Pushin(int x){stk[++top].x=x;}
inline void Pushout(){stk[top].x=stk[top].v=0; top--;}
bool Ad[510000],Xd[510000];
void DFS(){//手写栈
	Pushin(1); Depth[1]=1;
	for(;;){
		if(!Ad[stk[top].x]){Ad[stk[top].x]=1;IN[stk[top].x]=++cnt;Depth[stk[top].x]=Depth[stk[top-1].x]+1;}
		if(!Xd[stk[top].x]){Xd[stk[top].x]=1;stk[top].v=Tree[stk[top].x];}
		else stk[top].v=Etree[stk[top].v].next;
		if(stk[top].v){
			if(Etree[stk[top].v].x!=Fm[stk[top].x][0]){
				Fm[Etree[stk[top].v].x][0]=stk[top].x;
				Pushin(Etree[stk[top].v].x);
			}
		}else{
			OUT[stk[top].x]=++cnt; Pushout(); if(!top)break;
		}
	}
}
void lcainit(){
	logn=floor(log2(n));
	for(int vj=1;vj<=logn;vj++)
	for(int vi=1;vi<=n;vi++)
	Fm[vi][vj]=Fm[Fm[vi][vj-1]][vj-1];
}
int lca(int u,int v){
	if(Depth[u]<Depth[v])std::swap(u,v);
	int k=Depth[u]-Depth[v],l=0;
	for(;k;k>>=1,l++)if(k&1)u=Fm[u][l];
	if(u==v)return u; if(Fm[u][0]==Fm[v][0])return Fm[u][0];
	for(;;){
		for(k=1;;k++)if(Fm[u][k]==Fm[v][k])break; k--;
		u=Fm[u][k]; v=Fm[v][k]; if(Fm[u][0]==Fm[v][0])return Fm[u][0];
	}
}
int intm;
int Seg[2200000];
void Segbuild(){
	intm=ceil(log2(n<<1)); intm=1<<intm;
	for(int vi=1;vi<=n;vi++)Seg[IN[vi]+intm-1]=Seg[OUT[vi]+intm-1]=val[vi];
	for(int vi=intm-1;vi;vi--)
	Seg[vi]=Seg[vi<<1]^Seg[vi<<1|1];
}
void SegChange(int p,int w){
	p+=intm-1; Seg[p]=w;
	for(p>>=1;p;p>>=1)Seg[p]=Seg[p<<1]^Seg[p<<1|1];//加法
}
int SegGetsum(int l,int r){
	int tmp=0; if(l>r)return 0;
	for(l+=intm-1,r+=intm-1;l!=r;l>>=1,r>>=1){
		if(l&1)tmp^=Seg[l-1]; if(!(r&1))tmp^=Seg[r+1];//减法
	}
	tmp^=Seg[l];//加法 return tmp;
}
void Change(int p,int w){
	SegChange(IN[p],w); SegChange(OUT[p],w);//单点修改
}
int Getsum(int u,int v){
	int tmp,l=lca(u,v);
	tmp=SegGetsum(1,IN[u])^SegGetsum(1,IN[v])^SegGetsum(1,IN[l])^SegGetsum(1,IN[Fm[l][0]]);//加法
	return tmp;
}
char ch;
int main(){
	int i,u,v,w;
	read(n);
	for(i=1;i<=n;i++)read(val[i]);
	for(i=1;i<=n-1;i++){
		read(u); read(v); ins(u,v); ins(v,u);
	}
	top=0; DFS(); Segbuild(); lcainit();
	read(q);
	for(i=1;i<=q;i++){
		for(ch=getchar();ch!='Q'&&ch!='C';ch=getchar());
		if(ch=='Q'){
			read(u); read(v); w=Getsum(u,v);
			if(!w)printf("No\n");else printf("Yes\n");
		}else{
			read(u); read(w); Change(u,w);
		}
	}
}