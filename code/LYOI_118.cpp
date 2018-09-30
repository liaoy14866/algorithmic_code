#include<cstdio>
#include<algorithm>
#include<queue>
#include<stack>
const int none=1e8;
struct Rec{int x,w,next;};
struct inf{int x,next;};
int n,m,ans,s,t,top,now;
int A[60],B[60];
int Arrmap[5000],Depth[5000],flag[5000],First[5000];
Rec Arre[5000];
inf Belong[5000];
bool fApp[60];

void put(int f,int s){now++;Belong[now].x=s;Belong[now].next=First[f];First[f]=now;}
void ins(int f,int s,int w){
	top++;Arre[top].x=s;Arre[top].w=w;Arre[top].next=Arrmap[f];Arrmap[f]=top;
}
bool BFS(){
	top++; std::queue<int> Arr;Arr.push(s); flag[s]=top;
	while(!Arr.empty()){
		int u=Arr.front(),v=Arrmap[u]; Arr.pop();
		while(v!=0){
			if((Arre[v].w>0)&&(flag[Arre[v].x]!=top)){
				Arr.push(Arre[v].x); flag[Arre[v].x]=top; Depth[Arre[v].x]=Depth[u]+1;
			}
			v=Arre[v].next;
		}
	}
	if(flag[t]!=top)return false;else return true;
}
int DFS(int x,int flow){
	if(x==t)return flow;
	int tmp,sum=0,v=Arrmap[x];
	while(v!=0){
		if((Arre[v].w>0)&&(Depth[x]+1==Depth[Arre[v].x])){
			tmp=DFS(Arre[v].x,std::min(Arre[v].w,flow));
			sum+=tmp; flow-=tmp; Arre[v].w-=tmp; Arre[v+((v&1)<<1)-1].w+=tmp;
			if(flow==0)break;
		}
		v=Arre[v].next;
	}
	if(flow==0)Depth[x]=-1;
	return sum;
}
void Dinic(){
	while(BFS())
	ans-=DFS(s,none);
}
int main(){
	scanf("%d%d",&m,&n); s=n+m+1; t=n+m+2;
	
	for(int i=1;i<=m;i++){
		scanf("%d",&A[i]);
		ans+=A[i];
		ins(s,i,A[i]);
		ins(i,s,0);
		int a=0;
		while(1){
			char c; c=getchar();
			if(((c<'0')||(c>'9'))&&(a!=0)){
				put(i,a);ins(i,m+a,none);ins(m+a,i,0);a=0;if(c=='\n')break;
			}
			if((c>='0')&&(c<='9'))(a*=10)+=c-'0';
		}
	}
	
	for(int i=1;i<=n;i++){scanf("%d",&B[i]);ins(i+m,t,B[i]);ins(t,i+m,0);}
	top=0;
	Dinic();
	int tot=0;
	int Q[60];
	for(int i=1;i<=m;i++)if(flag[i]==top){tot++;Q[tot]=i;}
	for(int i=1;i<=tot;i++)printf("%d ",Q[i]);
	printf("\n");
	for(int i=1;i<=tot;i++){
		int u=First[Q[i]];
		while(u!=0){
			flag[Belong[u].x]=none;
			u=Belong[u].next;
		}
	}
	for(int i=1;i<=n;i++)if(flag[i]==none)printf("%d ",i);
	printf("\n");
	printf("%d\n",ans);
}