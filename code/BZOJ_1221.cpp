/*
具体思路：
如果没有洗毛巾这一说：
我们直接从s到第一个月连一条<none/f>的边（<容量/费用>）。每个月向下一个月连一条<none/0>的边。每个月向t连一条<N[i]/0>的边。
现在有了洗毛巾：于是对于每一个月i，我们先建立一个虚点i'，s向i'连一条<N[i]/0>的边。
接下来虚点i'会向i+a+1连一条<none/fa>的边，向i+b+1连一条<none/fb>的边。这样限制了毛巾数量，同时加入的方案。
*/
#include<cstdio>
#include<queue>
#include<algorithm>
const int none=1e8;
struct Rec{
	int x,next;
};
int n,a,b,f,fa,fb,top,tot,s,t,money,tim;
int A[1200],vol[2200][2200],cost[2200][2200];
int Arrmap[2200];
Rec Arre[22000];
int Dist[2200],Pre[2200],flag[2200];
inline void ins(int f,int s,int w,int c){
	top++; Arre[top].x=s; Arre[top].next=Arrmap[f]; Arrmap[f]=top;
	vol[f][s]=w; cost[f][s]=c;
}
inline bool Relax(int u,int v,int w){
	if(Dist[u]+w<Dist[v]){Dist[v]=Dist[u]+w;Pre[v]=u;return true;}
	return false;
}
bool Spfa(){
	for(int vi=1;vi<=tot;vi++)Dist[vi]=none,Pre[vi]=0;tim++;
	Dist[s]=0; std::queue<int> Arr; Arr.push(s); flag[s]=tim;
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
void EK(){
	while(Spfa()){
		int flow=none,p=t;
		while(Pre[p]){flow=std::min(flow,vol[Pre[p]][p]);p=Pre[p];}
		p=t;
		while(Pre[p]){vol[Pre[p]][p]-=flow;vol[p][Pre[p]]+=flow;p=Pre[p];}
		money+=flow*Dist[t];
	}
}
int main(){
	scanf("%d%d%d%d%d%d",&n,&a,&b,&f,&fa,&fb);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	tot=n; s=++tot; t=++tot; 
	ins(s,1,none,f); ins(1,s,0,-f); ins(1,t,A[1],0); ins(t,1,0,0);
	for(int i=2;i<=n;i++){
		ins(i-1,i,none,0); ins(i,i-1,0,0); ins(i,t,A[i],0); ins(t,i,0,0);
	}
	for(int i=1;i<=n;i++){
		tot++;
		ins(s,tot,A[i],0); ins(tot,s,0,0);
		if(i+a+1<=n){ins(tot,i+a+1,none,fa);ins(i+a+1,tot,0,-fa);}
		if(i+b+1<=n){ins(tot,i+b+1,none,fb);ins(i+b+1,tot,0,-fb);}
		if((i+a+1>n)&&(i+b+1>n))break;//边界情况注意
	}
	EK();
	printf("%d\n",money);
}