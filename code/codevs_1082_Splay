#include<cstdio>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,q,root;
int A[210000];
struct node{
	int s[2];
	long long val,sum,tag;
}Btr[210000];
int size[210000],Fa[210000];
void unite(int p){
	Btr[p].sum=Btr[Btr[p].s[0]].sum+Btr[Btr[p].s[1]].sum+Btr[p].val;
	size[p]=size[Btr[p].s[0]]+size[Btr[p].s[1]]+1;
}
void update(int p,int w){
	Btr[p].sum+=(long long)size[p]*w; Btr[p].val+=w; Btr[p].tag+=w;
}
void down(int p){
	if(!Btr[p].tag)return;
	update(Btr[p].s[0],Btr[p].tag); update(Btr[p].s[1],Btr[p].tag); Btr[p].tag=0;
}
int Btrbuild(int l,int r){
	if(l>r)return 0; if(l==r){Btr[l+1].val=Btr[l+1].sum=A[l];size[l+1]=1;return l+1;}
	int m=(l+r)>>1; Btr[m+2].val=A[m+1];
	Btr[m+2].s[0]=Btrbuild(l,m); Btr[m+2].s[1]=Btrbuild(m+2,r); Fa[Btr[m+2].s[0]]=Fa[Btr[m+2].s[1]]=m+2;
	unite(m+2); return m+2;
}
int f,gf,s,v;
void rot(int p){
	f=Fa[p]; gf=Fa[f]; down(f); down(p); v=Btr[f].s[0]!=p;
	s=Btr[p].s[v^1]; Btr[p].s[v^1]=f; Btr[f].s[v]=s; Fa[s]=f; Fa[p]=gf; Fa[f]=p; unite(f); unite(p);
	if(gf){v=Btr[gf].s[0]!=f;Btr[gf].s[v]=p;}
}
void Splay(int p){
	for(f=Fa[p],gf=Fa[f];Fa[p]&&Fa[f];rot(p),f=Fa[p],gf=Fa[f])rot((Btr[gf].s[0]!=f)^(Btr[f].s[0]!=p)?p:f);
	if(Fa[p])rot(p); root=p;
}
void Change(int l,int r,int w){
	Splay(r+2); Splay(l); if(Btr[l].s[1]!=r+2)rot(r+2);
	update(Btr[r+2].s[0],w); unite(r+2); unite(l);
}
long long Getsum(int l,int r){
	Splay(r+2); Splay(l); if(Btr[l].s[1]!=r+2)rot(r+2);
	down(l); down(r+2); return Btr[Btr[r+2].s[0]].sum;
}
int main(){
	int i,li,ri,wi,opt;
	long long vi;
	read(n);
	for(i=1;i<=n;i++)read(A[i]);
	root=Btrbuild(0,n+1);
	read(q);
	for(i=1;i<=q;i++){
		read(opt);
		if(opt==1){
			read(li); read(ri); read(wi); Change(li,ri,wi);
		}else{
			read(li); read(ri); vi=Getsum(li,ri); printf("%lld\n",vi);
		}
	}
}