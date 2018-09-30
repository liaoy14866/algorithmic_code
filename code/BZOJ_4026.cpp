#include<cstdio>
#include<cmath>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
const int intp=1e6+777;
int n,q;
int l[51000],r[51000];
int cnt;
int A[351000],L[351000],D[351000],SumA[351000],SumD[351000];
//L表示上一次出现的位置，D是处理之后的(p-1)/p,SumA是原来读入的数字的前缀积，SumD是D数组的前缀积。
int Bucket[1000010];//一个桶，记录上一次出现的位置

void Div(int x){//分解质因数
	if(x==1){A[++cnt]=1;return;}
	int sqrtx=ceil(sqrt(x));
	for(int vi=2;vi<=sqrtx;vi++){
		if(!(x%vi)){
			while(!(x%vi))x/=vi;
			A[++cnt]=vi;
		}
	}
	if(x!=1)A[++cnt]=x;
}
int power(int a,int b){//求逆元
	long long s=1,w=a;
	for(;b;w=w*w%intp,b>>=1)if(b&1)s=s*w%intp;
	return s;
}
/*线性筛求逆元*/
int top;
int inver[1000810];
bool flag[1000810];
int prime[1000000];
void Sieve(){
	inver[1]=1;
	for(int i=2,j;i<1e6+777;i++){
		if(!flag[i]){
			prime[++top]=i; inver[i]=power(i,intp-2);
		}
		j=1;
		while(i*prime[j]<1e6+777){
			flag[i*prime[j]]=1; inver[i*prime[j]]=(long long)inver[i]*inver[prime[j]]%intp;
			if(!(i%prime[j]))break; j++;
		}
	}
	top=0;
}
struct node{//主席树
	int l,r,m,s[2];
	int sum;
}Seg[351000*21];
int root[351000];
int Segbuild(int l,int r){//建一棵主席树
	int p=++top; Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1;
	if(l==r){Seg[p].sum=1;return p;}
	Seg[p].s[0]=Segbuild(l,Seg[p].m); Seg[p].s[1]=Segbuild(Seg[p].m+1,r);
	Seg[p].sum=(long long)Seg[Seg[p].s[0]].sum*Seg[Seg[p].s[1]].sum;
	return p;
}
int Update(int x,int k,int w){//更新节点
	int p=++top; Seg[p]=Seg[x]; Seg[p].sum=((long long)Seg[p].sum*w)%intp;
	if(Seg[x].l==Seg[x].r)return p;
	if(k<=Seg[x].m)Seg[p].s[0]=Update(Seg[x].s[0],k,w);else Seg[p].s[1]=Update(Seg[x].s[1],k,w);
	return p;
}
int Getsum(int x,int y,int l,int r){//求积
	if(Seg[x].l==l&&Seg[x].r==r)return (long long)Seg[y].sum*inver[Seg[x].sum]%intp;
	if(r<=Seg[x].m)return Getsum(Seg[x].s[0],Seg[y].s[0],l,r);
	else
	if(Seg[x].m+1<=l)return Getsum(Seg[x].s[1],Seg[y].s[1],l,r);
	else return 
	(long long)Getsum(Seg[x].s[0],Seg[y].s[0],l,Seg[x].m)*Getsum(Seg[x].s[1],Seg[y].s[1],Seg[x].m+1,r)%intp;
}
int lastans;
int main(){
	int i,w,li,ri,Lsum,Dsum,Asum,Psum;
	Sieve();//先筛一遍求逆元
	read(n); read(q); SumA[0]=SumD[0]=1;
	for(i=1;i<=n;i++){
		read(w); l[i]=r[i-1]+1; Div(w); r[i]=cnt; SumA[i]=(long long)SumA[i-1]*w%intp;//读入
	}
	for(i=1;i<=cnt;i++){//分解质因数，然后拆分到一个新的数组
		L[i]=Bucket[A[i]]; Bucket[A[i]]=i;
		if(A[i]==1)D[i]=1;else D[i]=((long long)A[i]-1)*inver[A[i]]%intp;
		SumD[i]=(long long)SumD[i-1]*D[i]%intp;
	}
	root[0]=Segbuild(0,cnt);//建一棵主席树
	for(i=1;i<=cnt;i++)root[i]=Update(root[i-1],L[i],D[i]);
	for(i=1;i<=q;i++){
		read(li); read(ri); li^=lastans; ri^=lastans;
		Asum=(long long)SumA[ri]*inver[SumA[li-1]]%intp;
		li=l[li]; ri=r[ri];
		Lsum=Getsum(root[li-1],root[ri],li,ri); Dsum=(long long)SumD[ri]*inver[SumD[li-1]]%intp;
		Psum=(long long)Dsum*inver[Lsum]%intp; //计算答案
		lastans=(long long)Asum*Psum%intp; printf("%d\n",lastans);//输出
	}
}