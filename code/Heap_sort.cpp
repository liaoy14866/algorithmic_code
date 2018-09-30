#include<cstdio>
#include<algorithm>
int n;
int A[100010];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){scanf("%d",&A[i]);std::push_heap(A+1,A+i+1);}
	for(int i=n;i>=1;i--)std::pop_heap(A+1,A+i+1);
	for(int i=1;i<=n;i++)printf("%d ",A[i]);
}