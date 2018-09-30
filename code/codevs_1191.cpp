#include<cstdio>
//定义i所在的Btree的位置就是i+1 
int n,m,root;
struct node{
	int data,sum,son[2];
	bool tag;
};
node Btree[210000];
int Fa[210000];
int Splaybuild(int l,int r){
	if(l>r)return 0;
	if(l==r){Btree[l+1].data=1;Btree[l+1].sum=1;return l+1;}
	int m=(l+r)>>1;
	Btree[m+2].son[0]=Splaybuild(l,m); Btree[m+2].son[1]=Splaybuild(m+2,r);
	Btree[m+2].data=1; Btree[m+2].sum=Btree[Btree[m+2].son[0]].sum+Btree[Btree[m+2].son[1]].sum+1;
	Fa[Btree[m+2].son[0]]=Fa[Btree[m+2].son[1]]=m+2;
	return m+2;
}
inline void Pushdown(int p){
	if(!Btree[p].tag)return;
	Btree[Btree[p].son[0]].tag=true; Btree[Btree[p].son[1]].tag=true; Btree[p].tag=false;
	Btree[p].data=0; Btree[p].sum=0;
}
inline void Union(int p){
	Btree[p].sum=Btree[Btree[p].son[0]].sum+Btree[Btree[p].son[1]].sum+Btree[p].data;
}
void Splay(int p){
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
	Fa[son]=f; Fa[f]=p; Fa[p]=gf;
	Union(f); Union(p);
	if(gf){if(Btree[gf].son[0]==f)Btree[gf].son[0]=p;else Btree[gf].son[1]=p;}
}
void Change(int l,int r){
	while(r+2!=root)Splay(r+2);
	while(l!=root)Splay(l);
	if(Btree[l].son[1]!=r+2)Splay(r+2);
	Pushdown(l); Pushdown(r+2); Pushdown(Btree[r+2].son[1]); Pushdown(Btree[l].son[0]);
	Btree[Btree[r+2].son[0]].tag=true;
	Btree[r+2].sum=Btree[Btree[r+2].son[1]].sum+Btree[r+2].data; Union(l);
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
	root=Splaybuild(0,n+1);
	for(int i=1;i<=m;i++){
		int l,r; scanf("%d%d",&l,&r);
		Change(l,r);
		int w=Getsum(1,n); printf("%d\n",w);
	}
}