#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
	for(a=0;ch>='0'&&ch<='9';ch=getchar())(a*=10)+=ch-'0';
}
int n;
struct inf{
	int p,h;
};
inf wood[100010];
inline bool Acmp(const inf &a,const inf &b){return a.h>b.h;}
int tot;
bool flag[100010];//以原来的pos为下标 
int Fa[100010];//以原来的pos为下标 
inline int Getfa(int u){
	int v=u,o;
	for(;u!=Fa[u];u=Fa[u]);
	for(o=Fa[v];Fa[v]!=u;Fa[v]=u,v=o,o=Fa[v]);
	return u;
}
inline void unite(int u,int v){
	int fu=Getfa(u),fv=Getfa(v);
	if(fu!=fv)Fa[fu]=fv;
}
long long ans;
int main(){
	int vi,vj;
	read(n);
	for(vi=1;vi<=n;vi++)wood[vi].p=vi,read(wood[vi].h),Fa[vi]=vi;
	sort(wood+1,wood+n+1,Acmp);
	for(vi=wood[1].h,vj=1;vi>=1;vi--){
		for(;wood[vj].h>=vi;vj++){
			tot++; flag[wood[vj].p]=1;
			if(flag[wood[vj].p-1])unite(wood[vj].p,wood[vj].p-1),tot--;
			if(flag[wood[vj].p+1])unite(wood[vj].p,wood[vj].p+1),tot--;
		}
		ans+=tot;
	}
	printf("%lld\n",ans);
}