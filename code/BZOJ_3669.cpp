#include<cstdio>
#include<algorithm>

const int none=1e8;//初始化答案为none
struct Rec{
	int x,y,A,B;
	bool operator <(const Rec &r)const{return B<r.B;}
}; 
struct node{
	int maxpos,A,son[2];//A表示当前节点的A值，maxpos表示以当前节点为根的子树中，最大的点权是哪一个节点。
	bool Tag;
};
int n,m,ans;
Rec E[110000];//E[i]储存边
node Tree[160000];//在Splay中，第i条边拆分出来的虚点编号为i+n
int Fa[160000];

bool Beroot(int x){
	return (Tree[Fa[x]].son[0]!=x)&&(Tree[Fa[x]].son[1]!=x);
}

void Pushdown(int p){
	if(!Tree[p].Tag)return;
	std::swap(Tree[p].son[0],Tree[p].son[1]);
	Tree[Tree[p].son[0]].Tag^=1; Tree[Tree[p].son[1]].Tag^=1; Tree[p].Tag^=1;
}

void Update(int p){//用son的maxpos来更新它的maxpos
	int p1=Tree[Tree[p].son[0]].maxpos,p2=Tree[Tree[p].son[1]].maxpos;
	if(Tree[p1].A<Tree[p2].A)std::swap(p1,p2);
	if(Tree[p].A>Tree[p1].A)Tree[p].maxpos=p;else Tree[p].maxpos=p1;
}

void Splay(int p){
	int f=Fa[p],gf=Fa[f],son;
	Pushdown(f); Pushdown(p);
	if(Beroot(p))return;
	if(Tree[f].son[0]==p){
		son=Tree[p].son[1]; Tree[p].son[1]=f; Tree[f].son[0]=son;
	}
	else{
		son=Tree[p].son[0]; Tree[p].son[0]=f; Tree[f].son[1]=son;
	}
	Fa[p]=gf; Fa[son]=f; Fa[f]=p;
	if(gf!=0){
		if(Tree[gf].son[0]==f)Tree[gf].son[0]=p;
		else
		if(Tree[gf].son[1]==f)Tree[gf].son[1]=p;
	}
	Update(f); Update(p);
}

void Access(int x){
	int t=0;
	while(x!=0){
		while(!Beroot(x))Splay(x);
		Pushdown(x);
		Tree[x].son[1]=t;
		Update(x);//此处会删除或者加入新的Splay，需要更新maxpos
		t=x; x=Fa[x];
	}
} 

void Make_root(int x){
	Access(x);
	while(!Beroot(x))Splay(x);
	Tree[x].Tag^=1;
}

void Cut(int x,int y){
	Make_root(x);
	Access(y);
	while(!Beroot(x))Splay(x);
	Fa[y]=0; Tree[x].son[1]=0;
	Update(x);//此处会删除一些节点，需要更新maxpos
}

void Link(int x,int y){
	Make_root(x);
	Fa[x]=y;
}

int Find_root(int x){
	Access(x);
	while(!Beroot(x))Splay(x);
	while(Tree[x].son[0]!=0)x=Tree[x].son[0];
	return x;
}

int Find_maxpos(int x,int y){//找到x与y在最小生成树上点权最大的点是哪一个节点
	Make_root(x);
	Access(y);
	while(!Beroot(x))Splay(x);
	return Tree[x].maxpos;//返回节点的编号。这是一条边拆分出来的点的编号
}

int main(){
	scanf("%d%d",&n,&m);//读入
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",&E[i].x,&E[i].y,&E[i].A,&E[i].B);
		std::push_heap(E+1,E+i+1);
	}
	for(int i=m;i>=1;i--)std::pop_heap(E+1,E+i+1);//按照E[i].B排序
	
	for(int i=1;i<=m;i++)Tree[i+n].maxpos=i+n,Tree[i+n].A=E[i].A;//初始化
	for(int i=1;i<=n;i++)Tree[i].maxpos=i;
	ans=none;
	
	for(int i=1;i<=m;i++){//处理边
		int fu=Find_root(E[i].x),fv=Find_root(E[i].y);
		if(fu==fv){//如果这两条边之前已经在最小生成树中连接起来了
			int u=Find_maxpos(E[i].x,E[i].y);//找到最大的边权
			if(Tree[u].A>=E[i].A){//考虑环切
				Cut(E[u-n].x,u); Cut(E[u-n].y,u);
				Link(E[i].x,i+n); Link(E[i].y,i+n);
			}
		}
		else{
			Link(E[i].x,i+n); Link(E[i].y,i+n); //否则把它们相连
		}
		fu=Find_root(1); fv=Find_root(n);//寻找1到n是否有路径
		if(fu!=fv)continue;
		int w=Find_maxpos(1,n);
		ans=std::min(ans,E[i].B+Tree[w].A);//如果有，尝试更新答案
	}
	if(ans==none)printf("-1");else printf("%d",ans); //输出
}