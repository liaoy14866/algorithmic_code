#include<cstdio>
#include<queue>
#include<algorithm>

const int none=1e8;
const int dx[5]={0,0,1,-1,0};
const int dy[5]={1,-1,0,0,0};//开始这里忘记向自己连边，调试了好久，样例死活过不去

struct Rec{
	int x,w,next;
};
int n,m,tot,s,t,top,ans,tim;
int Num[110][110];
int Arrmap[41000],Depth[41000],vis[41000];
Rec Arre[410000];

inline void ins(int f,int s,int w){//插入一条边
	top++; Arre[top].x=s; Arre[top].w=w; Arre[top].next=Arrmap[f]; 
	Arrmap[f]=top;
}
bool BFS(){
	std::queue<int> Arr; tim++; Arr.push(s); vis[s]=tim;
	while(!Arr.empty()){
		int u=Arr.front(),v=Arrmap[u]; Arr.pop();
		while(v){
			if((Arre[v].w>0)&&(vis[Arre[v].x]!=tim)){
				Depth[Arre[v].x]=Depth[u]+1;
				vis[Arre[v].x]=tim;
				Arr.push(Arre[v].x);
			}
			v=Arre[v].next;
		}
	}
	return vis[t]==tim;
}
int DFS(int x,int flow){
	if(x==t)return flow;
	int tmp,sum=0,v=Arrmap[x];
	while(v){
		if((Arre[v].w>0)&&(Depth[x]+1==Depth[Arre[v].x])){
			tmp=DFS(Arre[v].x,std::min(Arre[v].w,flow));
			sum+=tmp; flow-=tmp; Arre[v].w-=tmp; Arre[v^1].w+=tmp;
			if(!flow)break;
		}
		v=Arre[v].next;
	}
	if(!sum)Depth[x]=-1;
	return sum;
}
void Dinic(){//最小割
	while(BFS())
	ans-=DFS(s,none);
}

int main(){
	scanf("%d%d",&n,&m);//读入
	s=1; t=2; tot=2; top=1;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	Num[i][j]=++tot;//定义点的位置
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){//先把一个人选择文科与理科的边连上
		int w;scanf("%d",&w); ans+=w;
		ins(s,Num[i][j],w); ins(Num[i][j],s,0);
	}
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		int w;scanf("%d",&w); ans+=w;
		ins(Num[i][j],t,w); ins(t,Num[i][j],0);
	}
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){//之后考虑same的影响
		int w;scanf("%d",&w); ans+=w;
		tot++;
		ins(s,tot,w); ins(tot,s,0);
		for(int k=0;k<5;k++){
			int vx=i+dx[k],vy=j+dy[k];
			if((vx<1)||(vx>n)||(vy<1)||(vy>m))continue;
			ins(tot,Num[vx][vy],none); ins(Num[vx][vy],tot,0);
		}
	}
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		int w;scanf("%d",&w); ans+=w;
		tot++;
		ins(tot,t,w); ins(t,tot,0);
		for(int k=0;k<5;k++){
			int vx=i+dx[k],vy=j+dy[k];
			if((vx<1)||(vx>n)||(vy<1)||(vy>m))continue;
			ins(Num[vx][vy],tot,none); ins(tot,Num[vx][vy],0);
		}
	}
	
	Dinic();//跑最小割
	
	printf("%d\n",ans);//输出
}