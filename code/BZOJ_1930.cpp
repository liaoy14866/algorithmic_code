#include<cstdio>
#include<algorithm>
#include<vector>
char c;
void read(int &a){
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(a=0;c>='0'&&c<='9';c=getchar())(a*=10)+=c-'0';
}
const int none=1e8;
int n,s,os,t,top,money;
struct point{
	int x,y;
	bool operator <(const point &qa)const{
		return x!=qa.x?x<qa.x:y<qa.y;
	}
}P[4100];
struct rec{
	int fr,to,ne,vol,cost;
}tmp;
std::vector<rec>Arre;//动态储存边
int Arrmap[4100];
void ins(int f,int s,int vol,int cost){
	top++;
	tmp.fr=f; tmp.to=s; tmp.ne=Arrmap[f]; Arrmap[f]=top;
	tmp.vol=vol; tmp.cost=cost; Arre.push_back(tmp);
}
void addedge(int f,int s,int vol,int cost){
	ins(f,s,vol,cost); ins(s,f,0,-cost);
}
bool put(const point &a,const point &b){
	return (a.x<b.x&&a.y<b.y);
}
int Dist[4100],Pre[4100],flag[4100];
int tim;
bool Relax(int u,int v,int p){
	if(Dist[u]+Arre[p].cost>Dist[v]){
		Dist[v]=Dist[u]+Arre[p].cost; Pre[v]=p; return 1;
	}return 0;
}
int Arr[6200]; int hi,ti;
bool Spfa(){
	int vi,u;
	for(vi=1;vi<=t;vi++)Dist[vi]=-none,Pre[vi]=0; Dist[s]=0; tim++;
	hi=0; ti=1; Arr[1]=s; flag[s]=tim;
	while(hi!=ti){
		hi++; if(hi>6100)hi=1; flag[Arr[hi]]=tim-1;
		for(u=Arrmap[Arr[hi]];u;u=Arre[u].ne){
			if(Arre[u].vol>0)
			if(Relax(Arr[hi],Arre[u].to,u))
			if(flag[Arre[u].to]!=tim){
				ti++; if(ti>6100)ti=1;
				Arr[ti]=Arre[u].to; flag[Arr[ti]]=tim;
			}
		}
	}
	return Dist[t]!=-1;
}
void EK(){
	int flow=none,p=t;
	while(Spfa()){
		for(p=t;Pre[p];p=Arre[Pre[p]].fr)flow=std::min(flow,Arre[Pre[p]].vol);
		for(p=t;Pre[p];p=Arre[Pre[p]].fr)Arre[Pre[p]].vol-=flow,Arre[Pre[p]^1].vol+=flow;
		money+=flow*Dist[t];
	}
}
int main(){
	int i,j,minn,maxn;
	read(n); maxn=0;
	for(i=1;i<=n;i++)read(P[i].x),read(P[i].y),maxn=std::max(maxn,P[i].y);
	std::sort(P+1,P+n+1);
	Arre.push_back(tmp); Arre.push_back(tmp); top=1;
	s=n<<1|1; os=(n+1)<<1; t=(n+1)<<1|1; addedge(s,os,2,0);
	for(i=1;i<=n;i++){
		addedge(i,i+n,1,1); addedge(i,i+n,1,0);
		addedge(os,i,1,0); addedge(i+n,t,1,0);
	}
	for(i=1;i<=n;i++){
		minn=maxn+1;
		for(j=i+1;j<=n;j++)if(P[j].y<minn&&P[i].y<=P[j].y){
			addedge(i+n,j,2,0); minn=std::min(minn,P[j].y);
		}
	}
	EK();//费用流
	printf("%d\n",money);//输出答案
}