#include<cstdio>
#include<algorithm>
#include<stack>
#include<cmath>

long long none=1ll<<60;
struct Rec{
	int x,w,next;
};

int A[260010],Depth[260010],dfn[260010],vis[260010];
int n,m,top,tim,cnt,root,logn;
int Arrmap[260010],Tree[260010],Vtree[260010];
Rec Arre[510010],Etree[260010],Vetree[260010];
int Fa[260010];
int Fm[260010][30];
int point[260010],stk[260010];
long long F[260010],minn[260010];

inline void ins(int f,int s,int w){//插入无根树的边
	top++; Arre[top].x=s; Arre[top].next=Arrmap[f]; Arre[top].w=w; Arrmap[f]=top;
}
inline void Treeins(int f,int s,int w){//插入有根树的边
	top++; Etree[top].x=s; Etree[top].next=Tree[f]; Etree[top].w=w; Tree[f]=top; Fa[s]=f;
}
inline void Vtreeins(int f,int s){//插入虚树的边
	if(vis[f]!=tim){vis[f]=tim;Vtree[f]=0;}//这里用vis来判断
	top++; Vetree[top].x=s; Vetree[top].next=Vtree[f]; Vtree[f]=top;
}
void Treebuild(int x,int d){//建一棵有根树
	vis[x]=tim; cnt++; dfn[x]=cnt; Depth[x]=d;
	int v=Arrmap[x];
	while(v){
		if(vis[Arre[v].x]!=tim){
			Treeins(x,Arre[v].x,Arre[v].w);
			minn[Arre[v].x]=std::min(minn[x],(long long)Arre[v].w);
			Treebuild(Arre[v].x,d+1);
		}
		v=Arre[v].next;
	}
}

void lcainit(){//倍增lca的初始化
	logn=ceil(log(n)/log(2));
	for(int i=1;i<=n;i++)Fm[i][0]=Fa[i];
	for(int j=1;j<=logn;j++)
	for(int i=1;i<=n;i++)
	Fm[i][j]=Fm[Fm[i][j-1]][j-1];
}

int lca(int u,int v){//倍增lca
	if(Depth[u]<Depth[v])std::swap(u,v);
	int k=Depth[u]-Depth[v],l=0;
	while(k){if(k&1)u=Fm[u][l]; k=k>>1; l++;}
	if(u==v)return u;
	if(Fa[u]==Fa[v])return Fa[u];
	for(;;){
		for(k=1;k<=logn;k++)if(Fm[u][k]==Fm[v][k])break;
		k--;
		u=Fm[u][k]; v=Fm[v][k];
		if(Fa[u]==Fa[v])return Fa[u];
	}
}

bool Acmp(int a,int b){return dfn[a]<dfn[b];}
void Vtreebuild(int k){
	tim++; top=0; int stktop=0;
	std::sort(A+1,A+k+1,Acmp);//先按照dfn（dfs序的位置）排序
	stk[++stktop]=root;//先把根入栈
	int s=1; if(A[s]==root)s++;
	for(int vi=s;vi<=k;vi++){
		int l=lca(stk[stktop],A[vi]);//先求出lca
		while((Depth[l]<=Depth[stk[stktop-1]])&&(stktop>=2)){
			Vtreeins(stk[stktop-1],stk[stktop]); stktop--;//弹栈+连边
		}
		if(Depth[stk[stktop]]!=Depth[l]){//可能需要加入的lca
			Vtreeins(l,stk[stktop]); stk[stktop]=l;
		}
		stk[++stktop]=A[vi];//加入当前关键点
	}
	while(stktop>=2){
		Vtreeins(stk[stktop-1],stk[stktop]); stktop--;//最后清空栈
	}
}
void DFS(int x){//在虚树上DP
	if(point[x]==tim){F[x]=minn[x];return;}
	long long tmp=0;int v=Vtree[x];
	while(v){
		DFS(Vetree[v].x);
		tmp+=F[Vetree[v].x];
		v=Vetree[v].next;
	}
	F[x]=std::min((long long)minn[x],tmp);
}
void DP(int k){
	tim++;
	for(int vi=1;vi<=k;vi++)F[vi]=0,point[A[vi]]=tim;
	DFS(root);
}

int main(){
	scanf("%d",&n);//读入
	for(int i=1;i<=n-1;i++){
		int u,v,w; scanf("%d%d%d",&u,&v,&w);
		ins(u,v,w); ins(v,u,w);
	}
	root=1; tim++; top=0; minn[root]=none; Treebuild(root,1);//建一棵有根树
	lcainit();//倍增初始化
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int k;scanf("%d",&k); F[root]=0;
		for(int j=1;j<=k;j++)scanf("%d",&A[j]);//读入
		Vtreebuild(k);//建一棵虚树
		DP(k);//DP求解
		printf("%lld\n",F[root]);//输出
	}
}