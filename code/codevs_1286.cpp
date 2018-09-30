#include<cstdio>
struct treenode{
	int son[2],data,Num;
};
int n,minn,k,Line,root,top,Leave;
treenode Tree[600010];
int Fa[600010],Size[600010];
char ifdo[5];

void Back(int p,int f,int gf){
	if (gf!=0){
		if (Tree[gf].son[0]==f)Tree[gf].son[0]=p;else Tree[gf].son[1]=p;
		Fa[p]=gf;
	}else Fa[p]=0;
	Size[f]=Size[Tree[f].son[0]]+Size[Tree[f].son[1]]+Tree[f].Num;
	Size[p]=Size[Tree[p].son[0]]+Size[Tree[p].son[1]]+Tree[p].Num;
}

void Splay(int p){//左旋与右旋
	int f,gf,son;
	if (p==root)return;
	if (Fa[p]==root)root=p;
	f=Fa[p]; gf=Fa[f];
	if (Tree[f].son[0]==p){
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

void Dplay(int p){//双旋
	int gf,f;
	if (p==root)return;
	f=Fa[p]; gf=Fa[f];
	if (gf==0){Splay(p);}
	else
	if ((Tree[gf].son[0]==f&&Tree[f].son[0]==p)||(Tree[gf].son[1]==f&&Tree[f].son[1]==p))
	{Splay(f);Splay(p);}
	else{Splay(p);Splay(p);}
}

void Ins(int w){//插入一个节点
	if (root==0){
		top++;
		root=top;
		Tree[root].data=w;
		Size[top]=1;
		Tree[top].Num=1;
		return;
	}
	int p=root;
	while (1){
		Size[p]++;
		if (Tree[p].data<w){
			if (Tree[p].son[1]==0){
				top++;
				Tree[top].data=w;
				Tree[p].son[1]=top;Fa[top]=p;
				Size[top]=1;Tree[top].Num=1;
				p=top;
				break;
			}
			else p=Tree[p].son[1];
		}
		else
		if (Tree[p].data>w){
			if (Tree[p].son[0]==0){
				top++;
				Tree[top].data=w;
				Tree[p].son[0]=top;Fa[top]=p;
				Size[top]=1;Tree[top].Num=1;
				p=top;
				break;
			}
			else p=Tree[p].son[0];
		}
		else{
			Tree[p].Num++;
			break;
		}
	}
	while (p!=root)Dplay(p);
}

int maxintree(int p){
	while (Tree[p].son[1]!=0)p=Tree[p].son[1];
	return p;
}
int minintree(int p){
	while (Tree[p].son[0]!=0)p=Tree[p].son[0];
	return p;
}

int Prefix(int p){//查找前驱
	if (Tree[p].son[0]!=0) return(maxintree(Tree[p].son[0]));
	int f=Fa[p];
	while (f!=0&&Tree[f].son[0]==p){
		p=f; 
		f=Fa[f];
	}
	return f;
}

int Suffix(int p){//查找后继
	if (Tree[p].son[1]!=0) return(minintree(Tree[p].son[1]));
	int f=Fa[p];
	while (f!=0&&Tree[f].son[1]==p){
		p=f;
		f=Fa[f];
	}
	return f;
}

void Delete(int p){//删除一个点
	if (Tree[p].Num>=2){Tree[p].Num--;Size[p]--;return;}
	while (p!=root)Dplay(p);
	if (Tree[p].son[0]==0&&Tree[p].son[1]!=0){root=Tree[p].son[1];Fa[root]=0;return;}
	else
	if (Tree[p].son[1]==0&&Tree[p].son[1]!=0){root=Tree[p].son[0];Fa[root]=0;return;}
	else
	if (Tree[p].son[1]==0&&Tree[p].son[0]==0){root=0;Fa[root]=0;return;}
	int l=Prefix(p);while (l!=root)Dplay(l);
	int r=Suffix(p);while (r!=root)Dplay(r);
	if (Tree[root].son[1]!=r)Splay(r);
	int f=Fa[p];
	if (Tree[f].son[0]==p)Tree[f].son[0]=0;else Tree[f].son[1]=0;
	Size[l]--; Size[r]--; Size[p]=0;
	Fa[p]=0;
}

void Subdelete(int floor,int ifdo){//删除比floor小的节点
    Ins(floor);
    if (Tree[root].son[0]!=0){
    	if (ifdo==0)Leave+=Size[Tree[root].son[0]];
    	Size[root]-=Size[Tree[root].son[0]];
    	Tree[root].son[0]=0;
	}
	Delete(root);
}

int Rank(int p,int k){//查找第k小的数
	if ((Tree[p].son[0]!=0)&&(Size[Tree[p].son[0]]>=k))return(Rank(Tree[p].son[0],k));
	if (Tree[p].Num>=k-Size[Tree[p].son[0]])return p;
	return(Rank(Tree[p].son[1],k-Size[Tree[p].son[0]]-Tree[p].Num));
}

int main(){
	scanf("%d%d",&n,&minn);
	for (int i=1;i<=n;i++){
		scanf("%s%d",ifdo,&k);
		switch(ifdo[0]){
			case 'I':{Ins(k+Line);Subdelete(minn+Line,1);break;}
			case 'A':{Line-=k;break;}
			case 'S':{Line+=k;Subdelete(minn+Line,0);break;}
			case 'F':{
				if (Size[root]<k)printf("%d\n",-1);
				else{
					int w=Rank(root,Size[root]-k+1);
			    	printf("%d\n",Tree[w].data-Line);
				}
				break;
			}
		}
	}
	printf("%d\n",Leave);
	return 0;
}