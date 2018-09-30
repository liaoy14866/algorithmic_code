#include<cstdio>
#include<algorithm>
using namespace std;
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int n,m,top;
int Arrmap[2100];
struct rec{
	int x,ne;
}Arre[8100];
inline void ins(const int &f,const int &s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
int cnt,ant;
bool vis[2100],flag[2100];
int dfn[2100],low[2100],stk[2100],Nar[2100];
void Tarjan(const int &x){
	dfn[x]=low[x]=++cnt; vis[x]=flag[x]=1; stk[++top]=x; int v;
	for(v=Arrmap[x];v;v=Arre[v].ne)
	if(!vis[Arre[v].x]){
		Tarjan(Arre[v].x); low[x]=min(low[x],low[Arre[v].x]);
	}else if(flag[Arre[v].x])low[x]=min(low[x],low[Arre[v].x]);
	if(low[x]==dfn[x]){
		ant++;
		while(stk[top]!=x){
			Nar[stk[top]]=ant; flag[stk[top]]=0; stk[top--]=0;
		}
		Nar[stk[top]]=ant; flag[stk[top]]=0; stk[top--]=0;
	}
}
int Ans[2100];/*0表示不选择，1表示选择，2表示不知道*/
int h,t; int Arr[2100];
int done[2100]; int tim;
bool BFS(const int &fr,const int &to){
	tim++; h=0; t=1; Arr[1]=fr; done[fr]=tim; int v;
	while(h!=t){
		h++;
		for(v=Arrmap[Arr[h]];v;v=Arre[v].ne)if(done[Arre[v].x]!=tim){
			t++; Arr[t]=Arre[v].x; done[Arr[t]]=tim; if(Arr[t]==to)return 1;
		}
	}
	return 0;
}
int main(){
	int i,u[2]; bool opt[2];
	read(n); read(m);
	for(i=1;i<=m;i++){
		read(u[0]); opt[0]=(getchar()=='N'); read(u[1]); opt[1]=(getchar()=='N');
		ins(u[0]+(opt[0]^1)*n,u[1]+opt[1]*n); ins(u[1]+(opt[1]^1)*n,u[0]+opt[0]*n);
	}
	top=0;
	for(i=1;i<=n<<1;i++)if(!vis[i])Tarjan(i);
	for(i=1;i<=n;i++)if(Nar[i]==Nar[i+n]){
		printf("IMPOSSIBLE\n"); return 0;
	}
	for(i=1;i<=n;i++)if(BFS(i,i+n))Ans[i]=0;else if(BFS(i+n,i))Ans[i]=1;else Ans[i]=2;
	for(i=1;i<=n;i++)if(!Ans[i])printf("N");else if(Ans[i]&1)printf("Y");else printf("?");
}