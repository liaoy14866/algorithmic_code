/*
尝试了一下与线段树一致的标记
线段树标记表示儿子的信息，此时当前节点的信息已经修改过了
之前用Splay做翻转区间的时候，Splay直接记录的是当前节点的信息
下面的代码是记录儿子的信息。由此Flip与Push有些不同
*/
#include<cstdio>
struct Treenode{
	bool Tag;
	int data,son[2];
};

int n,m,root,Top;
int A[120000],Size[120000],Fa[120000];
Treenode Tree[120000];

void swap(int &a,int &b){int c=a;a=b;b=c;}

void Push(int p){
	if(Tree[p].Tag==false)return;
	for(int vi=0;vi<=1;vi++){
		int son=Tree[p].son[vi];
		Tree[son].Tag=!Tree[son].Tag;
		swap(Tree[son].son[0],Tree[son].son[1]);
	}
	Tree[p].Tag=false;
}

void Back(int p,int f,int gf){
	if(gf!=0){
		if(Tree[gf].son[0]==f)Tree[gf].son[0]=p;else Tree[gf].son[1]=p;
		Fa[p]=gf;
	}else Fa[p]=0;
	Size[f]=Size[Tree[f].son[0]]+Size[Tree[f].son[1]]+1;
	Size[p]=Size[Tree[p].son[0]]+Size[Tree[p].son[1]]+1;
}

void Splay(int p){
	int f,gf,son;
	if(p==root)return;
	if(Fa[p]==root)root=p;
	f=Fa[p]; gf=Fa[f];
	Push(f);
	if(Tree[f].son[0]==p){
		son=Tree[p].son[1];
		Tree[p].son[1]=f; Tree[f].son[0]=son;
	}
	else{
		son=Tree[p].son[0];
		Tree[p].son[0]=f; Tree[f].son[1]=son;
	}
	Fa[f]=p; Fa[son]=f;
	Back(p,f,gf);
}

int Build(int l,int r){
	if(l>r)return 0;
	if(l==r){
		Top++;
		Tree[Top].data=A[l]; Size[Top]=1;
		return Top;
	}
	int m=(l+r)>>1;
	int ls=Build(l,m); 
	int rs=Build(m+2,r);
	Top++;
	Tree[Top].son[0]=ls; Tree[Top].son[1]=rs; Tree[Top].data=A[m+1];
	Fa[ls]=Top; Fa[rs]=Top; Size[Top]=Size[ls]+Size[rs]+1;
	return Top;
}

int Rank(int p,int k){
	Push(p);
	if(Size[Tree[p].son[0]]==k-1)return p;
	else
	if(Size[Tree[p].son[0]]>k-1)return Rank(Tree[p].son[0],k);
	else
	return Rank(Tree[p].son[1],k-Size[Tree[p].son[0]]-1);
}

void Flip(int l,int r){
	int pl=Rank(root,l),pr=Rank(root,r+2);
	while(pr!=root)Splay(pr);
	while(pl!=root)Splay(pl);
	if(Tree[pl].son[1]!=pr)Splay(pr);
	int q=Tree[pr].son[0];
	swap(Tree[q].son[0],Tree[q].son[1]);
	Tree[q].Tag=!Tree[q].Tag;
}

void Print(int p){
	Push(p);
	if(Tree[p].son[0]!=0)Print(Tree[p].son[0]);
	if(Tree[p].data!=0)printf("%d ",Tree[p].data);
	if(Tree[p].son[1]!=0)Print(Tree[p].son[1]);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)A[i]=i;
	
	root=Build(0,n+1);
	
	for(int i=1;i<=m;i++){
		int l,r;
		scanf("%d%d",&l,&r);
		Flip(l,r);
	}
	
	Print(root);
	
	return 0;
}