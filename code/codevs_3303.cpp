/*
在这里，我的Splay的Tag记录的是当前的节点为子树的区间是否需要翻转。
与一般的Segment_Tree不同，Segment_Tree的Tag记录的是当前节点的子树的信息。
当然用Segment_Tree的Tag形式也是可以的。也许还好一些？
*/
#include<cstdio>
struct Treenode{
	int Data;
	int son[2];
	bool Tag;
};

Treenode Tree[150000];
int n,m,top,root;
int A[150000],Size[150000],Fa[150000];

void swap(int &a,int &b){int c=a; a=b; b=c;}

void Push(int p){
//Splay的下传时间与Segment_Tree的有所不同。
//一般来说，Segment_Tree的下传是要穿过这个节点的时候再下传，而Splay的下传则是只要拜访到就下传
	if(Tree[p].Tag==false)return;
	swap(Tree[p].son[0],Tree[p].son[1]);
	Tree[Tree[p].son[0]].Tag=!Tree[Tree[p].son[0]].Tag; 
	Tree[Tree[p].son[1]].Tag=!Tree[Tree[p].son[1]].Tag;
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
	Push(f); if(Tree[p].Tag==true)Push(p);
	//因为要拜访到f与p，所以f与p均要下传（下传时间没关系）。
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

void Dplay(int p){
//双旋是基于单旋的基础上的，所以最终关于旋转中标记下传都是单旋中完成，双旋中不必考虑
	int f,gf;
	if(p==root)return;
	f=Fa[p]; gf=Fa[f];
	if(gf==0)Splay(p);
	else
	if(((Tree[gf].son[0]==f)&&(Tree[f].son[0]==p))||
	((Tree[gf].son[1]==f)&&(Tree[f].son[1]==p)))
	{Splay(f);Splay(p);}
	else
	{Splay(p);Splay(p);}
}

int Build(int l,int r){
//初始化建一棵Splay。返回值为这一段区间在Splay中的根节点
	if(l>r)return 0;
	if(l==r){
		top++;
		Tree[top].Data=A[l]; Size[top]=1;
		return top;
	}
	int m=(l+r)>>1;
	int ls=Build(l,m);
	int rs=Build(m+2,r);
	top++;
	Tree[top].son[0]=ls; Tree[top].son[1]=rs; Tree[top].Data=A[m+1];
	Fa[ls]=top; Fa[rs]=top; 
	Size[top]=Size[Tree[top].son[0]]+Size[Tree[top].son[1]]+1;
	return top;
}

int Rank(int p,int k){
//拜访到了p，由此先下传p
	Push(p);
	if(Size[Tree[p].son[0]]==k-1)return p;
	else
	if(Size[Tree[p].son[0]]>k-1)return Rank(Tree[p].son[0],k);
	else
	return Rank(Tree[p].son[1],k-Size[Tree[p].son[0]]-1);
}

void Flip(int l,int r){
//区间翻转。
//由于我们需要把[l..r]一段区间放在一棵子树中，所以需要把l-1作为根节点，r+1作为子树根节点。
//这样会涉及到A[0]与A[n+1]的出现。由此我们要把0和n+1一同放入Splay中。
//这样一来，l-1就是子树中排名为l的节点，r+1就是子树中排名为r+2的节点。即Rank(root,l)与Rank(root,r+2)
//当然，由于是区间问题，记录在数组中的位置也是一个很好的方法
	int pl=Rank(root,l); int pr=Rank(root,r+2);
	while(pr!=root)Dplay(pr);
	while(pl!=root)Dplay(pl);
	if(Tree[pl].son[1]!=pr)Splay(pr);
	Tree[Tree[pr].son[0]].Tag=!Tree[Tree[pr].son[0]].Tag;
}

void Print(int p){
//输出。由于拜访到了p，所以先下传
	Push(p);
	if(Tree[p].son[0]!=0)Print(Tree[p].son[0]);
	if(Tree[p].Data!=0)printf("%d ",Tree[p].Data);
	if(Tree[p].son[1]!=0)Print(Tree[p].son[1]);
}

int main(){
	int l,r;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)A[i]=i;
	root=Build(0,n+1);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&l,&r);
		Flip(l,r);
	}
	Print(root);
}