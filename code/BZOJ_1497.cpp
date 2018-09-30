#include<cstdio>
#include<queue>

const int none=1e8;
struct Rec{
	int x,w,next;
};
int n,m,s,t,top,ans,time;
int Arrmap[62000],vis[62000],Depth[62000];
Rec Arre[1200000];

inline void ins(int f,int s,int w){//插入一条边
	top++; Arre[top].x=s; Arre[top].w=w; Arre[top].next=Arrmap[f]; Arrmap[f]=top;
}

bool BFS(){
	std::queue<int> Arr; time++;//用时间戳可以避免bool数组的memset
	Arr.push(s); vis[s]=time;
	while(!Arr.empty()){
		int u=Arr.front(),v=Arrmap[u]; Arr.pop();
		while(v){
			if((vis[Arre[v].x]!=time)&&(Arre[v].w>0)){
				Arr.push(Arre[v].x);
				vis[Arre[v].x]=time;
				Depth[Arre[v].x]=Depth[u]+1;
			}
			v=Arre[v].next;
		}
	}
	if(vis[t]!=time)return false;return true;//在最后判断，使得Dinic可以一次拓展多条路，加速算法
}

int DFS(int x,int flow){
	if(x==t)return flow;
	int v=Arrmap[x],tmp,sum=0;
	while(v){
		if((Arre[v].w>0)&&(Depth[x]+1==Depth[Arre[v].x])){
			tmp=DFS(Arre[v].x,std::min(Arre[v].w,flow));
			sum+=tmp; flow-=tmp; Arre[v].w-=tmp; Arre[v^1].w+=tmp;
			if(!flow)break;//如果没有流了，就可以弹出了
		}
		v=Arre[v].next;
	}
	if(!sum)Depth[x]=-1;//如果此处拓展不出增广路了，那么之后一定也拓展不出，将Depth置为-1
	return sum;
}

void Dinic(){//Dinic算法
	while(BFS())ans-=DFS(s,none);
}

int main(){
	scanf("%d%d",&n,&m);
	s=n+m+1; t=n+m+2; top=1;
	//top=1是为了这样可以使得奇数编号边的反向边为奇数编号-1的边，偶数编号边的反向边为偶数编号+1的边
	//由此可以用异或^得到反向边
	for(int i=1;i<=n;i++){//建图
		int u;scanf("%d",&u); ins(i,t,u); ins(t,i,0);
	}
	for(int i=1;i<=m;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w); 
		ins(s,i+n,w); ins(i+n,s,0); ans+=w;
		ins(u,i+n,0); ins(i+n,u,none); ins(v,i+n,0); ins(i+n,v,none);
	}
	Dinic();//网络流
	printf("%d\n",ans);//输出
}