#include<cstdio>
const int none=1e9+7;
int n,m,top;
struct node{
	int s[2],sum;
};
node Seg[6000000];
int A[110000],root[110000];
int Update(int p,int l,int r,int k){
	int now=++top; Seg[top]=Seg[p]; Seg[top].sum++;
	if(l==r)return now;int m=(l+r)>>1;
	if(k<=m)Seg[now].s[0]=Update(Seg[p].s[0],l,m,k);
	else Seg[now].s[1]=Update(Seg[p].s[1],m+1,r,k);
	return now;
}
int Getsum(int x,int y,int sl,int sr,int k){
	if(sl==sr)return sl;
	int sum=Seg[Seg[y].s[0]].sum-Seg[Seg[x].s[0]].sum,m=(sl+sr)>>1;
	if(sum>=k)return Getsum(Seg[x].s[0],Seg[y].s[0],sl,m,k);
	else return Getsum(Seg[x].s[1],Seg[y].s[1],m+1,sr,k-sum);
}
int main(){
	int i,li,ri,ki,wi;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&A[i]);
	for(i=1;i<=n;i++)root[i]=Update(root[i-1],-none,none,A[i]);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&li,&ri,&ki);
		wi=Getsum(root[li-1],root[ri],-none,none,ki);
		printf("%d\n",wi);
	}
}