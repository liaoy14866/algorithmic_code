#include<cstdio>
#include<cmath>
#include<algorithm>
int n,m,top,root,logn,ifdo;
int Tree[110000];
struct Rec{
	int x,next;
};
Rec Etree[210000];
/*邻接链表*/
inline void ins(int f,int s){
	Etree[++top].x=s; Etree[top].next=Tree[f]; Tree[f]=top;
}
int Wson[110000],Size[110000],PIH[110000],B[110000],Depth[110000],Top[110000];
int Fm[110000][20];
int val[110000];
/*树链剖分*/
void DFS1(int f,int x){
	int maxn=0; Size[x]=1; Fm[x][0]=f;
	for(int v=Tree[x];v;v=Etree[v].next){
		if(f==Etree[v].x)continue;
		DFS1(x,Etree[v].x);
		if(Size[Etree[v].x]>maxn){
			maxn=Size[Etree[v].x]; Wson[x]=Etree[v].x;
		}
		Size[x]+=Size[Etree[v].x];
	}
}
void DFS2(int f,int x,int d){
	PIH[x]=++top; Depth[x]=d; Top[x]=f;
	if(Wson[x])DFS2(f,Wson[x],d+1);
	for(int v=Tree[x];v;v=Etree[v].next)
	if(Etree[v].x!=Fm[x][0]&&Etree[v].x!=Wson[x])DFS2(Etree[v].x,Etree[v].x,d+1);
}
void Fminit(){
	logn=log2(n)+1;
	for(int j=1;j<=logn;j++)
	for(int i=1;i<=n;i++)
	Fm[i][j]=Fm[Fm[i][j-1]][j-1];
}
int lca(int u,int v){
	if(Depth[u]<Depth[v])std::swap(u,v);
	int k=Depth[u]-Depth[v],l;
	for(l=0;k;k>>=1,l++)if(k&1)u=Fm[u][l];
	if(u==v)return u; if(Fm[u][0]==Fm[v][0])return Fm[u][0];
	for(;;){
		for(l=1;;l++)if(Fm[u][l]==Fm[v][l])break; l--;
		u=Fm[u][l]; v=Fm[v][l]; if(Fm[u][0]==Fm[v][0])return Fm[u][0];
	}
}
/*线段树*/
struct node{
	int minn,l,r,m,tag,son[2];
};
node Seg[210000];
inline void Pushdown(int p){
	if(!Seg[p].tag)return;
	Seg[Seg[p].son[0]].minn=Seg[Seg[p].son[1]].minn=
	Seg[Seg[p].son[0]].tag=Seg[Seg[p].son[1]].tag=Seg[p].tag; Seg[p].tag=0;
}
inline void Union(int p){
	Seg[p].minn=std::min(Seg[Seg[p].son[0]].minn,Seg[Seg[p].son[1]].minn);
}
int Segbuild(int l,int r){
	int now=++top; Seg[now].l=l; Seg[now].r=r; Seg[now].m=(l+r)>>1;
	if(l==r){Seg[now].minn=val[B[l]];return now;}
	Seg[now].son[0]=Segbuild(l,Seg[now].m); Seg[now].son[1]=Segbuild(Seg[now].m+1,r);
	Union(now); return now;
}
void Segchange(int p,int l,int r,int w){
	if(Seg[p].l==l&&Seg[p].r==r){
		Seg[p].minn=w; Seg[p].tag=w; return;
	}
	Pushdown(p);
	if(r<=Seg[p].m)Segchange(Seg[p].son[0],l,r,w);
	else
	if(Seg[p].m+1<=l)Segchange(Seg[p].son[1],l,r,w);
	else{
		Segchange(Seg[p].son[0],l,Seg[p].m,w); Segchange(Seg[p].son[1],Seg[p].m+1,r,w);
	}
	Union(p);
}
/*询问与修改*/
int Seggetmin(int p,int l,int r){
	if(l>r)return 1<<30;
	if(Seg[p].l==l&&Seg[p].r==r)return Seg[p].minn;
	Pushdown(p);
	if(r<=Seg[p].m)return Seggetmin(Seg[p].son[0],l,r);
	else
	if(Seg[p].m+1<=l)return Seggetmin(Seg[p].son[1],l,r);
	else
	return std::min(Seggetmin(Seg[p].son[0],l,Seg[p].m),
	Seggetmin(Seg[p].son[1],Seg[p].m+1,r));
}
void Change(int u,int v,int w){
	int fu,fv;
	while(Top[u]!=Top[v]){
		fu=Top[u],fv=Top[v];
		if(Depth[Fm[fu][0]]<Depth[Fm[fv][0]]){
			std::swap(u,v); std::swap(fu,fv);
		}
		Segchange(1,PIH[fu],PIH[u],w);
		u=Fm[fu][0];
	}
	if(PIH[u]>PIH[v])std::swap(u,v); Segchange(1,PIH[u],PIH[v],w);
}
int Getmin(int x){
	if(x==root)return Seggetmin(1,1,n);
	int l=lca(root,x);
	if(x!=l)return Seggetmin(1,PIH[x],PIH[x]+Size[x]-1);
	else{
		int u=root,k;
		for(;;){
			if(Fm[u][0]==x)break;
			for(k=1;k<=logn;k++)if(Depth[u]-(1<<k)<=Depth[x])break;
			k--; u=Fm[u][k];
		}
		k=std::min(Seggetmin(1,1,PIH[u]-1),Seggetmin(1,PIH[u]+Size[u],n));
		return k;
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n-1;i++){
		int u,v; scanf("%d%d",&u,&v); ins(u,v); ins(v,u);//插入边
	}
	for(int i=1;i<=n;i++)scanf("%d",&val[i]);
	DFS1(0,1); top=0; DFS2(1,1,1); Fminit(); scanf("%d",&root);//树链剖分
	for(int i=1;i<=n;i++)B[PIH[i]]=i;
	top=0; Segbuild(1,n);
	for(int i=1;i<=m;i++){
		scanf("%d",&ifdo);
		switch(ifdo){
			case 1:{
				int k;scanf("%d",&k); root=k;
				break;
			}
			case 2:{
				int u,v,w; scanf("%d%d%d",&u,&v,&w); Change(u,v,w);//修改
				break;
			}
			case 3:{
				int u; scanf("%d",&u); 
				int w=Getmin(u); //查询
				printf("%d\n",w);
				break;
			}
		}
	}
}