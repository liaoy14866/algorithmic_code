#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
	for(a=0;ch>='0'&&ch<='9';ch=getchar())(a*=10)+=ch-'0';
}
const int intp=999961;
int T;
int Hash[intp];
struct inf{
	int x,ne;
};
inf H[1000010];
int top;
inline int h(int x){return x%intp;}
inline void ins(int x){
	int v=h(x);
	H[++top].x=x; H[top].ne=Hash[v]; Hash[v]=top;
}
inline int p(int x){
	int v=h(x);
	for(v=Hash[v];v;v=H[v].ne)if(H[v].x==x)return v;
	return 0;
}
int n;
int Fa[1000010];
inline int Getfa(int x){
	int u=p(x);
	if(!u){ins(x);Fa[top]=top;return top;}
	int v=u,o;
	for(;u!=Fa[u];u=Fa[u]);
	for(o=Fa[v];Fa[v]!=u;Fa[v]=u,v=o,o=Fa[v]);
	return u;
}
inline void unite(int x,int y){
	int fu=Getfa(x),fv=Getfa(y);
	if(fu!=fv)Fa[fu]=fv;
}
struct inv{
	int u,v;
};
inv U[1000010];
int tot;
void init(){
	//清空hash就好了，不用清空Fa 
	int vi;
	for(vi=0;vi<intp;vi++)Hash[vi]=0;
	top=0; tot=0;
}
int work(){
	int vi,u,v,opt;
	read(n);
	for(vi=1;vi<=n;vi++){
		read(u); read(v); read(opt);
		if(opt)unite(u,v);else U[++tot]=(inv){u,v};
	}
	for(vi=1;vi<=tot;vi++)if(Getfa(U[vi].u)==Getfa(U[vi].v))return 0;
	return 1;
}
int main(){
	read(T);
	for(int vt=1;vt<=T;vt++){
		init();
		if(work())printf("YES\n");else printf("NO\n");
	}
}