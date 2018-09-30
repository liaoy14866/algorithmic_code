#include<cstdio>
#include<algorithm>
#include<cstring>

const int none=1e8;
struct Rec{
	int x,w,next;
};

int n,k,top,ans,time,pos,nowf,tot;//pos记录重心，nowf记录最大的f，f(x)=max{size[son],area-size[x]}
int Arrmap[10010],Dist[10010];
Rec Arre[20020];
int vis[10010];//vis记录是否出现过。time为时间戳。
bool cut[10010];//cut数组记录这个点有没有在点分治的过程中被切掉
int size[10010],pipe[10010];//size在每一次求重心的时候用于统计子树大小。pipe是把dist储存并排序的数组

inline void ins(int f,int s,int w){//插入一条边
	top++; Arre[top].x=s; Arre[top].next=Arrmap[f];Arre[top].w=w; Arrmap[f]=top;
}

bool Linit(){//初始化
	top=0; ans=0;  memset(Arrmap,0,sizeof(Arrmap)); memset(Arre,0,sizeof(Arre)); memset(cut,0,sizeof(cut));
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n-1;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);ins(u,v,w); ins(v,u,w);}//建一棵树
	return (n|k)>0;
}

void focusDFS(int x,int A){//寻找重心的DFS
	int v=Arrmap[x],f=0; size[x]=1; vis[x]=time;
	while(v){
		if((vis[Arre[v].x]!=time)&&(!cut[Arre[v].x])){
			focusDFS(Arre[v].x,A);
			size[x]+=size[Arre[v].x]; 
			f=std::max(f,size[Arre[v].x]);
		}
		v=Arre[v].next;
	}
	f=std::max(f,A-size[x]);
	if(f<nowf){pos=x; nowf=f;}
}

void distDFS(int x,int now){//处理出距离的DFS
	Dist[x]=now; vis[x]=time;
	int v=Arrmap[x];
	while(v){
		if((vis[Arre[v].x]!=time)&&(!cut[Arre[v].x]))distDFS(Arre[v].x,now+Arre[v].w);
		v=Arre[v].next;
	}
}

void putDFS(int x){//把子树里面的节点全部放到pipe里面的DFS
	int v=Arrmap[x]; vis[x]=time; tot++; pipe[tot]=Dist[x];
	while(v){
		if((vis[Arre[v].x]!=time)&&(!cut[Arre[v].x]))putDFS(Arre[v].x);
		v=Arre[v].next;
	}
}

int distCount(int p){//计算距离小于k的点对
	time++; vis[p]=time; tot=0; putDFS(p);
	std::sort(pipe+1,pipe+tot+1);//排序
	int tl,tr,mid,sum=0;
	for(int vi=2;vi<=tot;vi++){
		if(pipe[vi]+pipe[1]>k)break;//用的二分查找。两个指针也可以
		tl=1;tr=vi-1;
		while(tl!=tr){
			mid=((tl+tr)>>1)+1;
			if(pipe[mid]+pipe[vi]<=k)tl=mid;else tr=mid-1;
		}
		sum+=tl;
	}
	return sum;
}

void Div(int root,int area){//点分治。
	if(area==1)return;
	time++; nowf=none; vis[root]=time; focusDFS(root,area);//先找出重心，记为pos
	time++; vis[pos]=time; distDFS(pos,0);//处理出其他点到pos的距离
	ans+=distCount(pos); cut[pos]=true;//先处理出所有的距离小于k的点对
	int v=Arrmap[pos];
	while(v){//再减去在同一个子树内，到pos的距离之和仍然小于k的
		if(!cut[Arre[v].x])ans-=distCount(Arre[v].x);
		v=Arre[v].next;
	}
	v=Arrmap[pos];
	while(v){//向下分治
		if(!cut[Arre[v].x])Div(Arre[v].x,size[Arre[v].x]);
		v=Arre[v].next;
	}
}
int main(){
	for(;;){
		if(!Linit())return 0;//初始化
		Div(1,n);//分治
		printf("%d",ans);//输出
	}
}