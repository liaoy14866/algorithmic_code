#include<cstdio>
#include<algorithm>
#include<queue>

const int none=1e8;
struct Rec{
	int x,next;
};
int n,m,S,s,t,top,tim,money;
int U[60],d[60];
int cost[60][60],vol[60][60],Arrmap[60],Pre[60],flag[60],Dist[60];
//cost是花费，vol是容量
Rec Arre[360];

inline void ins(int f,int s,int w,int c){//插入一条边
	top++; Arre[top].x=s; Arre[top].next=Arrmap[f]; vol[f][s]=w; cost[f][s]=c; Arrmap[f]=top;
}
inline bool Relax(int u,int v,int w){//注意更新前驱
	if(Dist[u]+w<Dist[v]){Dist[v]=Dist[u]+w;Pre[v]=u;return true;}
	return false;
}
bool Spfa(){//对花费跑最短路
	std::queue<int> Arr; tim++; Arr.push(s); flag[s]=tim;
	for(int i=1;i<=t;i++)Dist[i]=none; Dist[s]=0;
	while(!Arr.empty()){
		int u=Arr.front(),v=Arrmap[u]; Arr.pop(); flag[u]--;
		while(v){
			if(vol[u][Arre[v].x]>0)
			if(Relax(u,Arre[v].x,cost[u][Arre[v].x]))
			if(flag[Arre[v].x]!=tim){
				Arr.push(Arre[v].x); flag[Arre[v].x]=tim;
			}
			v=Arre[v].next;
		}
	}
	return Dist[t]!=none;
}
void EK(){//费用流
	while(Spfa()){
		int flow=none,p=t;
		while(Pre[p]){flow=std::min(flow,vol[Pre[p]][p]);p=Pre[p];}
		p=t;
		while(Pre[p]){vol[Pre[p]][p]-=flow;vol[p][Pre[p]]+=flow;p=Pre[p];}//扣除流
		money+=flow*Dist[t];//计算费用
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&S);
	for(int i=1;i<=n;i++)scanf("%d",&U[i]);
	for(int i=1;i<=n;i++)scanf("%d",&d[i]);
	s=n+1; t=n+2;
	for(int i=1;i<=n;i++){
		ins(s,i,none,d[i]); ins(i,t,U[i],0);
		ins(i,s,0,-d[i]); ins(t,i,0,0);
	}
	for(int i=1;i<=n-1;i++){
		ins(i,i+1,S,m); ins(i+1,i,0,-m);
	}
	EK();
	printf("%d\n",money);
}