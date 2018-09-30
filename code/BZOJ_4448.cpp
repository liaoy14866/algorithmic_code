/*
题目大意：给出一棵树，要求支持
1.查询路径上有多少点的点权大于ci
2.给一个点打上标记。一个点如果打上标记，在之后每一次操作，点权会自动+1
个人解法：
由于询问只和单点有关，不涉及区间合并，因此树链剖分拆开路径，查询转换为区间上的查询
考虑使用标准线line。定义真实权值为线段树的权值+line。
由于我们只需要查询有多少个是大于c的，于是对于还没有打上标记的，初始权值可以设置为-time。
等到time的时候被打上标记，于是刚刚好变为0。
这样把动态权值变成了静态权值。
查询便转换为，区间上有多少个数字大于c。
于是主席树即可。
关于不离散的想法：由于line最大只会有2e5，如果有负数，倒不如把所有的坐标加上2e5？ 
*/
#include<cstdio>
#include<algorithm>
inline void read(int &a){//读入优化
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,q,top,Root,none;
int Qtop,Otop,ifdo;
struct inf1{
	int u,v,c;
};
inf1 Que[210000];
int Ope[210000];

/*主席树*/
struct node{
	int l,r,m,sum,son[2];
};
node Seg[6100000];
int root[210000];
int Segbuild(int l,int r){
	int now=++top; Seg[now].l=l; Seg[now].r=r; Seg[now].m=(Seg[now].l+Seg[now].r)>>1;
	if(l==r)return now;
	Seg[now].son[0]=Segbuild(l,Seg[now].m); Seg[now].son[1]=Segbuild(Seg[now].m+1,r);
	return now;
}
int Update(int p,int k){
	int now=++top; Seg[now]=Seg[p]; Seg[now].sum++;
	if(Seg[p].l==Seg[p].r)return now;
	if(k<=Seg[p].m)Seg[now].son[0]=Update(Seg[p].son[0],k);
	else Seg[now].son[1]=Update(Seg[p].son[1],k);
	return now;
}
int Getsum(int x,int y,int minn,int maxn){
	int sum=Seg[y].sum-Seg[x].sum;
	if(Seg[x].l==minn&&Seg[x].r==maxn)return sum;
	if(maxn<=Seg[x].m)return Getsum(Seg[x].son[0],Seg[y].son[0],minn,maxn);
	else
	if(Seg[x].m+1<=minn)return Getsum(Seg[x].son[1],Seg[y].son[1],minn,maxn);
	else
	return Getsum(Seg[x].son[0],Seg[y].son[0],minn,Seg[x].m)
	+Getsum(Seg[x].son[1],Seg[y].son[1],Seg[x].m+1,maxn);
}
/*坐标全部加上一个大数none=q+1*/
inline int vpos(int a){return a+none;}
/*树链剖分*/
struct Rec{
	int x,next;
};
int Tree[210000];
Rec Etree[210000];
int Size[210000],Wson[210000],PIH[210000],Arr[210000],Top[210000],Fa[210000],Depth[210000];
int val[210000];//val[i] is the number which has been simplified
inline void ins(int f,int s){
	Etree[++top].x=s; Etree[top].next=Tree[f]; Tree[f]=top; Fa[s]=f;
}
void DFS1(int x,int d){
	int v=Tree[x],maxn=0; Size[x]=1; Depth[x]=d;
	while(v){
		DFS1(Etree[v].x,d+1);
		Size[x]+=Size[Etree[v].x];
		if(Size[Etree[v].x]>maxn){
			Wson[x]=Etree[v].x;
			maxn=Size[Etree[v].x];
		}
		v=Etree[v].next;
	}
}
void DFS2(int x,int f){
	Arr[++top]=val[x]; PIH[x]=top; Top[x]=f;
	if(Wson[x])DFS2(Wson[x],f);
	int v=Tree[x];
	while(v){
		if(Etree[v].x!=Wson[x])DFS2(Etree[v].x,Etree[v].x);
		v=Etree[v].next;
	}
}
int num;
int GetSeg(int u,int v,int minn,int maxn){
	int fu,fv,sum=0;
	while(Top[u]!=Top[v]){
		fu=Top[u];fv=Top[v];
		if(Depth[Fa[fu]]<Depth[Fa[fv]]){
			std::swap(u,v); std::swap(fu,fv);
		}
		num+=Depth[u]-Depth[fu]+1;
		sum+=Getsum(root[PIH[fu]-1],root[PIH[u]],minn,maxn);
		u=Fa[fu];
	}
	if(PIH[u]>PIH[v])std::swap(u,v);
	num+=Depth[v]-Depth[u]+1;
	sum+=Getsum(root[PIH[u]-1],root[PIH[v]],minn,maxn);
	return sum;
}
int main(){
	read(n);
	for(int i=1;i<=n;i++){//读入
		int w;scanf("%d",&w); if(w)ins(w,i);else Root=i;
	}
	read(q); none=q+1;
	//设定none=q+1的原因可以见下
	//询问的初始值:[-(q-1)+none,+无穷大]（最初我误以为ci可以无限大）
	//点权的初始值:[-q+none,-1+none]
	for(int i=1;i<=q;i++){
		read(ifdo);
		if(ifdo==1){
			Qtop++; read(Que[Qtop].u); read(Que[Qtop].v); read(Que[Qtop].c); Que[Qtop].c-=i-1;//在这里转换权值，变为静态权值
			Que[Qtop].c=vpos(Que[Qtop].c);//（起初误以为ci无穷大）一个询问相当于查询[Que[Qtop].c,+无穷大)上的数字有多少个
		}
		else{
			Otop++; read(Ope[Otop]); val[Ope[Otop]]=-i;
			val[Ope[Otop]]=vpos(val[Ope[Otop]]);//转换权值，变为静态权值
		}
	}
	top=0;
	DFS1(Root,1);
	DFS2(Root,Root);//树链剖分
	top=0;
	root[0]=Segbuild(0,none);//建一棵主席树
	for(int i=1;i<=n;i++)root[i]=Update(root[i-1],Arr[i]);
	for(int i=1;i<=Qtop;i++){//回答询问。其中num是记录路径上点的个数，而GetSeg返回的是[c,none]的数字的个数
		if(Que[i].c>none)Que[i].c=none;//起初误以为ci可以无穷大
		num=0;
		int w=GetSeg(Que[i].u,Que[i].v,Que[i].c,none);
		printf("%d %d\n",num,w);
	}
}