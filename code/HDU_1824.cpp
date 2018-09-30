#include<cstdio>
#include<algorithm>
using namespace std;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
int n,m;
int top;
int Arrmap[1010*3*2];
struct rec{
	int x,ne;
}Arre[1010*12+5010*2];
void ins(int f,int s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
int tim;
int ant,cnt,stktop;
int vis[1010*3*2],flag[1010*3*2],low[1010*3*2],dfn[1010*3*2],stk[1010*3*2],Nar[1010*3*2];
void Tarjan(int x){
	low[x]=dfn[x]=++cnt; vis[x]=flag[x]=tim; stk[++stktop]=x; int v;
	for(v=Arrmap[x];v;v=Arre[v].ne)
	if(vis[Arre[v].x]!=tim){
		Tarjan(Arre[v].x); low[x]=min(low[x],low[Arre[v].x]);
	}else if(flag[Arre[v].x]==tim)low[x]=min(low[x],low[Arre[v].x]);
	if(low[x]==dfn[x]){
		ant++;
		while(stk[stktop]!=x){
			Nar[stk[stktop]]=ant; flag[stk[stktop]]=0; stk[stktop--]=0;
		}
		Nar[x]=ant; flag[x]=0; stk[stktop--]=0;
	}
}
bool fl;
int main(){
	int i,u[3];
	while(scanf("%d%d",&n,&m)!=EOF){
		fl=1;
		for(i=1;i<=n;i++){
			read(u[0]); u[0]++; read(u[1]); u[1]++; read(u[2]); u[2]++;
			ins(u[0],u[1]+3*n); ins(u[0],u[2]+3*n); ins(u[0]+3*n,u[1]); ins(u[0]+3*n,u[2]);
			ins(u[1],u[2]); ins(u[1],u[0]+3*n); ins(u[1]+3*n,u[2]+3*n); ins(u[1]+3*n,u[0]);
			ins(u[2],u[1]); ins(u[2],u[0]+3*n); ins(u[2]+3*n,u[1]+3*n); ins(u[2]+3*n,u[0]);
		}
		for(i=1;i<=m;i++){
			read(u[0]); read(u[1]); u[0]++; u[1]++;
			ins(u[0],u[1]+3*n); ins(u[1],u[0]+3*n);
		}
		tim++; ant=cnt=0;
		for(i=n*3*2;i>=1;i--)if(vis[i]!=tim)Tarjan(i);
		for(i=n*3;i>=1;i--)if(Nar[i]==Nar[i+3*n]){
			fl=0; break;
		}
		if(fl)printf("yes\n");else printf("no\n");
		for(i=1;i<=n*3*2;i++)Arrmap[i]=0;
		for(i=1;i<=top;i++)Arre[top].x=Arre[top].ne=0; top=0;
	}
}