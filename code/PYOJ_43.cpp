#include<cstdio>
#include<algorithm>
inline void read(int &a){//读入优化（不太清楚有没有负数，按照负数的读入了）
    char c=getchar();
    bool f=0;
    for(a=0;(c<'0'||c>'9')&&c!='-';c=getchar());
    if(c=='-')f=1,c=getchar();
    for(;c>='0'&&c<='9';c=getchar())(a*=10)+=c-'0';
    if(f)a=-a;
}

struct node{//线段树
	int l,r,lmax,rmax,sum,ans;
};
int n,m;
int A[250000],T[250000];
node Seg[880000];
char ifdo[10];

inline void Union(node &p,const node &ls,const node &rs){//合并
	p.sum=ls.sum+rs.sum;
	p.lmax=std::max(ls.lmax,ls.sum+rs.lmax);
	p.rmax=std::max(rs.rmax,rs.sum+ls.rmax);
	p.ans=std::max(std::max(ls.ans,rs.ans),ls.rmax+rs.lmax);
}
inline void Update(int p,int k){//叶子节点的更新
	Seg[p].lmax=std::max(0,T[k]); Seg[p].rmax=Seg[p].lmax; Seg[p].sum=T[k];
	Seg[p].ans=Seg[p].lmax;
}
void Build(int p,int l,int r){//建一棵树
	Seg[p].l=l; Seg[p].r=r;
	if(l==r){Update(p,l); return;}
	int m=(Seg[p].l+Seg[p].r)>>1;
	Build(p<<1,l,m); Build(p<<1|1,m+1,r);
	Union(Seg[p],Seg[p<<1],Seg[p<<1|1]);
}
node Getmax(int p,int l,int r){//取区间的最大子段和
	if((Seg[p].l==l)&&(Seg[p].r==r))return Seg[p];
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(r<=m)return Getmax(p<<1,l,r);
	else
	if(m+1<=l)return Getmax(p<<1|1,l,r);
	else{
		node ls=Getmax(p<<1,l,m),rs=Getmax(p<<1|1,m+1,r),G;
		G.l=l; G.r=r; 
		Union(G,ls,rs);
		return G;
	}
}
void Change(int p,int k,int w){//单点修改
	if((Seg[p].l==k)&&(Seg[p].r==k)){Update(p,k); return;}
	int m=(Seg[p].l+Seg[p].r)>>1;
	if(k<=m)Change(p<<1,k,w);else Change(p<<1|1,k,w);
	Union(Seg[p],Seg[p<<1],Seg[p<<1|1]);
}
int main(){
	read(n);//读入
	for(int i=1;i<=n;i++)read(A[i]);
	for(int i=1;i<n;i++)T[i]=A[i]-A[i+1];//差分
	read(m);
	Build(1,1,n+m+10); n--;//建一棵树
	for(int i=1;i<=m;i++){
		scanf("%s",ifdo);
		if(ifdo[0]=='A'){
			int l,r; read(l); read(r); r--; if(l>r){printf("%d\n",0);continue;}//处理[i..i]这种查询
			node q=Getmax(1,l,r); int w=q.ans; printf("%d\n",w);//输出
			if(w>0){
				n++; A[n+1]=w; T[n]=A[n]-A[n+1]; 
				//加入一个点。由于只需要在最后面加入节点，所以可以先开很大的线段树，就不用动态玩节点了
				Change(1,n,T[n]);
			}
		}
		else{
			int l,r,w; read(l); read(r); read(w);
			if(l-1>=1){T[l-1]-=w; Change(1,l-1,T[l-1]);}//修改
			if(r<=n){T[r]+=w; Change(1,r,T[r]);}
			if(r==n+1)A[n+1]+=w;//在插入的时候用到了最后一个数字，所以需要同步更新最后一个数字
		}
	}
}