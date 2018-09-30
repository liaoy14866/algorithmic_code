/*
题目大意：
给出一片森林，要求支持：
1.查询路径第k小。
2.连一条边
思想：
如果用LCT，Splay中仅仅是按照Depth排序，不好按照大小来排序。
考虑如果没有连边操作，就可以直接上主席树了。
现在有连边操作。由于我们这棵主席树，只要可以求出lca以及lca的fa就好了。于是我们维护倍增的数组、以及深度，当然还有前缀主席树。
不必维护树的形态。
既然不必维护树的形态，在连边的时候，我们可以启发式合并。重构较小连通块的倍增数组与深度数组。
根据启发式的复杂度分析，一个点，被重构之后块的大小会变为2倍。于是一个点最多会被重构logn次。
每一次重构，更新数组的复杂度为O(1)，更新主席树的复杂度为O(logn)。于是总的时间复杂度为O(nlog^2n)，空间复杂度亦然。
*/
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>

inline void read(int &a){//读入优化
	char c; a=0;
	for(c=getchar();c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}

struct Rec{
	int x,next;
};
int T;
int n,m,t,top,cnt,tim,logn,lastans,tot;
struct num{
	int x,p;
};
num Temp[90000];
int val[90000],Arrmap[90000],Depth[90000],size[90000];
//size记录子树大小，不过只有根的size才有实际意义
int Ele[90000];
Rec Arre[170000];
char ifdo[10];
int F[90000][20];
int vis[90000];
struct node{
	int sum,l,r,son[2];
};
int root[90000];
node Seg[20000000];

inline void ins(int f,int s){//插入
	tot++; Arre[tot].x=s; Arre[tot].next=Arrmap[f]; Arrmap[f]=tot;
}

int SegBuild(int l,int r){//建一棵主席树
	top++; int now=top;
	Seg[now].l=l; Seg[now].r=r; if(l==r)return now;
	int m=(Seg[now].l+Seg[now].r)>>1;
	Seg[now].son[0]=SegBuild(l,m);
	Seg[now].son[1]=SegBuild(m+1,r);
	return now;
}

int Update(int p,int k){//主席树更新
	top++; int now=top;
	Seg[now]=Seg[p]; Seg[now].sum++;
	if(Seg[p].l==Seg[p].r)return now;
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(k<=m)Seg[now].son[0]=Update(Seg[p].son[0],k);
	else Seg[now].son[1]=Update(Seg[p].son[1],k);
	return now;
}

int Rank(int f,int l,int u,int v,int k){//查询第k小
	if(Seg[f].l==Seg[f].r)return Seg[f].l;
	int sum=Seg[Seg[u].son[0]].sum+Seg[Seg[v].son[0]].sum;
	sum-=Seg[Seg[f].son[0]].sum+Seg[Seg[l].son[0]].sum;
	if(sum>=k)return Rank(Seg[f].son[0],Seg[l].son[0],Seg[u].son[0],Seg[v].son[0],k);
	else return Rank(Seg[f].son[1],Seg[l].son[1],Seg[u].son[1],Seg[v].son[1],k-sum);
}

int lca(int u,int v){//查询lca
	if(Depth[u]<Depth[v])std::swap(u,v);
	int k=Depth[u]-Depth[v],l=0;
	while(k){
		if(k&1)u=F[u][l];
		k>>=1; l++;
	}
	if(u==v)return u;
	if(F[u][0]==F[v][0])return F[u][0];
	for(;;){
		for(k=1;k<=logn;k++)if(F[u][k]==F[v][k])break;
		k--; if(F[u][k]==F[v][k])return F[u][k];
		u=F[u][k]; v=F[v][k];
	}
}

int Make_root(int last,int x,int d){//重置x所在连通块的深度数组、倍增数组，前缀主席树，返回遍历到的点的个数（即连通块大小）
	int size=1;
	F[x][0]=last; Depth[x]=d; root[x]=Update(root[last],val[x]);
	for(int j=1;j<=logn;j++)F[x][j]=F[F[x][j-1]][j-1];
	vis[x]=tim; int v=Arrmap[x];
	while(v){
		if(vis[Arre[v].x]!=tim)size+=Make_root(x,Arre[v].x,d+1);
		v=Arre[v].next;
	}
	return size;
}

int Find_root(int x){//寻找x所在连通块的根
	int k=Depth[x]-1,l=0;
	while(k){
		if(k&1)x=F[x][l];
		k>>=1; l++;
	}
	return x;
}
void Link(int u,int v){//加入一条边
	if(!root[u])tim++,size[u]=Make_root(0,u,1);
	if(!root[v])tim++,size[v]=Make_root(0,v,1);
	int fu=Find_root(u),fv=Find_root(v);
	ins(u,v); ins(v,u);
	if(size[fu]<size[fv])std::swap(u,v),std::swap(fu,fv);
	tim++; vis[u]=tim; size[fu]+=Make_root(u,v,Depth[u]+1);
}
int Query(int u,int v,int k){//查询路径上第k小的数
	if(!root[u])tim++,size[u]=Make_root(0,u,1);
	if(!root[v])tim++,size[v]=Make_root(0,v,1);
	int l=lca(u,v);
	int w=Rank(root[F[l][0]],root[l],root[u],root[v],k);
	return Ele[w];
}
inline bool Acmp(const num &a,const num &b){return a.x<b.x;}
void Linit(){//初始化
	read(n); read(m); read(t); logn=log2(n);
	for(int i=1;i<=n;i++)read(Temp[i].x),Temp[i].p=i;
	std::sort(Temp+1,Temp+n+1,Acmp);//离散排序
	cnt=0;
	for(int i=1;i<=n;i++)
	if(Temp[i].x!=Temp[i-1].x)val[Temp[i].p]=val[Temp[i-1].p]+1,Ele[++cnt]=Temp[i].x;
	else val[Temp[i].p]=val[Temp[i-1].p];
	top=0;
	root[0]=SegBuild(1,val[Temp[n].p]);//建一棵主席树
	for(int i=1;i<=m;i++){
		int u,v; read(u); read(v);
		Link(u,v);//连一些初始的边
	}
}
int main(){
	read(T);//测试点编号
	Linit();//初始化
	for(int i=1;i<=t;i++){
		scanf("%s",ifdo);
		if(ifdo[0]=='Q'){
			int u,v,k; read(u); read(v); read(k); u=lastans^u; v=lastans^v; k=lastans^k;
			lastans=Query(u,v,k);//查询
			printf("%d\n",lastans);
		}
		else{
			int u,v; read(u); read(v); u=u^lastans; v=v^lastans;
			Link(u,v);//连接边
		}
	}
}