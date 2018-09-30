#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

const int none=1e8;
struct Rec{int x,next;};
int n,m,k,top,s,t,p,cost;
int Num[70][70],Food[70][70];
int w[1600][1600],c[1600][1600];
int Arrmap[1600],Pre[1600],Dist[1600];
bool Flag[1600];
Rec Arre[360000];

inline void ins(int f,int s){top++;Arre[top].x=s;Arre[top].next=Arrmap[f];Arrmap[f]=top;}//插入一条边

inline bool Relax(int x,int y,int w){
	if(Dist[x]+w<Dist[y]){Dist[y]=Dist[x]+w;Pre[y]=x;return true;}
	else return false;
}
bool Spfa(){
	std::queue<int> Arr; memset(Flag,false,sizeof(Flag)); memset(Pre,0,sizeof(Pre));
	for(int vi=1;vi<=p;vi++)Dist[vi]=none;
	Dist[s]=0; Flag[s]=true; Arr.push(s);
	while(!Arr.empty()){
		int u=Arr.front(),v=Arrmap[u]; Arr.pop(); Flag[u]=false;
		while(v!=0){
			if(w[u][Arre[v].x]>0)
			if(Relax(u,Arre[v].x,c[u][Arre[v].x]))
			if(!Flag[Arre[v].x]){Arr.push(Arre[v].x); Flag[Arre[v].x]=true;}
			v=Arre[v].next;
		}
	}
	if(Dist[t]==none)return false;else return true;
}
void EK(){//费用流
	while(Spfa()){
		int p=t,flow=none;
		while(p!=s){flow=std::min(flow,w[Pre[p]][p]);p=Pre[p];}
		p=t;
		while(p!=s){w[Pre[p]][p]-=flow;w[p][Pre[p]]+=flow;p=Pre[p];}
		cost+=Dist[t]*flow;
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&k);//读入
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m+i-1;j++){scanf("%d",&Food[i][j]);top+=2; Num[i][j]=top;}//Num[i][j]是出点，Num[i][j]-1是入点
	
	s=top+2; t=s+1; top=0; p=t+1; ins(s,p); ins(p,s); w[s][p]=k;//构图
	for(int j=1;j<=m;j++){ins(p,Num[1][j]-1); ins(Num[1][j]-1,p); w[p][Num[1][j]-1]=1;}
	for(int j=1;j<=n+m-1;j++){ins(Num[n][j],t); ins(t,Num[n][j]);w[Num[n][j]][t]=1;}
	for(int i=1;i<=n-1;i++)//to the under
	for(int j=1;j<=m+i-1;j++){
		ins(Num[i][j],Num[i+1][j]-1); ins(Num[i+1][j]-1,Num[i][j]); w[Num[i][j]][Num[i+1][j]-1]=1; 
		ins(Num[i][j],Num[i+1][j+1]-1); ins(Num[i+1][j+1]-1,Num[i][j]); w[Num[i][j]][Num[i+1][j+1]-1]=1; 
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m+i-1;j++){
		w[Num[i][j]-1][Num[i][j]]=1; ins(Num[i][j]-1,Num[i][j]); ins(Num[i][j],Num[i][j]-1);
		c[Num[i][j]-1][Num[i][j]]=-Food[i][j]; c[Num[i][j]][Num[i][j]-1]=Food[i][j];
	}
	
	EK();//费用流
	
	printf("%d",-cost);//输出
}