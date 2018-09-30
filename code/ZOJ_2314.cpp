#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>

const int none=1e8;
struct Rec{int fr,x,next;};
int T,n,m,x,y,top,maxflow,ans;
int w[220][220],minn[220][220],maxn[220][220];
int Arrmap[220],Deta[220],Depth[220];
bool flag[220];
Rec Arre[42000];

inline void ins(int f,int s){top++;Arre[top].fr=f;Arre[top].x=s;Arre[top].next=Arrmap[f];Arrmap[f]=top;}//插入
void Linit(){//初始化
	memset(Arrmap,0,sizeof(Arrmap)); memset(Arre,0,sizeof(Arre)); memset(Deta,0,sizeof(Deta));
	memset(Depth,0,sizeof(Depth)); memset(w,0,sizeof(w));
	top=0; maxflow=0; ans=0;
	scanf("%d%d",&n,&m); 
	x=n+1;y=n+2;
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v); scanf("%d%d",&minn[u][v],&maxn[u][v]);//读入
		ins(u,v); ins(v,u); w[u][v]=maxn[u][v]-minn[u][v]; Deta[u]+=minn[u][v]; Deta[v]-=minn[u][v];
	}
	for(int i=1;i<=n;i++)if(Deta[i]>0){ins(i,y);ins(y,i);w[i][y]=Deta[i];maxflow+=Deta[i];}
	else{ins(i,x);ins(x,i);w[x][i]=-Deta[i];}//建边
}

bool BFS(){
	memset(flag,false,sizeof(flag)); std::queue<int> Arr;
	Arr.push(x); flag[x]=true;
	while(!Arr.empty()){
		int u=Arr.front(),v=Arrmap[u]; Arr.pop();
		while(v!=0){
			if((!flag[Arre[v].x])&&(w[u][Arre[v].x])){
				Depth[Arre[v].x]=Depth[u]+1; flag[Arre[v].x]=true;
				Arr.push(Arre[v].x);
				if(Arre[v].x==y)return true;
			}
			v=Arre[v].next;
		}
	}
	return false;
}
int DFS(int p,int flow){
	if(p==y)return flow;
	int tmp,sum=0,v=Arrmap[p];
	while(v!=0){
		if((Depth[p]+1==Depth[Arre[v].x])&&(w[p][Arre[v].x])){
			tmp=DFS(Arre[v].x,std::min(flow,w[p][Arre[v].x]));
			sum+=tmp; flow-=tmp; w[p][Arre[v].x]-=tmp; w[Arre[v].x][p]+=tmp;
		}
		v=Arre[v].next; 
	}
	Depth[p]=-1; return sum;
}
void Dinic(){//网络流
	while(BFS())ans+=DFS(x,none);
}

int main(){
	scanf("%d",&T);//多组数据
	while(T!=0){
		T--;
		Linit();//初始化
		Dinic();//跑网络流
		if(ans!=maxflow)printf("NO\n");
		else{
			printf("YES\n");
			for(int i=1;i<=(m<<1);i+=2)
			printf("%d\n",maxn[Arre[i].fr][Arre[i].x]-w[Arre[i].fr][Arre[i].x]);//输出
		}
		if(T!=0)printf("\n");
	}
}