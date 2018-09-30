#include<cstdio>
#include<algorithm>
#include<cstdio>
using namespace std;
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int Fa[2][41000],Dist[2][41000];//Fa[0]是东西向，Fa[1]是南北向的
int n,m,k;
int Getfa(int ifdo,int x){//带权并查集
	if(!Fa[ifdo][x]){Fa[ifdo][x]=x;return x;}
	if(Fa[ifdo][x]==x)return x;
	int fu=Getfa(ifdo,Fa[ifdo][x]);
	Dist[ifdo][x]+=Dist[ifdo][Fa[ifdo][x]]; Fa[ifdo][x]=fu; return fu;
}
struct inf{
	bool ope;//如果ope是1，那么就是合并；如果ope是0，那么就是查询
	bool dir;
	int time,u,v,d;//如果是合并，d就是该方向（dir储存）上的距离；如果是查询，d就是查询的编号。time是时间
};
int top;
inf Q[51000];
inline bool Acmp(const inf &a,const inf &b){
	return (a.time==b.time?a.ope<b.ope:a.time<b.time);
}
int cnt;
int Ans[11000];
int main(){
	int i,fu,fv,dis[2];
	char c;
	bool fl;
	read(n); read(m);//读入
	for(i=1;i<=m;i++){
		Q[i].time=++top; read(Q[i].u); read(Q[i].v); read(Q[i].d); Q[i].ope=0;
		for(c=getchar();c!='E'&&c!='W'&&c!='S'&&c!='N';c=getchar());
		if(c=='E'||c=='W'){if(c=='W'){swap(Q[i].u,Q[i].v);}Q[i].dir=0;}
		else{if(c=='S'){swap(Q[i].u,Q[i].v);}Q[i].dir=1;}
		/*
		定义东（E）与北（N）为正方向。如果出现了西（W）或者南（S）就把点对(u,v)顺序交换
		*/
	}
	read(k);
	for(i=1;i<=k;i++){
		top++; read(Q[top].u); read(Q[top].v); read(Q[top].time); Q[top].d=i; Q[top].ope=1;
	}
	std::sort(Q+1,Q+top+1,Acmp);
	for(i=1;i<=top;i++){
		if(!Q[i].ope){
			fu=Getfa(Q[i].dir,Q[i].u); fv=Getfa(Q[i].dir,Q[i].v); if(fu!=fv){//合并
				Fa[Q[i].dir][fu]=fv; Dist[Q[i].dir][fu]=Q[i].d+Dist[Q[i].dir][Q[i].v]-Dist[Q[i].dir][Q[i].u];
			}
			fu=Getfa(Q[i].dir^1,Q[i].u); fv=Getfa(Q[i].dir^1,Q[i].v); if(fu!=fv){
				Fa[Q[i].dir^1][fu]=fv; Dist[Q[i].dir^1][fu]=0+Dist[Q[i].dir^1][Q[i].v]-Dist[Q[i].dir^1][Q[i].u];
			}
		}else{
			fl=true;//查询
			fu=Getfa(0,Q[i].u); fv=Getfa(0,Q[i].v); fl&=(fu==fv);
			dis[0]=Dist[0][Q[i].u]-Dist[0][Q[i].v]; if(dis[0]<0)dis[0]=-dis[0];
			fu=Getfa(1,Q[i].u); fv=Getfa(1,Q[i].v); fl&=(fu==fv);
			dis[1]=Dist[1][Q[i].u]-Dist[1][Q[i].v]; if(dis[1]<0)dis[1]=-dis[1];
			if(fl)Ans[Q[i].d]=dis[0]+dis[1];else Ans[Q[i].d]=-1;
		}
	}
	for(i=1;i<=k;i++)printf("%d\n",Ans[i]);//输出
}