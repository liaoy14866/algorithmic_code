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
int n,m;
int BIT[500010];
inline void Change(int p,int w){for(;p<=n;p+=p&-p)BIT[p]+=w;}
int Find(){
	int p,vi;
	for(vi=n;vi;vi-=vi&-vi)if(BIT[vi])p=vi;
	for(vi=(p&-p)>>1,p-=p&-p;vi;vi>>=1)if(!BIT[p|vi])p|=vi;
	return p+1;
}
int main(){
	int vi,opt,id;
	freopen("T.in","r",stdin); freopen("T.out","w",stdout);
	read(n); read(m);
	for(vi=1;vi<=m;vi++){
		read(opt);
		if(!opt)printf("%d\n",Find());else read(id),Change(id,opt);
	}
}
