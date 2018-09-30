#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,top,ans;
struct Rec{
	int x,next;
}Arre[4100000];
int Arrmap[110000];
inline void ins(int f,int s){
	top++; Arre[top].x=s; Arre[top].next=Arrmap[f]; Arrmap[f]=top;
}
int Fa[110000];
int S[110000];//记录连通块的大小
int Getfa(int u){//路径压缩
	if(!Fa[u]){Fa[u]=u;return u;}
	int v=u;
	for(;Fa[u]!=u;u=Fa[u]);
	for(int o=Fa[v];Fa[v]!=u;Fa[v]=u,v=o,o=Fa[v]);
	return u;
}
int Arr[110000];
int h,t;
int tag[110000];
int tim;
void BFS(int x){//广搜。每删去一个点，就说明当前连通块大小+1。这两个同时更新即可。
	t++; Arr[t]=x; Fa[x]=Getfa(x+1); S[ans]++; int v;//此时删去x
	for(;h!=t;){
		h++; tim++; tag[Arr[h]]=tim;
		for(v=Arrmap[Arr[h]];v;v=Arre[v].next){
			if(tag[Arre[v].x]!=tim)tag[Arre[v].x]=tim;
		}
		for(v=Getfa(0);v<=n;v=Getfa(v)){
			if(tag[v]!=tim){t++; Arr[t]=v; Fa[v]=Getfa(v+1); S[ans]++;}else v++;//每一个在连通块里面的点都要删去
		}
	}
}
int main(){
	int i,u,v;
	read(n); read(m);
	for(i=1;i<=m;i++){
		read(u); read(v); ins(u,v); ins(v,u);//插入边
	}
	Fa[0]=1; Fa[1]=1;
	for(u=Getfa(0);u<=n;u=Getfa(0)){
		ans++; BFS(u);//搜索
	}
	std::sort(S+1,S+ans+1);//排序
	printf("%d\n",ans);
	for(i=1;i<=ans;i++){printf("%d",S[i]);if(i!=ans)printf(" ");}//输出
}