/*
区间翻转……
*/

#include<cstdio>

struct Treenode{
	bool Tag;
	int son[2];
	int data;
};
Treenode Tree[400000];
int n,root,Top;
int A[400000],Size[400000],Fa[400000];

void swap(int&a,int&b){int c=a;a=b;b=c;}

void Push(int p){
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
	int son,f,gf;
	if(p==root)return;
	if(Fa[p]==root)root=p;
	f=Fa[p]; gf=Fa[f];
	Push(f); Push(p);
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
	if(p==root)return;
	int f=Fa[p],gf=Fa[f];
	if(gf==0)Splay(p);
	else
	if(((Tree[gf].son[0]==f)&&(Tree[f].son[0]==p))||
	((Tree[gf].son[1]==f)&&(Tree[f].son[1]==p)))
	{Splay(f);Splay(p);}
	else
	{Splay(p);Splay(p);}
}

int Build(int l,int r){
	if(l>r)return 0;
	if(l==r){
		Top++;
		Size[Top]=1; Tree[Top].data=A[l];
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
	return(Rank(Tree[p].son[1],k-Size[Tree[p].son[0]]-1));
}

void Flip(int l,int r){
	int pl=Rank(root,l),pr=Rank(root,r+2);
	while(pr!=root)Dplay(pr);
	while(pl!=root)Dplay(pl);
	if(Tree[pl].son[1]!=pr)Splay(pr);
	Tree[Tree[pr].son[0]].Tag=!Tree[Tree[pr].son[0]].Tag;
}

int main(){
	int Step=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);//读入
	root=Build(0,n+1);
	while(1){
		int w=Rank(root,2);//旋转
		if(Tree[w].data==1)break;
		Step++;
		Flip(1,Tree[w].data);
		if(Step>100000){Step=-1;break;}
	}
	printf("%d\n",Step);//输出
	return 0;
}