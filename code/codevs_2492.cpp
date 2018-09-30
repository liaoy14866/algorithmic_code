#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
struct link{
	int pre,ne;
};
link L[100010];
int n,m;
long long A[100010],BIT[100010];
inline void Change(int p,long long w){for(;p<=n;p+=p&(-p))BIT[p]+=w;}
inline long long Getsum(int p){long long sum=0;for(;p;p-=p&(-p))sum+=BIT[p];return sum;}
inline int Find(int x){
	if(A[x]!=1)return x;
	else return (L[x].ne=Find(L[x].ne));
}
int main(){
	int vi,opt,x,y;
	long long fin,det;
	scanf("%d",&n);
	for(vi=1;vi<=n;vi++)L[vi].ne=vi+1,L[vi].pre=vi-1,scanf("%lld",&A[vi]),Change(vi,A[vi]);
	A[n+1]=2;
	scanf("%d",&m);
	for(vi=1;vi<=m;vi++){
		scanf("%d %d %d",&opt,&x,&y); if(x>y)swap(x,y);
		if(opt)printf("%lld\n",Getsum(y)-Getsum(x-1));
		else for(x=Find(x);x<=y;x=L[x].ne){
			fin=floor(sqrt(A[x])); det=fin-A[x];
			Change(x,det); A[x]=fin;
			if(A[x]==1)L[L[x].pre].ne=L[x].ne,L[L[x].ne].pre=L[x].pre;
		}
	}
}
