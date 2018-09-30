#include<cstdio>
#include<algorithm>
#include<stack>

const int none=1e7;
struct Rec{
	int x,w,next;
};
struct inf{
	int x,d,step;
};
int n,k,top,time,nowf,pos,tot,ans;
Rec Arre[410000];
int Arrmap[210000],vis[210000],size[210000],Dist[210000];
bool cut[210000];
int Bucket[1200000];
inf pipe[210000];

inline void ins(int f,int s,int w){//插入一条边
	top++; Arre[top].x=s; Arre[top].w=w; Arre[top].next=Arrmap[f]; Arrmap[f]=top;
}
void focusDFS(int x,int A){
	size[x]=1; vis[x]=time; int v=Arrmap[x],f=0;
	while(v){
		if((vis[Arre[v].x]!=time)&&(!cut[Arre[v].x])){
			focusDFS(Arre[v].x,A);
			size[x]+=size[Arre[v].x];
			f=std::max(f,size[Arre[v].x]);
		}
		v=Arre[v].next;
	}
	f=std::max(f,A-size[x]);
	if(f<nowf){pos=x;nowf=f;}
}
void distDFS(int x,int d,int step){
	if(d>k)return;
	Dist[x]=d; vis[x]=time; tot++; pipe[tot].x=x; pipe[tot].d=d; pipe[tot].step=step;
	int v=Arrmap[x];
	while(v){
		if((vis[Arre[v].x]!=time)&&(!cut[Arre[v].x]))distDFS(Arre[v].x,d+Arre[v].w,step+1);
		v=Arre[v].next;
	}
}
void Div(int root,int area){//点分治
	if(area==1)return;
	time++; nowf=none; focusDFS(root,area);//找出重心
	cut[pos]=true;//切断重心
	int v=Arrmap[pos],last=0; tot=0;
	while(v){
		if(!cut[Arre[v].x]){
			time++; distDFS(Arre[v].x,Arre[v].w,1);//处理出dist
			for(int vi=last+1;vi<=tot;vi++)
			ans=std::min(ans,pipe[vi].step+Bucket[k-pipe[vi].d]);//更新答案
			for(int vi=last+1;vi<=tot;vi++)
			Bucket[pipe[vi].d]=std::min(Bucket[pipe[vi].d],pipe[vi].step);//更新Bucket
			last=tot;
		}
		v=Arre[v].next;
	}
	ans=std::min(ans,Bucket[k]);//注意在这里还要更新ans，可能重心到其他子树的某个点也可能成为答案
	for(int vi=1;vi<=tot;vi++)Bucket[pipe[vi].d]=none;//还原Bucket数组
	v=Arrmap[pos];
	while(v){
		if(!cut[Arre[v].x])Div(Arre[v].x,size[Arre[v].x]);
		v=Arre[v].next;//分治下去
	}
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n-1;i++){
		int u,v,w; scanf("%d%d%d",&u,&v,&w); u++; v++;//读入，对数据做了一点处理
		ins(u,v,w); ins(v,u,w);
	}
	for(int i=0;i<=k+1;i++)Bucket[i]=none;//初始化Bucket数组
	ans=none;
	Div(1,n);//分治
	if(ans==none)printf("-1");else printf("%d\n",ans);//输出
}