/*
给出一棵树，要求支持：
1.树上链加
2.查询子树的权值和
强上树链剖分即可。
*/
#include<cstdio>
#include<algorithm>
int n,m,top;
struct Rec{
	int x,next;
};
int Tree[110000];
Rec Etree[110000];
inline void ins(int f,int s){
	top++; Etree[top].x=s; Etree[top].next=Tree[f]; Tree[f]=top;
}
int Size[110000],Wson[110000],PIH[110000],Depth[110000],Top[110000],Fa[110000];
void DFS1(int x,int d){
	Size[x]=1; Depth[x]=d; int maxn=0;
	for(int v=Tree[x];v;v=Etree[v].next){
		DFS1(Etree[v].x,d+1);
		Size[x]+=Size[Etree[v].x];
		if(Size[x]>maxn){
			maxn=Size[x]; Wson[x]=Etree[v].x;
		}
	}
}
void DFS2(int t,int x){
	PIH[x]=++top; Top[x]=t; if(Wson[x])DFS2(t,Wson[x]);
	for(int v=Tree[x];v;v=Etree[v].next){
		if(Etree[v].x!=Wson[x])DFS2(Etree[v].x,Etree[v].x);
	}
}
struct node{
	int l,r,m,son[2];
	long long sum,tag;
};
node Seg[210000];
inline void Update(int p,int w){
	Seg[p].sum+=(long long)(Seg[p].r-Seg[p].l+1)*w; Seg[p].tag+=w;
}
inline void Pushdown(int p){
	Update(Seg[p].son[0],Seg[p].tag); Update(Seg[p].son[1],Seg[p].tag);
	Seg[p].tag=0;
}
inline void Union(int p){
	Seg[p].sum=Seg[Seg[p].son[0]].sum+Seg[Seg[p].son[1]].sum;
}
int Segbuild(int l,int r){
	int p=++top; Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1;
	if(l==r)return p;
	Seg[p].son[0]=Segbuild(l,Seg[p].m); Seg[p].son[1]=Segbuild(Seg[p].m+1,r);
	return p;
}
void SegChange(int p,int l,int r,int w){
	if(Seg[p].l==l&&Seg[p].r==r){Update(p,w);return;}
	Pushdown(p);
	if(r<=Seg[p].m)SegChange(Seg[p].son[0],l,r,w);
	else
	if(Seg[p].m+1<=l)SegChange(Seg[p].son[1],l,r,w);
	else{
		SegChange(Seg[p].son[0],l,Seg[p].m,w); SegChange(Seg[p].son[1],Seg[p].m+1,r,w);
	}
	Union(p);
}
long long SegGetsum(int p,int l,int r){
	if(Seg[p].l==l&&Seg[p].r==r)return Seg[p].sum;
	Pushdown(p);
	if(r<=Seg[p].m)return SegGetsum(Seg[p].son[0],l,r);
	else
	if(Seg[p].m+1<=l)return SegGetsum(Seg[p].son[1],l,r);
	else return
	SegGetsum(Seg[p].son[0],l,Seg[p].m)+SegGetsum(Seg[p].son[1],Seg[p].m+1,r);
}
void Change(int u,int v,int w){
	int fu,fv;
	while(Top[u]!=Top[v]){
		fu=Top[u]; fv=Top[v];
		if(Depth[Fa[fu]]<Depth[Fa[fv]]){
			std::swap(u,v); std::swap(fu,fv);
		}
		SegChange(1,PIH[fu],PIH[u],w); u=Fa[fu];
	}
	if(PIH[u]>PIH[v])std::swap(u,v); SegChange(1,PIH[u],PIH[v],w);
}
char ifdo[10];
int u,v,w;
long long s;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){
		int u,v; scanf("%d%d",&u,&v); u++; v++; ins(u,v); Fa[v]=u;
	}
	DFS1(1,1); top=0; DFS2(1,1); top=0; Segbuild(1,n);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%s",ifdo);
		if(ifdo[0]=='A'){
			scanf("%d%d%d",&u,&v,&w); u++; v++; Change(u,v,w);
		}else{
			scanf("%d",&u); u++; s=SegGetsum(1,PIH[u],PIH[u]+Size[u]-1);
			printf("%lld\n",s);
		}
	}
}