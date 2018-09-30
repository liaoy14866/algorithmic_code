#include<cstdio>
struct Treenode{
	int son[2],l,r,sum;
};
Treenode Seg[3000000];//主席树
int A[200000],P[200000],B[200000],root[200000];
//A是原数组，PB是离散数组，root[i]记录第i个版本的线段树
int n,m,maxn,Top;

void swap(int &a,int &b){int c=a;a=b;b=c;}//交换

void sort(int l,int r){//离散排序
	int tl=l,tr=r,x=A[(l+r)>>1]; 
	do{
		while(A[tl]<x)tl++;while(A[tr]>x)tr--;
		if(tl<=tr){
			swap(A[tl],A[tr]);
			swap(P[tl],P[tr]);
			tl++; tr--;
		}
	}
	while(tl<=tr);
	if(l<tr)sort(l,tr);
	if(tl<r)sort(tl,r);
}

int Build(int l,int r){//先建一棵空的链表式线段树
	Top++;
	int q=Top;
	Seg[q].l=l; Seg[q].r=r;
	if(l==r)return q;
	int m=(l+r)>>1;
	int ls=Build(l,m);
	int rs=Build(m+1,r);
	Seg[q].son[0]=ls; Seg[q].son[1]=rs;
	return q;
}

int Update(int p,int k){//更新
	Top++; int now=Top;
	Seg[now]=Seg[p]; Seg[now].sum++;
	//显然，所经过的节点都要sum++，于是开一个新的节点记录
	//C++可以结构体赋值？涨姿势了
	if((Seg[p].l==k)&&(Seg[p].r==k))return now;
	//叶子节点就可以返回了
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(k<=m)Seg[now].son[0]=Update(Seg[p].son[0],k);
	else Seg[now].son[1]=Update(Seg[p].son[1],k);
	//更新下一个节点
	return now;
	//返回当前节点的下标
}

int Query(int p1,int p2,int k){
	if(Seg[p1].l==Seg[p1].r)return Seg[p1].l;
	//叶子节点就可以返回了
	int deta=Seg[Seg[p2].son[0]].sum-Seg[Seg[p1].son[0]].sum;
	//找到当前区间的线段树对应的权值
	if(deta>=k)return Query(Seg[p1].son[0],Seg[p2].son[0],k);
	else return Query(Seg[p1].son[1],Seg[p2].son[1],k-deta);
	//往下寻找
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){scanf("%d",&A[i]);P[i]=i;}
	sort(1,n);
	for(int i=1;i<=n;i++)B[P[i]]=i;//离散
	
	root[0]=Build(1,n);//建一棵线段树
	
	for(int i=1;i<=n;i++)root[i]=Update(root[i-1],B[i]);//建一棵主席树
	
	for(int i=1;i<=m;i++){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		int w=Query(root[l-1],root[r],k);//查询
		printf("%d\n",A[w]);//输出
	}
	return 0;
}