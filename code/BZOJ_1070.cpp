#include<cstdio>
#include<queue>
#include<algorithm>

const int none=1e8;
struct Rec{
	int x,next;
};
int n,m,s,t,tot,top,tim,money;
int A[70][11];
int vol[700][700],cost[700][700];
int Arrmap[700];
Rec Arre[490000];
int Dist[700],flag[700],Pre[700];

inline void ins(int f,int s,int w,int c){
	top++; Arre[top].x=s; Arre[top].next=Arrmap[f]; Arrmap[f]=top;
	vol[f][s]=w; cost[f][s]=c;
}
inline bool Relax(int u,int v,int w){
	if(Dist[u]+w<Dist[v]){Dist[v]=Dist[u]+w;Pre[v]=u;return true;}
	return false;
}
bool Spfa(){
	for(int vi=1;vi<=tot;vi++)Dist[vi]=none,Pre[vi]=0; tim++;
	std::queue<int> Arr; Arr.push(s); flag[s]=tim; Dist[s]=0;
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
void EK(){//费用流算法
	while(Spfa()){
		int p=t,flow=none;
		while(Pre[p]){flow=std::min(flow,vol[Pre[p]][p]); p=Pre[p];}
		p=t;
		while(Pre[p]){vol[Pre[p]][p]-=flow;vol[p][Pre[p]]+=flow;p=Pre[p];}
		money+=Dist[t]*flow;
	}
}

int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)scanf("%d",&A[i][j]);//读入，A[i][j]表示i师傅修了j这辆车的时间花费
	s=n+1; t=n+2; tot=n+2;
	for(int i=1;i<=n;i++){
		ins(i,t,1,0); ins(t,i,0,0);//建边
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		tot++;
		ins(s,tot,1,0); ins(tot,s,0,0);
		for(int k=1;k<=n;k++){
			ins(tot,k,1,i*A[k][j]); ins(k,tot,0,-i*A[k][j]);
		}
	}
	
	EK();//费用流
	
	double ans=(double)money/(double)n;
	printf("%.2f\n",ans);//输出平均时间
}