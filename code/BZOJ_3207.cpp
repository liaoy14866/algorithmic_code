#include<cstdio>
#include<algorithm>
inline void read(int &a){//读入优化
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
const unsigned long long intp=1e12+7;
const unsigned long long base=233339;
/*
不知道是不是质数，随便取了一个
据说字符串Hash只取一个模数很容易被卡。刚开始也没有准备AC。起初模数只有1e6的大小，不冲突的概率都是1?5……
后来看了别人的程序，尝试把模数调大了。
结果本来应该先模一个大质数再模一个小质数来着？只模了一次就过来……
*/
int n,m,k;
unsigned long long now;
int top;
struct inf1{
	unsigned long long x;
	int p;
};
inf1 A[410000];
int Q[210000];
int cnt;
inline void Apush(unsigned long long q){
	A[++top].x=q; A[top].p=top;
}
inline bool Acmp(const inf1 a,const inf1 b){
	return a.x<b.x;
}
int B[410000],L[210000],R[210000];//离线，并且离散了操作，L与R为询问的端点
struct node{
	int l,r,m,sum,son[2];
};
node Seg[4210000];//主席树
int root[210000];
int Segbuild(int l,int r){//建一棵主席树
	int now=++top; Seg[now].l=l; Seg[now].r=r; Seg[now].m=(l+r)>>1;
	if(l==r)return now;
	Seg[now].son[0]=Segbuild(l,Seg[now].m); Seg[now].son[1]=Segbuild(Seg[now].m+1,r);
	return now;
}
int SegUpdate(int p,int k){//主席树的更新
	int now=++top; Seg[now]=Seg[p]; Seg[now].sum++;
	if(Seg[p].l==Seg[p].r)return now;
	if(k<=Seg[p].m)Seg[now].son[0]=SegUpdate(Seg[p].son[0],k);
	else Seg[now].son[1]=SegUpdate(Seg[p].son[1],k);
	return now;
}
int Getsum(int x,int y,int k){//主席树上，在[l..r]上找权值为k的数有多少个
	for(;Seg[x].l!=Seg[x].r;
	x=(k<=Seg[x].m)?Seg[x].son[0]:Seg[x].son[1],y=(k<=Seg[y].m)?Seg[y].son[0]:Seg[y].son[1]);
	return Seg[y].sum-Seg[x].sum;
}
int main(){
	read(n); read(m); read(k);//读入
	for(int i=1;i<=n;i++)read(Q[i]);
	for(int i=1;i<=n-k+1;i++){
		now=0; for(int j=i;j<=i+k-1;j++)now=(now*base+Q[j])%intp;
		Apush(now);
	}
	for(int i=1;i<=m;i++){
		read(L[i]); read(R[i]); int w; now=0;
		for(int j=1;j<=k;j++){read(w); now=(now*base+w)%intp;}
		Apush(now);
	}//离散排序
	std::sort(A+1,A+top+1,Acmp);
	B[A[1].p]=1;
	for(int i=2;i<=top;i++)B[A[i].p]=(A[i].x==A[i-1].x)?B[A[i-1].p]:B[A[i-1].p]+1;
	cnt=top; top=0;
	root[0]=Segbuild(1,B[A[cnt].p]);//建一棵主席树
	for(int i=1;i<=n-k+1;i++)root[i]=SegUpdate(root[i-1],B[i]);
	for(int i=n-k+2;i<=cnt;i++){
		int l=L[i-(n-k+1)]-1,r=R[i-(n-k+1)]-k+1;
		if(!Getsum(root[L[i-(n-k+1)]-1],root[R[i-(n-k+1)]-k+1],B[i]))//查询
		printf("Yes\n");else printf("No\n");//输出
	}
}