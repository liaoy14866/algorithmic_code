#include<cstdio>
#include<algorithm>
#include<cmath>
int n,m,Threshold,Num,top;
unsigned int A[13000],B[13000];
int root[13000];
struct node{//一棵可持久化Trie树
	int ne[2],sum[2];
}Trie[500000];
int stktop; int stk[34];//用于拆分数字的玩意
void split(unsigned int x){//拆分数字
	for(stktop=33;stktop>=1;stktop--)stk[stktop]=0;
	stktop=0;
	for(;x;x>>=1)stk[++stktop]=x&1;
}
int Update(int p,int vi){//更新
	int now=++top; Trie[now]=Trie[p]; if(!vi)return now;
	Trie[now].ne[stk[vi]]=Update(Trie[p].ne[stk[vi]],vi-1); Trie[now].sum[stk[vi]]++;
	return now;
}
unsigned int Getmax(int x,int y,int vi){//求区间[l..r]与w最大的异或和，w被拆分到了stk中
	if(!vi)return 0;
	if(Trie[y].sum[stk[vi]^1]-Trie[x].sum[stk[vi]^1])
	return (1<<(vi-1))+Getmax(Trie[x].ne[stk[vi]^1],Trie[y].ne[stk[vi]^1],vi-1);
	else return Getmax(Trie[x].ne[stk[vi]],Trie[y].ne[stk[vi]],vi-1);
}
unsigned int Ans[120][120];//预处理的答案
unsigned int lastans;
unsigned int x,y;
int main(){
	int len,i,j,k,l,r,pl,pr;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&B[i]);
	for(i=1;i<=n;i++)A[i+1]=A[i]^B[i]; n++;
	Threshold=ceil(sqrt(n)); Num=n/Threshold; if(Num*Threshold<n)Num++;
	for(i=1;i<=n;i++){
		split(A[i]); root[i]=Update(root[i-1],33);//构建一棵可持久化Trie树
	}
	for(i=1;i<=Num;i++){
		l=(i-1)*Threshold+1; r=i*Threshold; if(r>n)r=n;
		for(j=l;j<=r;j++)
		for(k=j+1;k<=r;k++)
		Ans[i][i]=std::max(Ans[i][i],A[j]^A[k]);
	}
	for(len=2;len<=Num;len++)//预处理第i块到第j块的答案
	for(i=1;i<=Num;i++){
		j=i+len-1; if(j>Num)break; l=(i-1)*Threshold+1; r=i*Threshold; pr=j*Threshold; if(pr>n)pr=n;
		Ans[i][j]=std::max(Ans[i+1][j],Ans[i][i]);
		for(k=l;k<=r;k++){
			split(A[k]); Ans[i][j]=std::max(Ans[i][j],Getmax(root[i*Threshold],root[pr],33));
		}
	}
	for(i=1;i<=m;i++){
		scanf("%d%d",&x,&y); ((x+=lastans)%=(n-1))++; ((y+=lastans)%=(n-1))++; l=std::min(x,y); r=std::max(x,y); r++;
		pl=(l/Threshold)+(l%Threshold?1:0); pr=(r/Threshold)+(r%Threshold?1:0);
		lastans=Ans[pl+1][pr-1];//查询答案
		if(pl!=pr){
			for(j=l;j<=pl*Threshold;j++){split(A[j]);lastans=std::max(lastans,Getmax(root[j-1],root[r],33));}
			for(j=(pr-1)*Threshold+1;j<=r;j++){split(A[j]);lastans=std::max(lastans,Getmax(root[l-1],root[j],33));}
		}else{
			for(j=l;j<=r;j++){split(A[j]);lastans=std::max(lastans,Getmax(root[j-1],root[r],33));}
		}
		printf("%d\n",lastans);
	}
}