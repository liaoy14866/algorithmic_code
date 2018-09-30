#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>

struct Rec{int x,next;};
struct Treenode{int son[2],l,r,sum;};

int n,m,top,Troot,maxn,logn;
int A[120000],P[120000],B[120000],root[120000],Temp[120000];//关于离散的数组
int Arrmap[120000],Arr[120000],Fa[120000],Depth[120000];//关于建有根树与求Lca的工具数组
Rec Arre[240000];
bool vis[120000];
Treenode Seg[3000000];//主席树
int F[120000][30];

void read(int &a){//读优
    char c=getchar();
    for(a=0;(c<'0'||c>'9')&&c!='-';c=getchar());
    for(;c>='0'&&c<='9';c=getchar())(a*=10)+=c-'0';
}

void swap(int &a,int &b){int c=a;a=b;b=c;}//离散排序
void sort(int l,int r){
	int tl=l,tr=r,x=A[(l+r)>>1];
	do{
		while(A[tl]<x)tl++; while(A[tr]>x)tr--;
		if(tl<=tr){swap(A[tl],A[tr]);swap(P[tl],P[tr]);tl++;tr--;}
	}while (tl<=tr);
	if(l<tr)sort(l,tr); if(tl<r)sort(tl,r);
}

void Ins(int f,int s){//无根树的插入
	top++; 
	Arre[top].x=s; Arre[top].next=Arrmap[f]; Arrmap[f]=top;
}

int Update(int p,int k){//主席树的更新
	top++; int now=top;
	Seg[now]=Seg[p]; Seg[now].sum++;
	if(Seg[p].l==Seg[p].r)return now;
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(k<=m)Seg[now].son[0]=Update(Seg[p].son[0],k);
	else Seg[now].son[1]=Update(Seg[p].son[1],k);
	return now;
}

int Build(int l,int r){//建一棵空的线段树
	top++; int now=top;
	Seg[now].l=l; Seg[now].r=r;
	if(l==r)return now;
	int m=(l+r)>>1;
	Seg[now].son[0]=Build(l,m); Seg[now].son[1]=Build(m+1,r);
	return now;
}

void Treeins(int f,int s){//插入一条树边（其实只需要更新Fa、Depth以及插入一条主席树的链）
	Fa[s]=f; Depth[s]=Depth[f]+1;
	root[s]=Update(root[f],B[s]);
}

void Bfs(){//建一棵有根树
	int h=0,t=1; Arr[1]=Troot; vis[Troot]=true;
	root[Troot]=Update(root[0],B[Troot]);
	while(h!=t){
		h++; int v=Arrmap[Arr[h]];
		while(v!=0){
			if(vis[Arre[v].x]==false){
				t++; 
				Arr[t]=Arre[v].x; vis[Arr[t]]=true;
				Treeins(Arr[h],Arr[t]);
			}
			v=Arre[v].next;
		}
	}
}

int lca(int u,int v){//倍增求Lca
	if(Depth[u]<Depth[v])swap(u,v);
	int k=Depth[u]-Depth[v],l=0;
	while(k!=0){if(k%2==1)u=F[u][l]; 
	k=k>>1; 
	l++;}
	if(u==v)return u; if(Fa[u]==Fa[v])return Fa[u];
	while(1){
		for(k=1;k<=logn;k++)if(F[u][k]==F[v][k])break;
		k--; u=F[u][k]; v=F[v][k];
		if(Fa[u]==Fa[v])return Fa[u];
	}
}

/*线段树为Seg[u]-Seg[Fa[l]]+Seg[v]-Seg[l]*/
int Rank(int pu,int pv,int pfl,int pl,int k){//线段树上找第k大（小）
	if(Seg[pu].l==Seg[pu].r)return Seg[pu].l;
	int deta=Seg[Seg[pu].son[0]].sum+Seg[Seg[pv].son[0]].sum;
	deta-=(Seg[Seg[pfl].son[0]].sum+Seg[Seg[pl].son[0]].sum);
	if(deta>=k)return Rank(Seg[pu].son[0],Seg[pv].son[0],Seg[pfl].son[0],Seg[pl].son[0],k);
	else return Rank(Seg[pu].son[1],Seg[pv].son[1],Seg[pfl].son[1],Seg[pl].son[1],k-deta);
}

int main(){
	int lastans=0;
	read(n); read(m); logn=floor(log(n)/log(2));//读入
	for(int i=1;i<=n;i++){read(A[i]);P[i]=i;}
	
	sort(1,n);//离散
	for(int i=1;i<=n;i++)if(A[i]==A[i-1])B[P[i]]=B[P[i-1]];
	else {B[P[i]]=B[P[i-1]]+1;top++;Temp[top]=A[i];}
	
	maxn=B[P[n]]; top=0;
	for(int i=1;i<=n-1;i++){//读入无根树
		int u,v; read(u); read(v);
		Ins(u,v); Ins(v,u);
	}
	
	top=0; root[0]=Build(1,maxn);
	Troot=/*rand()%n+*/1;//随机不随机都无所谓
	
	Bfs();//转为有根树
	
	for(int i=1;i<=n;i++)F[i][0]=Fa[i];//倍增预处理
	for(int j=1;j<=logn;j++)
	for(int i=1;i<=n;i++)
	F[i][j]=F[F[i][j-1]][j-1];
	
	for(int i=1;i<=m;i++){
		int u,v,k,l;
		read(u); read(v); read(k); u=lastans^u;
		l=lca(u,v);
		/*线段树为Seg[u]-Seg[Fa[l]]+Seg[v]-Seg[l]*/
		int w=Rank(root[u],root[v],root[Fa[l]],root[l],k); //查询
		lastans=Temp[w];
		printf("%d",lastans);//输出
		if(m!=i)printf("\n");//输出格式有点无话可说
	}
	return 0;
}