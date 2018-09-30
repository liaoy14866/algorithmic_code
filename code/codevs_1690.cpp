#include<cstdio>
int n,m,ifdo,l,r,root;
int Fa[110000],Size[110000];
struct node{
	int data,sum,son[2],tag;
};
node Btree[110000];
inline void Pushdown(int p){
	if(!Btree[p].tag)return;
	Btree[Btree[p].son[0]].tag^=1;Btree[Btree[p].son[1]].tag^=1;
	Btree[p].data^=1; Btree[p].sum=Size[p]-Btree[p].sum; Btree[p].tag=0;
}
inline void Union(int p){
	Size[p]=Size[Btree[p].son[0]]+Size[Btree[p].son[1]]+1;
	Btree[p].sum=Btree[Btree[p].son[0]].sum+Btree[Btree[p].son[1]].sum+Btree[p].data;
}
inline void Splay(int p){
	if(p==root)return;
	if(Fa[p]==root)root=p;
	int f=Fa[p],gf=Fa[f],son;
	Pushdown(f); Pushdown(Btree[f].son[0]); Pushdown(Btree[f].son[1]);
	Pushdown(p); Pushdown(Btree[p].son[0]); Pushdown(Btree[p].son[1]);
	if(Btree[f].son[0]==p){
		son=Btree[p].son[1]; Btree[p].son[1]=f; Btree[f].son[0]=son;
	}else{
		son=Btree[p].son[0]; Btree[p].son[0]=f; Btree[f].son[1]=son;
	}
	Fa[f]=p; Fa[son]=f; Fa[p]=gf;
	Union(f); Union(p);
	if(gf){if(Btree[gf].son[0]==f)Btree[gf].son[0]=p;else Btree[gf].son[1]=p;} 
}
int Btreebuild(int l,int r){
	if(l>r)return 0;
	if(l==r){Size[l+1]=1;return l+1;}
	int m=(l+r)>>1;
	Btree[m+2].son[0]=Btreebuild(l,m); Btree[m+2].son[1]=Btreebuild(m+2,r);
	Fa[Btree[m+2].son[0]]=Fa[Btree[m+2].son[1]]=m+2; Union(m+2);
	return m+2; 
}
void Change(int l,int r){
	while(r+2!=root)Splay(r+2);
	while(l!=root)Splay(l);
	if(Btree[l].son[1]!=r+2)Splay(r+2);
	Btree[r+2].sum=Size[Btree[r+2].son[0]]-Btree[Btree[r+2].son[0]].sum+Btree[Btree[r+2].son[1]].sum+Btree[r+2].data;
	Union(l); Btree[Btree[r+2].son[0]].tag^=1;
}
int Getsum(int l,int r){
	while(r+2!=root)Splay(r+2);
	while(l!=root)Splay(l);
	if(Btree[l].son[1]!=r+2)Splay(r+2); 
	Pushdown(l); Pushdown(r+2); Pushdown(Btree[r+2].son[0]);
	return Btree[Btree[r+2].son[0]].sum;
}
int main(){
	scanf("%d%d",&n,&m);
	root=Btreebuild(0,n+1);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&ifdo,&l,&r);
		if(!ifdo)Change(l,r);
		else{
			int w=Getsum(l,r); printf("%d\n",w);
		}
	}
}