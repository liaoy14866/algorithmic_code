#include<cstdio>
const int base=10;
int n,now=1;
int A[100010],Temp[100010];
int cnt[11];
inline int num(int x,int k){return (x%(k*base))/k;}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(;;){
		for(int i=1;i<base;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[num(A[i],now)]++;
		for(int i=1;i<base;i++)cnt[i]+=cnt[i-1];
		if(cnt[base-1]==cnt[0])break;
		for(int i=n;i>=1;i--){Temp[cnt[num(A[i],now)]]=A[i];cnt[num(A[i],now)]--;}
		for(int i=1;i<=n;i++)A[i]=Temp[i];
		now*=base;
	}
	for(int i=1;i<=n;i++)printf("%d ",A[i]);
}