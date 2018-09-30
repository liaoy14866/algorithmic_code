#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int n,m,Threshold,Num,maxn;
int nowl,nowr;
int A[200100];
struct inf{
	int top;
	int A[470];
}Block[470];
struct que{
	int l,r,num;
}Q[200010];
inline bool Acmp(const que &a,const que &b){
	return a.l/Threshold!=b.l/Threshold?a.l<b.l:a.r<b.r;
}
void Change(int p,int w){
	if(p>maxn)return;
	p++; int po=(p-1)/Threshold+1; Block[po].A[p-(po-1)*Threshold]+=w;
	if(w>0&&Block[po].A[p-(po-1)*Threshold]==1)Block[po].top++;
	if(w<0&&Block[po].A[p-(po-1)*Threshold]==0)Block[po].top--;
}
int mex(){
	int vi,vj,sum;
	/*末尾的块时可以放在一起讨论的*/
	for(sum=0,vi=1;vi<=Num;vi++,sum+=Threshold)if(Block[vi].top!=Threshold)
	for(vj=1;vj<=Threshold;vj++)
	if(!Block[vi].A[vj])return sum+vj-1;
}
void Moarr(int l,int r){
	while(nowr<r){
		nowr++; Change(A[nowr],1);
	}
	while(nowl<l){
		Change(A[nowl],-1); nowl++;
	}
	while(nowl>l){
		nowl--; Change(A[nowl],1);
	}
	while(nowr>r){
		Change(A[nowr],-1); nowr--;
	}
}
int Ans[200010];
int main(){
	int i;
	read(n); read(m); maxn=n+5; Threshold=ceil(sqrt(maxn)); Num=maxn/Threshold; if(Num*Threshold<maxn)Num++;
	/*注意，事实上我们是维护的是Bucket[0..maxn-1]，我们把每个数字在块中都往右边移动了一个单位*/
	for(i=1;i<=n;i++)read(A[i]);
	for(i=1;i<=m;i++)read(Q[i].l),read(Q[i].r),Q[i].num=i;
	sort(Q+1,Q+m+1,Acmp);
	nowl=1; nowr=1; Change(A[1],1);
	for(i=1;i<=m;i++){
		Moarr(Q[i].l,Q[i].r);
		Ans[Q[i].num]=mex();
	}
	for(i=1;i<=m;i++)printf("%d\n",Ans[i]);
}