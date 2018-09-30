#include<cstdio>
#include<algorithm>
#include<cmath>
int n,m,root,ifdo,l,r;
long long A[110000];
struct node{
	long long data,sum;
	int son[2];
	bool tag;
};
node Btree[110000];
int Size[110000],Fa[110000];
inline void Union(int p){
	Btree[p].sum=Btree[Btree[p].son[0]].sum+Btree[Btree[p].son[1]].sum+Btree[p].data;
	Size[p]=Size[Btree[p].son[0]]+Size[Btree[p].son[1]]+1;
}
void Splay(int p){
	if(p==root)return;
	if(Fa[p]==root)root=p;
	int f=Fa[p],gf=Fa[f],son;
	if(Btree[f].son[0]==p){
		son=Btree[p].son[1]; Btree[p].son[1]=f; Btree[f].son[0]=son;
	}else{
		son=Btree[p].son[0]; Btree[p].son[0]=f; Btree[f].son[1]=son;
	}
	Fa[son]=f; Fa[p]=gf; Fa[f]=p;
	Union(f); Union(p);
	if(gf){if(Btree[gf].son[0]==f)Btree[gf].son[0]=p;else Btree[gf].son[1]=p;}
}
int Btreebuild(int l,int r){
	if(l>r)return 0;
	if(l==r){Btree[l+1].data=Btree[l+1].sum=A[l];Size[l+1]=1;return l+1;}
	int m=(l+r)>>1;
	Btree[m+2].son[0]=Btreebuild(l,m); Btree[m+2].son[1]=Btreebuild(m+2,r);
	Fa[Btree[m+2].son[0]]=Fa[Btree[m+2].son[1]]=m+2;
	Btree[m+2].data=A[m+1]; Union(m+2);
	return m+2;
}
void Update(int p){
	Btree[p].data=floor(sqrt(Btree[p].data));
	if(Size[Btree[p].son[0]]!=Btree[Btree[p].son[0]].sum)Update(Btree[p].son[0]);
	if(Size[Btree[p].son[1]]!=Btree[Btree[p].son[1]].sum)Update(Btree[p].son[1]);
	Union(p);
}
void Change(int l,int r){
	while(r+2!=root)Splay(r+2); while(l!=root)Splay(l);
	if(Btree[l].son[1]!=r+2)Splay(r+2);
	Update(Btree[r+2].son[0]); Union(r+2); Union(l);
}
long long Getsum(int l,int r){
	while(r+2!=root)Splay(r+2); while(l!=root)Splay(l);
	if(Btree[l].son[1]!=r+2)Splay(r+2);
	return Btree[Btree[r+2].son[0]].sum;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
	root=Btreebuild(0,n+1);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&ifdo,&l,&r); if(l>r)std::swap(l,r);
		if(!ifdo)Change(l,r);
		else{
			long long w=Getsum(l,r); printf("%lld\n",w);
		}
	}
}