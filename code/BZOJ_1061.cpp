#include<cstdio>
#include<algorithm>
#include<queue>

const int none=1e8;
struct Rec{
	int fr,to,vol,cost,next;//需要储存从哪里来与到哪里去
};
int n,m,top,tot,s,t,money,tim;
int A[2200],T[2200];
int Arrmap[2200];
Rec Arre[220000];
int Dist[2200],Pre[2200],flag[2200];

inline void ins(int f,int s,int w,int c){//插入一条边
	top++; Arre[top].fr=f; Arre[top].to=s; Arre[top].vol=w; Arre[top].cost=c;
	Arre[top].next=Arrmap[f]; Arrmap[f]=top;
}

inline bool Relax(int u,int v,int p){
	if(Dist[u]+Arre[p].cost<Dist[v]){Dist[v]=Dist[u]+Arre[p].cost;Pre[v]=p;return true;}
	return false;
}
bool Spfa(){
	for(int vi=1;vi<=tot;vi++)Dist[vi]=none,Pre[vi]=0; Dist[s]=0; tim++;
	std::queue<int> Arr; Arr.push(s); flag[s]=tim;
	while(!Arr.empty()){
		int u=Arr.front(),v=Arrmap[u]; Arr.pop(); flag[u]--;
		while(v){
			if(Arre[v].vol>0)
			if(Relax(u,Arre[v].to,v))
			if(flag[Arre[v].to]!=tim){
				Arr.push(Arre[v].to); flag[Arre[v].to]=tim;
			}
			v=Arre[v].next;
		}
	}
	return Dist[t]!=none;
}
void EK(){//费用流
	while(Spfa()){
		int flow=none,p=t;
		while(Pre[p]){flow=std::min(flow,Arre[Pre[p]].vol);p=Arre[Pre[p]].fr;}
		p=t;
		while(Pre[p]){Arre[Pre[p]].vol-=flow;Arre[Pre[p]^1].vol+=flow;p=Arre[Pre[p]].fr;}
		money+=flow*Dist[t];
	}
}

int main(){
	scanf("%d%d",&n,&m);//读入
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1;i<=n+1;i++)T[i]=A[i]-A[i-1];//差分
	tot=n+1; s=++tot; t=++tot; top=1;
	if(T[1]>=0){ins(s,1,T[1],0); ins(1,s,0,0);}//建边
	else{ins(1,t,-T[1],0); ins(t,1,0,0);}
	for(int i=2;i<=n+1;i++){
		if(T[i]>=0){ins(s,i,T[i],0); ins(i,s,0,0);}
		else{ins(i,t,-T[i],0); ins(t,i,0,0);}
		ins(i,i-1,none,0); ins(i-1,i,0,0);
	}
	for(int i=1;i<=m;i++){
		int l,r,w; scanf("%d%d%d",&l,&r,&w);
		ins(l,r+1,none,w); ins(r+1,l,0,-w);
	}
	EK();//费用流
	printf("%d\n",money);//输出答案
}