#include<cstdio>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,q,top,ans;
struct Rec{
	int u,v;
}E[210000];
int stktop;
int Stk[210000];
struct inf{
	int u,v,ifdo;
	//1 is A,2 is D,3 is Q
}Q[11000];
bool tag[5100][5100];
int Fa[5100],Size[5100];
int Getfa(int u){
	if(!Fa[u]){Fa[u]=u;Size[u]=1;return u;}
	int v=u; for(;u!=Fa[u];u=Fa[u]);
	for(int o=Fa[v];u!=Fa[v];Fa[v]=u,v=o,o=Fa[v])Size[o]-=Size[v];
	return u;
}
inline void swap(int &a,int &b){int c=a;a=b;b=c;}
void Union(int u,int v){
	int fu=Getfa(u),fv=Getfa(v); if(fu==fv)return;
	if(Size[fu]>Size[fv])swap(fu,fv); Fa[fu]=fv; Size[fv]+=Size[fu];
}
struct lik{/*邻接链表*/
	int la,x,ne;
}Arre[41000];
int Arrmap[5100];
inline void ins(int f,int s){/*插入边*/
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arre[Arrmap[f]].la=top; Arrmap[f]=top;
}
inline void del(int f,int s){/*暴力删除边*/
	int v;
	for(v=Arrmap[f];Arre[v].x!=s;v=Arre[v].ne);
	if(Arre[v].la)Arre[Arre[v].la].ne=Arre[v].ne;else Arrmap[f]=Arre[v].ne;
	if(Arre[v].ne)Arre[Arre[v].ne].la=Arre[v].la;
}
int vis[5100];
int tim;
void DFS(int x){/*遍历查找连通块*/
	vis[x]=tim;
	for(int v=Arrmap[x];v;v=Arre[v].ne){
		if(vis[Arre[v].x]!=tim)DFS(Arre[v].x);
	}
}
int main(){
	int i,j; char c;
	read(n); read(m);
	for(i=1;i<=m;i++)read(E[i].u),read(E[i].v);
	read(q);
	for(i=1;i<=q;i++){//读入与处理
		for(c=getchar();c!='A'&&c!='D'&&c!='Q';c=getchar());
		switch(c){
			case 'A':{
				read(Q[i].u); read(Q[i].v); Q[i].ifdo=1; break;
			}
			case 'D':{
				read(Q[i].u); read(Q[i].v); Q[i].ifdo=2;
				tag[Q[i].u][Q[i].v]|=1; tag[Q[i].v][Q[i].u]|=1;
				break;
			}
			case 'Q':{
				Q[i].ifdo=3; break;
			}
		}
	}
	for(i=1;i<=m;i++)if(!tag[E[i].u][E[i].v])Union(E[i].u,E[i].v);else Stk[++stktop]=i;//把不用删除边连接的点连起来
	for(i=1;i<=n;i++)Getfa(i);//首先全部路径压缩一趟，之后就用Fa[x]代表新图的x点
	for(i=1;i<=stktop;i++)if(Fa[E[Stk[i]].u]!=Fa[E[Stk[i]].v])
	ins(Fa[E[Stk[i]].u],Fa[E[Stk[i]].v]),ins(Fa[E[Stk[i]].v],Fa[E[Stk[i]].u]);//插入边
	stktop=0; tim++;
	for(i=1;i<=n;i++)if(vis[Fa[i]]!=tim){//把新图的点扔到Stk里面
		Stk[++stktop]=Fa[i]; vis[Fa[i]]=tim;
	}
	for(i=1;i<=q;i++){
		if(Q[i].ifdo==1&&Fa[Q[i].u]!=Fa[Q[i].v])ins(Fa[Q[i].u],Fa[Q[i].v]),ins(Fa[Q[i].v],Fa[Q[i].u]);//插入
		else
		if(Q[i].ifdo==2&&Fa[Q[i].u]!=Fa[Q[i].v])del(Fa[Q[i].u],Fa[Q[i].v]),del(Fa[Q[i].v],Fa[Q[i].u]);//删除
		else
		if(Q[i].ifdo==3){//查询
			tim++; ans=0; for(j=1;j<=stktop;j++)if(vis[Stk[j]]!=tim){
				ans++; DFS(Stk[j]);
			}
			printf("%d\n",ans);//输出
		}
	}
}