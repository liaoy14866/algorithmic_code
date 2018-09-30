#include<cstdio>
int n,m,top,root;
char ifdo[3];
int PIH[110000];
struct Rec{
	int x,next;
};
int Arrmap[110000],Size[110000];
Rec Arre[210000];
inline void ins(int f,int s){
	Arre[++top].x=s; Arre[top].next=Arrmap[f]; Arrmap[f]=top;
}
struct node{
	int data,sum,son[2];
};
node Btree[110000];
int Fa[110000];
void DFS(int last,int x){
	PIH[x]=++top; Size[x]=1;
	for(int v=Arrmap[x];v;v=Arre[v].next){
		if(Arre[v].x!=last){
			DFS(x,Arre[v].x);
			Size[x]+=Size[Arre[v].x];
		}
	}
}
inline void Union(int p){
	Btree[p].sum=Btree[p].data+Btree[Btree[p].son[0]].sum+Btree[Btree[p].son[1]].sum;
}
int Btreebuild(int l,int r){
	if(l>r)return 0;
	if(l==r){Btree[l+1].data=1;Btree[l+1].sum=1;return l+1;}
	int m=(l+r)>>1;
	Btree[m+2].son[0]=Btreebuild(l,m); Btree[m+2].son[1]=Btreebuild(m+2,r);
	Btree[m+2].data=1; Union(m+2);
	Fa[Btree[m+2].son[0]]=Fa[Btree[m+2].son[1]]=m+2;
	return m+2;
}
void Splay(int p){
	if(p==root)return; if(Fa[p]==root)root=p;
	int f=Fa[p],gf=Fa[f],son;
	if(Btree[f].son[0]==p){
		son=Btree[p].son[1]; Btree[f].son[0]=son; Btree[p].son[1]=f;
	}else{
		son=Btree[p].son[0]; Btree[f].son[1]=son; Btree[p].son[0]=f;
	}
	Fa[p]=gf; Fa[f]=p; Fa[son]=f;
	Union(f); Union(p);
	if(gf){if(Btree[gf].son[0]==f)Btree[gf].son[0]=p;else Btree[gf].son[1]=p;}
}
void Change(int p){
	while(PIH[p]+1!=root)Splay(PIH[p]+1);
	Btree[PIH[p]+1].data^=1; Union(PIH[p]+1);
}
int Getsum(int p){
	int pl=PIH[p],pr=PIH[p]+Size[p]+1;
	while(pr!=root)Splay(pr);
	while(pl!=root)Splay(pl);
	if(Btree[pl].son[1]!=pr)Splay(pr);
	return Btree[Btree[pr].son[0]].sum;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){
		int u,v; scanf("%d%d",&u,&v); ins(u,v); ins(v,u);
	}
	top=0; DFS(0,1);
	root=Btreebuild(0,n+1);
	int p; scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%s",ifdo);
		if(ifdo[0]=='C'){
			scanf("%d",&p); Change(p);
		}else{
			scanf("%d",&p); int w=Getsum(p); printf("%d\n",w);
		}
	}
}