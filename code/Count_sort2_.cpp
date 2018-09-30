#include<cstdio>
const int co=5;
const int base=1<<co;
int n,now=0;
int A[100010],Temp[100010];
int cnt[1<<(co+1)];
inline int num(int x,int k){return (x&((1<<(k+co))-1))>>k;}//k means func
int main(){
	freopen("T.in","r",stdin); freopen("T.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(;;){
		for(int i=1;i<base;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[num(A[i],now)]++;
		for(int i=1;i<base;i++)cnt[i]+=cnt[i-1];
		if(cnt[base-1]==cnt[0])break;
		for(int i=n;i>=1;i--){
		Temp[cnt[num(A[i],now)]]=A[i];
		cnt[num(A[i],now)]--;}
		for(int i=1;i<=n;i++)A[i]=Temp[i];
		now+=co;
	}
	for(int i=1;i<=n;i++)printf("%d ",A[i]);
}