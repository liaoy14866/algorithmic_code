/*
给出一张每个点出度为1的图。求环的个数。
发现每个环只能在链的最低端。从任意一个点开始，并查集连接next即可。
黄学长的方法是直接全部连起来，每一个连通块自然有一个环。于是找连通块即可。
*/
#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,ans;
int next[1100000],Fa[1100000],Size[1100000];
bool vis[1100000];
int Getfa(int u){
	if(!Fa[u]){Fa[u]=u;Size[u]=1;return u;}
	int v=u; for(;u!=Fa[u];u=Fa[u]);
	for(int o=Fa[v];u!=Fa[v];Fa[v]=u,v=o,o=Fa[v])Size[o]-=Size[v];
	return u;
}
bool Union(int u,int v){
	int fu=Getfa(u),fv=Getfa(v); if(fu==fv)return 0;
	if(Size[fu]>Size[fv])std::swap(fu,fv); Fa[fu]=fv; Size[fv]+=Size[fu]; return 1;
}
int main(){
	int i,j;
	read(n);
	for(i=1;i<=n;i++)read(next[i]);
	for(i=1;i<=n;i++){
		for(j=i;!vis[j];j=next[j]){
			vis[j]=1; if(!Union(j,next[j])){ans++;break;}
		}
	}
	printf("%d\n",ans);
}