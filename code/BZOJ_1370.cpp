#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,ans;
int Fa[1100],Size[1100];
int Getfa(int u){
	if(!Fa[u]){Fa[u]=u;Size[u]=1;return u;}
	int v=u; for(;u!=Fa[u];u=Fa[u]);
	for(int o=Fa[v];u!=Fa[v];Fa[v]=u,v=o,o=Fa[v])Size[o]-=Size[v];
	return u;
}
void Union(int u,int v){
	int fu=Getfa(u),fv=Getfa(v); if(fu==fv)return;
	if(Size[fu]>Size[fv])std::swap(fu,fv); Fa[fu]=fv; Size[fv]+=Size[fu];
}
int Ene[1100][1100],Top[1100];
inline void ins(int f,int s){
	Top[f]++; Ene[f][Top[f]]=s;
}
bool vis[1100];
int main(){
	int i,j,u,v; char ch;
	read(n); read(m);
	for(i=1;i<=m;i++){
		for(ch=getchar();ch!='E'&&ch!='F';ch=getchar());
		read(u); read(v);
		if(ch=='F')Union(u,v);else ins(u,v),ins(v,u);
	}
	for(i=1;i<=n;i++)
	for(j=2;j<=Top[i];j++)Union(Ene[i][j-1],Ene[i][j]);
	for(i=1;i<=n;i++){
		j=Getfa(i); if(!vis[j]){vis[j]=1;ans++;}
	}
	printf("%d",ans);
}