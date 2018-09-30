/*
先找到[l..r]的权值线段树，上面记录着[l..r]区间的所有的数字的last[i]。
再找到这些数字中last[i]属于[l..r]的sum。
每一种数字对于sum的贡献，就是这个数字在[l..r]区间上出现的次数times-1。
所以len-ans=sum。
*/

#include<cstdio>
struct Treenode{
	int son[2];
	int l,r,sum;
};

Treenode Seg[710000];
int n,m,maxn,top;
int A[41000],Times[41000],Last[41000],P[41000],B[41000],root[41000];

void swap(int &a,int &b){int c=a;a=b;b=c;}
void sort(int l,int r){//离散排序
	int tl=l,tr=r,x=A[(l+r)>>1];
	do{
		while(A[tl]<x)tl++; while(A[tr]>x)tr--;
		if(tl<=tr){swap(A[tl],A[tr]);swap(P[tl],P[tr]);tl++;tr--;}
	}
	while(tl<=tr);
	if(l<tr)sort(l,tr); if(tl<r)sort(tl,r);
}

int Build(int l,int r){//建一棵主席树
	top++; int now=top;
	Seg[now].l=l; Seg[now].r=r;
	if(l==r)return now;
	int m=(l+r)>>1;
	Seg[now].son[0]=Build(l,m); Seg[now].son[1]=Build(m+1,r);
	return now;
}

int Update(int p,int k){//更新
	top++; int now=top;
	Seg[now]=Seg[p]; Seg[now].sum++;
	if(Seg[p].l==Seg[p].r)return now;
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(k<=m)Seg[now].son[0]=Update(Seg[p].son[0],k);
	else Seg[now].son[1]=Update(Seg[p].son[1],k);
	return now;
}

int Getsum(int px,int py,int l,int r){//求在[l..r]的线段树上，last[i]在[l..r]中的有多少个
	if((Seg[px].l==l)&&(Seg[px].r==r))return Seg[py].sum-Seg[px].sum;
	int m=(Seg[px].l+Seg[px].r)>>1;
	if(r<=m)return Getsum(Seg[px].son[0],Seg[py].son[0],l,r);
	else
	if(m+1<=l)return Getsum(Seg[px].son[1],Seg[py].son[1],l,r);
	else
	return Getsum(Seg[px].son[0],Seg[py].son[0],l,m)
	+Getsum(Seg[px].son[1],Seg[py].son[1],m+1,r);
}

int main(){
	scanf("%d",&n);//读入
	for(int i=1;i<=n;i++){scanf("%d",&A[i]);P[i]=i;}
	
	sort(1,n);
	for(int i=1;i<=n;i++)if(A[i]==A[i-1])B[P[i]]=B[P[i-1]];//离散
	else B[P[i]]=B[P[i-1]]+1; maxn=B[P[n]];
	
	for(int i=1;i<=n;i++){Last[i]=Times[B[i]];Times[B[i]]=i;}//更新Last
	
	root[0]=Build(0,n);//建树
	for(int i=1;i<=n;i++)root[i]=Update(root[i-1],Last[i]);
	
	scanf("%d",&m);//处理询问
	for(int i=1;i<=m;i++){
		int l,r;
		scanf("%d%d",&l,&r);
		int sum=Getsum(root[l-1],root[r],l,r);
		int ans=r-l+1-sum;//计算与输出
		printf("%d\n",ans);
	}
	return 0;
}