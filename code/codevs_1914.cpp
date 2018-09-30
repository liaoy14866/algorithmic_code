#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>

const int none=1e9;
struct Rec{
	int x,next;
};
int w[2300][2300],c[2300][2300],Tw[2300][2300],Tc[2300][2300];
int Arrmap[2300],Pre[2300],Dist[2300];
Rec Arre[120000];
bool flag[2300];
int n,m,s,t,top,cost;

inline void ins(int f,int s){top++; Arre[top].x=s; Arre[top].next=Arrmap[f]; Arrmap[f]=top;}//插入

bool Relax(int x,int y,int w){//松弛
	if(Dist[x]+w<Dist[y]){Dist[y]=Dist[x]+w;Pre[y]=x;return true;}
	else return false;
}
bool Spfa(){//费用最短路
	memset(flag,false,sizeof(flag)); std::queue<int> Arr;memset(Pre,0,sizeof(Pre));
	for(int vi=1;vi<=n+m+2;vi++)Dist[vi]=none;
	flag[s]=true; Arr.push(s); Dist[s]=0;
	while(!Arr.empty()){
		int u=Arr.front(),v=Arrmap[u]; Arr.pop(); flag[u]=false;
		while(v!=0){
			if(w[u][Arre[v].x]>0)
			if(Relax(u,Arre[v].x,c[u][Arre[v].x]))
			if(!flag[Arre[v].x]){Arr.push(Arre[v].x); flag[Arre[v].x]=true;}
			v=Arre[v].next;
		}
	}
	if(Dist[t]==none)return false;else return true;
}
void EdmondsKarp(){//EK拓展
	while(Spfa()){
		int p=t,flow=none;
		while(p!=s){flow=std::min(w[Pre[p]][p],flow);p=Pre[p];}
		p=t;
		while(p!=s){w[Pre[p]][p]-=flow;w[p][Pre[p]]+=flow;p=Pre[p];}
		cost+=Dist[t]*flow;//最后把cost加上Dist[t]*flow就可以了
		continue;
	}
}

int main(){
	scanf("%d%d",&m,&n);//读入
	s=n+m+1;t=n+m+2;//建图
	for(int i=1;i<=m;i++){int u;scanf("%d",&u); ins(s,i); ins(i,s); w[s][i]=u;}
	for(int i=1;i<=n;i++){int u;scanf("%d",&u); ins(i+m,t); ins(t,i+m); w[i+m][t]=u;}
	for(int i=1;i<=m;i++)
	for(int j=1;j<=n;j++){
		int u;scanf("%d",&u); ins(i,j+m); ins(j+m,i);
		w[i][j+m]=none; c[i][j+m]=u; c[j+m][i]=-u;
	}
	for(int i=1;i<=n+m+3;i++)
	for(int j=1;j<=n+m+3;j++){Tw[i][j]=w[i][j];Tc[i][j]=c[i][j];}
	cost=0; EdmondsKarp();//计算最小费用
	printf("%d\n",cost);
	for(int i=1;i<=n+m+3;i++)
	for(int j=1;j<=n+m+3;j++){w[i][j]=Tw[i][j];c[i][j]=-Tc[i][j];}//费用反向
	cost=0; EdmondsKarp();//计算最大费用
	printf("%d\n",-cost);
}