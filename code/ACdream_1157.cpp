#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,top,itop,qtop,maxn;
struct num{
	int x,p;
}A[200010];
inline bool Acmp(const num &a,const num &b){
	return a.x<b.x;
}
int B[200010];
int PIQ[100010];//PIQ[i]记录第i次插入操作在Q中的位置 
struct inf{
	int l,r,num,ans;
	int ope;//1表示插入，-1表示删除，0表示查询 
}Q[100010],tmp[100010];
void init(){
	top=itop=qtop=maxn=0; memset(Q,0,sizeof(Q));
	int vi,now; char ch;
	for(vi=1;vi<=n;vi++){
		for(ch=getchar();ch!='C'&&ch!='D'&&ch!='Q';ch=getchar());
		if(ch=='D'){
			Q[vi].ope=1; PIQ[++itop]=vi;
			top++; scanf("%d",&A[top].x); A[top].p=top; top++; scanf("%d",&A[top].x); A[top].p=top;
		}else if(ch=='C'){
			Q[vi].ope=-1;
			scanf("%d",&Q[vi].l);
		}else{
			Q[vi].ope=0; Q[vi].num=++qtop;
			top++; scanf("%d",&A[top].x); A[top].p=top; top++; scanf("%d",&A[top].x); A[top].p=top;
		}
	}
	sort(A+1,A+top+1,Acmp);
	for(vi=1;vi<=top;vi++)B[A[vi].p]=B[A[vi-1].p]+(A[vi].x!=A[vi-1].x); maxn=B[A[top].p];
	for(now=0,vi=1;vi<=n;vi++)
	if(Q[vi].ope==-1){
		Q[vi].r=Q[PIQ[Q[vi].l]].r; Q[vi].l=Q[PIQ[Q[vi].l]].l;
	}else{
		now++; Q[vi].l=B[now]; now++; Q[vi].r=B[now];
	}
}
int C[200010];
void Change(int p,int w){
	for(;p<=maxn;p+=p&-p)C[p]+=w;
}
int Getsum(int p){
	int sum=0; for(;p;p-=p&-p)sum+=C[p]; return sum;
}
void CDQ(const int &l,const int &r){
	if(l==r)return;
	int m=(l+r)>>1,tl=l,tr,tt;
	CDQ(l,m);
	CDQ(m+1,r);
	for(tr=m+1;tr<=r;tr++)if(!Q[tr].ope){
		while(Q[tl].r>=Q[tr].r&&tl<=m){
			if(Q[tl].ope)Change(Q[tl].l,Q[tl].ope); tl++;
		}
		Q[tr].ans+=Getsum(Q[tr].l);
	}
	for(tt=tl-1;tt>=l;tt--)if(Q[tt].ope)Change(Q[tt].l,-Q[tt].ope);
	for(tl=l,tr=m+1,tt=l;tt<=r;tt++)if((tr>r)||(tl<=m&&Q[tl].r>=Q[tr].r))tmp[tt]=Q[tl++];else tmp[tt]=Q[tr++];
	for(tt=l;tt<=r;tt++)Q[tt]=tmp[tt];
}
int Ans[100010];
void write(){
	int vi;
	for(vi=1;vi<=n;vi++)if(!Q[vi].ope)Ans[Q[vi].num]=Q[vi].ans;
	for(vi=1;vi<=qtop;vi++)printf("%d\n",Ans[vi]);
}
int main(){
	while(scanf("%d",&n)!=EOF){
		init();
		CDQ(1,n);
		write();
	}
}