#include<cstdio>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int Fa[11000],Size[11000],maxn[11000];
int n;
inline void swap(int &a,int &b){int c=a;a=b;b=c;}
inline int max(int a,int b){if(a>b)return a;return b;}
int Getfa(int u){
	if(!Fa[u]){Fa[u]=maxn[u]=u;Size[u]=1;return u;}
	int v=u; for(;u!=Fa[u];u=Fa[u]);
	for(int o=Fa[v];u!=Fa[v];Fa[v]=u,v=o,o=Fa[v])Size[o]-=Size[v];
	return u;
}
bool tag[11000];
void Union(int u,int v){
	int fu=Getfa(u),fv=Getfa(v); if(fu==fv){tag[fu]|=1;return;}
	if(Size[fu]>Size[fv])swap(fu,fv); Fa[fu]=fv; Size[fv]+=Size[fu]; maxn[fv]=max(maxn[fu],maxn[fv]);
}
int main(){
	int i,u,v;
	read(n);
	for(i=1;i<=n;i++){
		read(u); read(v); Union(u,v);//合并
	}
	for(i=1;i<=10001;i++){
		u=Getfa(i);
		if(maxn[u]==i&&!tag[u]){//判断条件
		printf("%d\n",i-1);return 0;}
	}
}