#include<cstdio>
#include<algorithm>
#include<stack>
#include<queue>
const int none=1e9;
struct Rec{
	int x,w,next;
};
int r,c,top,s,t,ans,time;
int Num[35][35];
int Fin[700],val[700],vis[700],Depth[700];
int Arrmap[2][700];
Rec Arre[2][490000];
inline void ins(int f,int s,int w,int ifdo){
	top++; Arre[ifdo][top].x=s; Arre[ifdo][top].w=w; Arre[ifdo][top].next=Arrmap[ifdo][f]; 
	Arrmap[ifdo][f]=top; if(!ifdo)Fin[s]++;
}
void Topu(){
	std::stack<int> stk;
	for(int i=1;i<=r*c;i++)if(!Fin[i])stk.push(i);
	while(!stk.empty()){
		int u=stk.top(),v=Arrmap[0][u]; stk.pop();
		while(v){
			ins(u,Arre[0][v].x,0,1);
			ins(Arre[0][v].x,u,Arre[0][v].w,1);
			Fin[Arre[0][v].x]--;
			if(!Fin[Arre[0][v].x])stk.push(Arre[0][v].x);
			v=Arre[0][v].next;
		}
	}
}
bool BFS(){
	std::queue<int> Arr; time++; Arr.push(s); vis[s]=time;
	while(!Arr.empty()){
		int u=Arr.front(),v=Arrmap[1][u]; Arr.pop();
		while(v){
			if((Arre[1][v].w>0)&&(vis[Arre[1][v].x]!=time)){
				Depth[Arre[1][v].x]=Depth[u]+1;
				vis[Arre[1][v].x]=time;
				Arr.push(Arre[1][v].x);
			}
			v=Arre[1][v].next;
		}
	}
	if(vis[t]!=time)return false;return true;
}
int DFS(int x,int flow){
	if(x==t)return flow;
	int tmp,sum=0,v=Arrmap[1][x];
	while(v){
		if((Arre[1][v].w>0)&&(Depth[x]+1==Depth[Arre[1][v].x])){
			tmp=DFS(Arre[1][v].x,std::min(flow,Arre[1][v].w));
			sum+=tmp; flow-=tmp; Arre[1][v].w-=tmp; Arre[1][v^1].w+=tmp;
			if(!flow)break;
		}
		v=Arre[1][v].next;
	}
	if(!sum)Depth[x]=-1;
	return sum;
}
void Dinic(){
	while(BFS())ans-=DFS(s,none);
}
int main(){
	freopen("pvz.in","r",stdin); freopen("pvz.out","w",stdout);
	scanf("%d%d",&r,&c);
	for(int i=1;i<=r;i++)
	for(int j=1;j<=c;j++){top++; Num[i][j]=top;}
	s=r*c+1; t=r*c+2; top=0;
	for(int i=1;i<=r;i++)
	for(int j=1;j<=c;j++){
		int u,x,y;scanf("%d%d",&val[Num[i][j]],&u);
		for(int k=1;k<=u;k++){
			scanf("%d%d",&x,&y); x++; y++;
			ins(Num[i][j],Num[x][y],none,0);
		}
		if(j!=c)ins(Num[i][j+1],Num[i][j],none,0);
	}
	top=1;
	Topu();
	for(int i=1;i<=r*c;i++){
		if(Fin[i])continue;
		if(val[i]>0){ins(s,i,val[i],1);ins(i,s,0,1);ans+=val[i];}
		else{ins(i,t,-val[i],1);ins(t,i,0,1);}
	}
	Dinic();
	printf("%d\n",ans);
}