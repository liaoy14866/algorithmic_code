#include<cstdio>
#include<algorithm>
#include<vector>
#define ULL unsigned long long
#define LL long long
using namespace std;
char ch; bool fh;
inline void read(int &a){
	for(fh=0,ch=getchar();ch<'0'||ch>'9';ch=getchar())if(ch=='-')fh=1;
	for(a=0;ch>='0'&&ch<='9';ch=getchar())(a*=10)+=ch-'0'; if(fh)a=-a;
}
int n,m,T;
int A[510][510];
int main(){
	int vi,vj,x,y,k,s;
	freopen("T.in","r",stdin);
	read(n); read(m); read(T);
	for(vi=1;vi<=n;vi++)
	for(vj=1;vj<=m;vj++)read(A[vi][vj]);
	for(vi=1;vi<=n;vi++)
	for(vj=m;vj>=2;vj--)A[vi][vj]-=A[vi][vj-1];
	for(vi=1;vi<=n;vi++)A[vi][1]=0;
	for(vj=2;vj<=m;vj++)
	for(vi=n;vi>=2;vi--)A[vi][vj]-=A[vi-1][vj];
	for(vj=1;vj<=m;vj++)A[1][vj]=0;
	for(vi=1;vi<=n;vi++)
	for(vj=1;vj<=m;vj++)if(A[vi][vj])A[vi][vj]=1;
	for(vi=2;vi<=n;vi++)
	for(vj=2;vj<=m;vj++)A[vi][vj]+=A[vi-1][vj]+A[vi][vj-1]-A[vi-1][vj-1];
	for(vi=1;vi<=T;vi++){
		read(x); read(y); read(k);
		s=A[x+k-1][y+k-1]-A[x][y+k-1]-A[x+k-1][y]+A[x][y];
		if(s)printf("N\n");else printf("Y\n");
	}
}

