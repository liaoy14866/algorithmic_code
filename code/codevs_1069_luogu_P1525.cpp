#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
char ch;
inline  void read(int &a){
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
	for(a=0;ch>='0'&&ch<='9';ch=getchar())(a*=10)+=ch-'0';
}
int n,m;
struct inf{
	int u,v,w;
};
inf A[100010];
int Fa[20010<<1];
int Getfa(int u){
	int v=u,o;
	for(;u!=Fa[u];u=Fa[u]);
	for(o=Fa[v];Fa[v]!=u;Fa[v]=u,v=o,o=Fa[v]);
	return u;
}
inline void unite(int u,int v){
	int fu=Getfa(u),fv=Getfa(v);
	if(fu!=fv)Fa[fu]=fv;
}
inline bool Acmp(const inf &a,const inf &b){return a.w>b.w;}
bool check(int uplen){
	int vi;
	for(vi=n<<1;vi>=1;vi--)Fa[vi]=vi;
	for(vi=1;vi<=uplen;vi++)unite(A[vi].u,A[vi].v+n),unite(A[vi].u+n,A[vi].v);
	for(vi=1;vi<=n;vi++)if(Getfa(vi)==Getfa(vi+n))return 0;
	return 1;
}
int main(){
	int vi;
	read(n); read(m);
	for(vi=1;vi<=m;vi++)read(A[vi].u),read(A[vi].v),read(A[vi].w);
	sort(A+1,A+m+1,Acmp);
	int tl=1,tr=m,mid;
	for(;tl!=tr;){
		mid=((tl+tr)>>1)+1;
		if(check(mid))tl=mid;else tr=mid-1;
	}
	printf("%d\n",A[tl+1].w);
}