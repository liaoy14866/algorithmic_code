/*
题目大意：给出一张网格图，其中有一些关键点。每个格子都有海拔。现在整个网格图都被淹没了，需要建一些水泵，来抽水。
只需要保证让关键点不被淹没即可。
求最少多少个水泵。
解法：
1.不难证明，水泵是可以全部在关键城市上的。
2.把所有格子按照高度排序。对于当前关键城市，比当前关键城市海拔低的点都被记录下来，并且相连的都被放在了一个集合中。
如果当前关键城市所在的集合中没有一个是水泵，就说明比之海拔低且可以到达其的点都没有水泵，那么就在这里建一个水泵。
相反，那么这个集合内所有的点放一个水泵都是可行的。那么就不用建水泵。
注意：一次要同时处理所有海拔相同的点。
用一个Done数组记录已经处理过的点，来保证当前点x不会和高度高于当前点x的点y合并。
*/
#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar(); bool fl=true;
	for(a=0;c>'9'||c<'0';c=getchar())if(c=='-')fl=false;
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
	if(!fl)a=-a;
}
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
int n,m,last,ans;
int H[1200][1200];
inline int num(int x,int y){return (x-1)*m+y;}
int Fa[1200000],Size[1200000];
bool tag[1200000];//记录这个连通块是否已经有水泵了
/*并查集*/
int Getfa(int u){
	if(!Fa[u]){Fa[u]=u;Size[u]=1;return u;}
	int v=u; for(;u!=Fa[u];u=Fa[u]);
	for(int o=Fa[v];u!=Fa[v];Fa[v]=u,v=o,o=Fa[v]){Size[o]-=Size[v];}
	return u;
}
void Union(int u,int v){
	int fu=Getfa(u),fv=Getfa(v); if(fu==fv)return;
	if(Size[fu]>Size[fv])std::swap(fu,fv); Fa[fu]=fv; Size[fv]+=Size[fu]; tag[fv]|=tag[fu];
}
bool flag[1200][1200];
struct inf{
	int x,y;
};
inf Arr[1200000];
int top;
inline bool Acmp(const inf &a,const inf &b){
	return (H[a.x][a.y]==H[b.x][b.y])?flag[a.x][a.y]<flag[b.x][b.y]:H[a.x][a.y]<H[b.x][b.y];
}
bool Done[1200][1200];//Done记录有没有被操作过
int main(){
	int i,j,vx,vy,v,fu;
	read(n); read(m);
	for(i=1;i<=n;i++)
	for(j=1;j<=m;j++){//读入
		read(H[i][j]); if(H[i][j]>0)flag[i][j]=1;else H[i][j]=-H[i][j]; top++; Arr[top].x=i; Arr[top].y=j;
	}
	H[0][0]=-1;
	std::sort(Arr+1,Arr+top+1,Acmp);//处理
	for(i=1;i<=top;i++){
		for(v=0;v<=3;v++){//把相邻的连通
			vx=Arr[i].x+dx[v];vy=Arr[i].y+dy[v]; if(vx<1||vx>n||vy<1||vy>m)continue;
			if(Done[vx][vy])Union(num(Arr[i].x,Arr[i].y),num(vx,vy));
		}
		Done[Arr[i].x][Arr[i].y]=1;
		if(H[Arr[i].x][Arr[i].y]!=H[Arr[i+1].x][Arr[i+1].y]){//同时处理高度相同的一块
			for(j=last+1;j<=i;j++){
				if(flag[Arr[j].x][Arr[j].y]){
					fu=Getfa(num(Arr[j].x,Arr[j].y)); if(tag[fu])continue;
					tag[fu]=1; ans++;
				}
			}
			last=i;
		}
	}
	printf("%d\n",ans);//输出
}