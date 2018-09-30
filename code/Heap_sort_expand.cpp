#include<cstdio>
#include<algorithm>
struct num{
	int x;
	bool operator <(const num &a)const{return x>a.x;}
};
int n;
num A[101000];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{scanf("%d",&A[i].x);std::push_heap(A+1,A+i+1);}
	for(int i=n;i>=1;i--){std::pop_heap(A+1,A+i+1);}
	for(int i=n;i>=1;i--)printf("%d ",A[i].x); 
}