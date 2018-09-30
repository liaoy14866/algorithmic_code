#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
struct Rec{
	int x,next;
};
const int none=1e8;
int w[2100][2100];
int Arrmap[2100],Pre[2100];
bool vis[2100];
Rec Arre[120000];
int n,m,s,t,ms,mt,top,ans;
inline void ins(int f,int s){top++;Arre[top].x=s;Arre[top].next=Arrmap[f];Arrmap[f]=top;}
bool BFS(){
	memset(Pre,0,sizeof(Pre)); memset(vis,false,sizeof(vis)); std::queue<int> Arr;
	vis[s]=true; Arr.push(s);
	while(!Arr.empty()){
		int u=Arr.front(),v=Arrmap[u]; Arr.pop();
		while(v!=0){
			if((!vis[Arre[v].x])&&(w[u][Arre[v].x]>0)){
				vis[Arre[v].x]=true;Pre[Arre[v].x]=u;Arr.push(Arre[v].x);
				if(Arre[v].x==t)return true;
			}
			v=Arre[v].next;
		}
	}
	return false;
}
void EdmondsKarp(){
	while(BFS()){
		int flow=none;
		int p=t; while(p!=s){flow=std::min(w[Pre[p]][p],flow); p=Pre[p];}
		p=t; while(p!=s){w[Pre[p]][p]-=flow;w[p][Pre[p]]+=flow;p=Pre[p];}
		ans+=flow;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i=1;i<=m;i++){scanf("%d%d",&u,&v);ins(u,v+n); ins(v+n,u); w[u][v+n]=1;}
	s=(n<<1)+1,t=(n<<1)+2;
	for(int i=1;i<=n;i++){ins(s,i);ins(i,s);w[s][i]=1;}
	for(int i=n+1;i<=n<<1;i++){ins(i,t);ins(t,i);w[i][t]=1;}
	EdmondsKarp();
	printf("%d",n-ans);
}