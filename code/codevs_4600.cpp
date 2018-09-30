#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
	for(a=0;ch>='0'&&ch<='9';ch=getchar())(a*=10)+=ch-'0';
}
int T;
map<int,int> Fa;
int n;
int Getfa(int u){
	int v=u,o;
	if(Fa.find(u)==Fa.end()){Fa[u]=u;return u;}
	for(;u!=Fa[u];u=Fa[u]);
	for(o=Fa[v];Fa[v]!=u;Fa[v]=u,v=o,o=Fa[v]);
	return u; 
}
void unite(int u,int v){
	int fu=Getfa(u),fv=Getfa(v);
	if(fu!=fv)Fa[fu]=fv;
}
int top;
struct inf{
	int u,v;
};
inf U[1000010];
void init(){
	Fa.clear();
	top=0;
}
int work(){
	int vi,u,v,opt;
	read(n);
	for(vi=1;vi<=n;vi++){
		read(u),read(v),read(opt);
		if(opt)unite(u,v);else U[++top]=(inf){u,v};
	}
	for(vi=1;vi<=top;vi++)if(Getfa(U[vi].u)==Getfa(U[vi].v))return 0;
	return 1;
}
int main(){
	freopen("T.in","r",stdin); freopen("T.out","w",stdout);
	read(T);
	for(int vt=1;vt<=T;vt++){
		init();
		if(work())printf("YES\n");else printf("NO\n");
	}
}
