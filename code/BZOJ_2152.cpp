#include<cstdio>
#include<algorithm>
const int none=1e8;
struct Rec{
	int x,w,next;
};
int n,top,time,nowf,pos,ans,all;
int Arrmap[21000];
Rec Arre[42000];
int vis[21000],size[21000],dist[21000];
bool cut[21000];
int cnt[4];
int gcd(int a,int b){
	int c=a%b;
	while(c){a=b;b=c;c=a%b;}
	return b;
}
inline void ins(int f,int s,int w){
	top++; Arre[top].x=s; Arre[top].w=w; Arre[top].next=Arrmap[f]; Arrmap[f]=top;
}
void focusDFS(int x,int A){
	size[x]=1; vis[x]=time; int v=Arrmap[x],f=0;
	while(v){
		if((!cut[Arre[v].x])&&(vis[Arre[v].x]!=time)){
			focusDFS(Arre[v].x,A);
			size[x]+=size[Arre[v].x];
			f=std::max(f,size[Arre[v].x]);
		}
		v=Arre[v].next;
	}
	f=std::max(f,A-size[x]);
	if(f<nowf){nowf=f; pos=x;}
}
void distDFS(int x,int d){
	dist[x]=d; vis[x]=time; int v=Arrmap[x];
	while(v){
		if((!cut[Arre[v].x])&&(vis[Arre[v].x]!=time))distDFS(Arre[v].x,(d+Arre[v].w)%3);
		v=Arre[v].next;
	}
	cnt[dist[x]]++;
}
void subDFS(int x){
	vis[x]=time; int v=Arrmap[x];
	while(v){
		if((!cut[Arre[v].x])&&(vis[Arre[v].x]!=time))subDFS(Arre[v].x);
		v=Arre[v].next;
	}
	cnt[dist[x]]++;
}

void Div(int root,int area){//点分治
	if(area==1)return;
	time++; vis[root]=time; nowf=none; focusDFS(root,area);//先找到重心，记为pos
	cnt[0]=0; cnt[1]=0; cnt[2]=0;
	time++; vis[pos]=time; distDFS(pos,0);//计算出距离pos 的距离（mod 3意义下）
	ans+=(cnt[0]*(cnt[0]-1))+((cnt[1]*cnt[2])<<1);//计算贡献
	cut[pos]=true; int v=Arrmap[pos];
	while(v){
		cnt[0]=0; cnt[1]=0; cnt[2]=0;
		if(!cut[Arre[v].x]){time++;subDFS(Arre[v].x);}//除去同一棵子树内点对的贡献
		ans-=(cnt[0]*(cnt[0]-1))+((cnt[1]*cnt[2])<<1);
		v=Arre[v].next;
	}
	v=Arrmap[pos];
	while(v){
		if(!cut[Arre[v].x])Div(Arre[v].x,size[Arre[v].x]);//往下分治
		v=Arre[v].next;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){//初始化
		int u,v,w; scanf("%d%d%d",&u,&v,&w);
		ins(u,v,w); ins(v,u,w);
	}
	
	Div(1,n);//分治
	
	ans+=n;//处理答案
	all=n*n;
	int gys=gcd(ans,all);
	ans/=gys; all/=gys;//输出
	printf("%d/%d\n",ans,all);
}