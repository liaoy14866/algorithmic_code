#include<cstdio>
struct node{
	int l,r,son[2],sum;
};

int n,m,lim,top;
int root[310000],A[310000];
node Seg[8100000];//主席树

int Build(int l,int r){//建一棵空树
	top++; int now=top;
	Seg[now].l=l;Seg[now].r=r;if(l==r)return now;
	m=(l+r)>>1;
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

int Getmax(int x,int y,int len){//找到最大的数字
	int deta=Seg[x].sum-Seg[y].sum;
	if(deta<=len)return -1;
	if(Seg[x].l==Seg[x].r)return Seg[x].l;
	deta=Seg[Seg[x].son[0]].sum-Seg[Seg[y].son[0]].sum;
	if(deta>len)return Getmax(Seg[x].son[0],Seg[y].son[0],len);
	deta=Seg[Seg[x].son[1]].sum-Seg[Seg[y].son[1]].sum;
	if(deta>len)return Getmax(Seg[x].son[1],Seg[y].son[1],len);
	return -1;//如果两个儿子都没有也要弹出-1
}

int main(){
	scanf("%d%d",&n,&lim);//读入
	
	root[0]=Build(1,lim);//建树
	
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1;i<=n;i++)root[i]=Update(root[i-1],A[i]);//建一棵主席树
	
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int l,r; scanf("%d%d",&l,&r);
		int w=Getmax(root[r],root[l-1],(r-l+1)/2);//回答询问
		if(w==-1)printf("no\n");
		else printf("yes %d\n",w);
	}
}