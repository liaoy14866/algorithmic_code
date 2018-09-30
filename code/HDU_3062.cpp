#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
int top;
struct rec{
	int x,ne;
}Arre[1010*1010*2];
int Arrmap[1010*2];
inline void ins(int f,int s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
int n,m;
void init(){
	int vi,u[2],opt[2];
	for(vi=1;vi<=top;vi++)Arre[vi].x=Arre[vi].ne=0; top=0;
	memset(Arrmap,0,sizeof(Arrmap));
	for(vi=1;vi<=m;vi++){
		read(u[0]); read(u[1]); u[0]++; u[1]++; read(opt[0]); read(opt[1]);
		ins(u[0]+opt[0]*n,u[1]+(opt[1]^1)*n); ins(u[1]+opt[1]*n,u[0]+(opt[0]^1)*n);
	}
}
int tim,stktop,ant,cnt;
int dfn[1010*2],low[1010*2],stk[1010*2],vis[1010*2],flag[1010*2],Nar[1010*2];
void Tarjan(int x){
	low[x]=dfn[x]=++cnt; flag[x]=vis[x]=tim; stk[++stktop]=x; int v;
	for(v=Arrmap[x];v;v=Arre[v].ne)
	if(vis[Arre[v].x]!=tim){
		Tarjan(Arre[v].x); low[x]=min(low[x],low[Arre[v].x]);
	}else if(flag[Arre[v].x])low[x]=min(low[x],low[Arre[v].x]);
	if(low[x]==dfn[x]){
		ant++;
		while(stk[stktop]!=x){
			Nar[stk[stktop]]=ant; flag[stk[stktop]]=0; stk[stktop--]=0;
		}
		Nar[x]=ant; flag[x]=0; stk[stktop--]=0;
	}
}
bool handle(){
	int vi; tim++; ant=cnt=0;
	for(vi=n<<1;vi>=1;vi--)if(vis[vi]!=tim)Tarjan(vi);
	for(vi=1;vi<=n;vi++)if(Nar[vi]==Nar[vi+n])return 0;
	return 1;
}
int main(){
	bool fl;
	while(scanf("%d%d",&n,&m)!=EOF){
		init();
		fl=handle();
		if(fl)printf("YES\n");else printf("NO\n");
	}
}