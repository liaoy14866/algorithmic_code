void Back(int p,int f,int gf){
	if (gf!=0){
		if (Tree[gf].son[0]==f)Tree[gf].son[0]=p;else Tree[gf].son[1]=p;
		Fa[p]=gf;
	}else Fa[p]=0;
	Size[f]=Size[Tree[f].son[0]]+Size[Tree[f].son[1]]+Tree[f].Num;
	Size[p]=Size[Tree[p].son[0]]+Size[Tree[p].son[1]]+Tree[p].Num;
}

//旋转
void Splay(int p){
	int f,gf,son;
	if (p==root)return;
	if (Fa[p]==root)root=p;
	f=Fa[p]; gf=Fa[f];
	if (Tree[f].son[0]==p)//右旋
	{son=Tree[p].son[1]; Tree[p].son[1]=f; Tree[f].son[0]=son;}
	else//左旋
	{son=Tree[p].son[0]; Tree[p].son[0]=f; Tree[f].son[1]=son;}
	Fa[f]=p; Fa[son]=f;
	Back(p,f,gf);
}

//双旋
void Splay(int p){
	int f,gf,son;
	if (p==root)return;
	if (Fa[p]==root)root=p;
	f=Fa[p]; gf=Fa[f];
	if (Tree[f].son[0]==p)
	{son=Tree[p].son[1]; Tree[p].son[1]=f; Tree[f].son[0]=son;}//右旋
	else
	{son=Tree[p].son[0]; Tree[p].son[0]=f; Tree[f].son[1]=son;}//左旋
	Fa[f]=p; Fa[son]=f;
	Back(p,f,gf);
}

//插入
void Ins(int w){
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

//查找前驱
int Prefix(int p){
	if (Tree[p].son[0]!=0) return(maxintree(Tree[p].son[0]));
	int f=Fa[p];
	while (f!=0&&Tree[f].son[0]==p){
		p=f; 
		f=Fa[f];
	}
	return f;
}

//查找后继
int Suffix(int p){
	if (Tree[p].son[1]!=0) return(minintree(Tree[p].son[1]));
	int f=Fa[p];
	while (f!=0&&Tree[f].son[1]==p){
		p=f;
		f=Fa[f];
	}
	return f;
}

//删除
void Delete(int p){
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
	Size[l]-=Tree[p].Num; Size[r]-=Tree[p].Num; Size[p]=0;
	Fa[p]=0;
}

//查找第k小
int Rank(int p,int k){
	if ((Tree[p].son[0]!=0)&&(Size[Tree[p].son[0]]>=k))return(Rank(Tree[p].son[0],k));
	if (Tree[p].Num>=k-Size[Tree[p].son[0]])return p;
	return(Rank(Tree[p].son[1],k-Size[Tree[p].son[0]]-Tree[p].Num));
}