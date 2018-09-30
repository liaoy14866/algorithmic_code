#include<cstdio>
#include<algorithm>

struct node{int son[2];bool Tag;};//i节点的下标为i
int Fa[12000];//如果不是根节点，那么Fa[i]表示i在Splay中的父亲，否则为Splay最浅节点在原树中的父亲
int n,m;
char ifdo[10];
node Tree[12000];

void Pushdown(int p){//下传标记
	if(!Tree[p].Tag)return;
	std::swap(Tree[p].son[0],Tree[p].son[1]);
	Tree[Tree[p].son[0]].Tag^=1; Tree[Tree[p].son[1]].Tag^=1;
	Tree[p].Tag=false;
}

bool Beroot(int p){//判断是否为根
	return (Tree[Fa[p]].son[0]!=p)&&(Tree[Fa[p]].son[1]!=p);
}

void Splay(int p){//单旋
	int f,gf,son;
	f=Fa[p]; gf=Fa[f];
	Pushdown(f); Pushdown(p);//下传标记
	if(Beroot(p))return;
	if(Tree[f].son[0]==p){
		son=Tree[p].son[1]; Tree[f].son[0]=son; Tree[p].son[1]=f;
	}
	else
	if(Tree[f].son[1]==p){
		son=Tree[p].son[0]; Tree[f].son[1]=son; Tree[p].son[0]=f;
	}
	Fa[f]=p; Fa[son]=f; Fa[p]=gf;
	if(gf!=0){
		if(Tree[gf].son[0]==f)Tree[gf].son[0]=p;
		else
		if(Tree[gf].son[1]==f)Tree[gf].son[1]=p;
	}
}

void Access(int x){//重置x到根的路径，转为重链，用一棵Splay维护
	int t=0;//做完Access之后，这棵Splay上所有点都没有Tag了，这也是接下来的操作都没有Pushdown的原因
	while(x!=0){
		while(!Beroot(x))Splay(x); 
		Pushdown(x);
		//由于这里x要跳到x的Fa上，然而x可能之前一个点为Splay时候有一个Tag，所以要Pushdown
		//只要x经过了Splay，就会自己下传，这个没问题
		//但是一个节点为根的时候，不会Splay。所以需要人为下传一次 
		Tree[x].son[1]=t; t=x; x=Fa[x];
	}
}

void Make_root(int x){//重置根
	Access(x);//先重置x到根节点的树链
	while(!Beroot(x))Splay(x);//这条链上的信息全部需要翻转
	Tree[x].Tag^=1;//打一个标记。
}

void Link(int x,int y){//连接两棵树
	Make_root(x);//重置根
	Fa[x]=y;//接上树
}

void Cut(int x,int y){//断开两棵树
	Make_root(x); //重置根
	Access(y);//重置y到根节点的树链
	while(!Beroot(x))Splay(x);//把x旋转到根节点
	Tree[x].son[1]=0; Fa[y]=0;//断绝x与y的关系
}

int Find_root(int x){//找到x的根
	Access(x);//重置x到根的树链
	while(!Beroot(x))Splay(x);//把x旋转到根
	//这里可以不用Pushdown的原因是已经Access了 
	while(Tree[x].son[0]!=0)x=Tree[x].son[0];//找到深度最小的节点
	return(x);
}

int main(){
	scanf("%d%d",&n,&m);//读入
	for(int i=1;i<=m;i++){
		scanf("%s",ifdo);
		switch(ifdo[0]){
			case 'Q':{
				int u,v; scanf("%d%d",&u,&v);
				int fu=Find_root(u),fv=Find_root(v);
				if(fu==fv)printf("Yes\n");else printf("No\n");//查询
				break;
			}
			case 'C':{
				int u,v; scanf("%d%d",&u,&v);Link(u,v);break;//链接
			}
			case 'D':{
				int u,v; scanf("%d%d",&u,&v);Cut(u,v);break;//切断
			}
		}
	}
}