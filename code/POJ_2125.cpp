#include<cstdio>
#include<queue>
#include<cstring>

struct Rec{
	int x,next;
};
const int none=1e8;
int n,m,top,ans,s,t,num;
int A[1300],B[1300];//+(A[i]) means incoming and -(B[i]) means outcoming
int w[2300][2300];
int Arrmap[2400],Depth[2400];
Rec Arre[12000];
bool vis[2300];
std::queue<int> Arr;

void ins(int f,int s){//插入一条边
	top++; Arre[top].x=s; Arre[top].next=Arrmap[f]; Arrmap[f]=top;
}
bool BFS(){//BFS
	while(!Arr.empty())Arr.pop(); memset(vis,false,sizeof(vis));
	Arr.push(s); vis[s]=true;
	while(!Arr.empty()){
		int u=Arr.front(),v=Arrmap[u]; Arr.pop();
		while(v!=0){
			if((!vis[Arre[v].x])&&(w[u][Arre[v].x]>0)){
				Depth[Arre[v].x]=Depth[u]+1;
				vis[Arre[v].x]=true;
				Arr.push(Arre[v].x);
				if(Arre[v].x==t)return true;
			}
			v=Arre[v].next;
		}
	}
	return false;
}
int DFS(int x,int flow){//DFS
	if(x==t)return flow;
	int tmp,sum=0,v=Arrmap[x];
	while(v!=0){
		if((Depth[x]+1==Depth[Arre[v].x])&&(w[x][Arre[v].x]>0)){
			tmp=DFS(Arre[v].x,std::min(flow,w[x][Arre[v].x]));
			sum+=tmp; flow-=tmp;
			w[x][Arre[v].x]-=tmp; w[Arre[v].x][x]+=tmp;
		}
		v=Arre[v].next;
	}
	return sum;
}
void Dinic(){//Dinic
	while(BFS()){ans+=DFS(s,none);}
}

void Find(int x){//在求解方案的时候的DFS
	int v=Arrmap[x];
	vis[x]=true;
	while(v!=0){
		if((!vis[Arre[v].x])&&(w[x][Arre[v].x]>0))Find(Arre[v].x);
		v=Arre[v].next;
	}
}

int main(){
	scanf("%d%d",&n,&m);//读入
	for(int i=1;i<=n;i++)scanf("%d",&A[i]); 
	for(int i=1;i<=n;i++)scanf("%d",&B[i]);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		ins(u,v+n);
		ins(v+n,u);
		w[u][v+n]=none;//左边的点与右边的点之间的边容量为正无穷
	}
	s=(n<<1)+1,t=(n<<1)+2;
	for(int i=1;i<=n;i++){ins(s,i);ins(i,s);w[s][i]=B[i];}//左边的点与s连边，容量为B[i]，即Wi-
	for(int i=n+1;i<=n<<1;i++){ins(i,t);ins(t,i);w[i][t]=A[i-n];}//右边的点与t连边，容量为A[i]，即Wi+
	
	Dinic();//网络流
	
	memset(vis,false,sizeof(vis));
	Find(s);//寻找方案
	
	printf("%d\n",ans);//输出
	for(int i=1;i<=n;i++)if(!vis[i])num++;//左边的点，如果没有便利到，就是我们要输出的点
	for(int i=n+1;i<=n<<1;i++)if(vis[i])num++;//右边的点，如果便利到了，就是我们要输出的点
	printf("%d\n",num);
	for(int i=1;i<=n;i++)if(!vis[i])printf("%d -\n",i);
	for(int i=n+1;i<=n<<1;i++)if(vis[i])printf("%d +\n",i-n);
}