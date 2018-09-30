#include<cstdio>
#include<cstring>
#include<vector>
char ch;
void read(int &a){
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
	for(a=0;ch>='0'&&ch<='9';ch=getchar())(a*=10)+=ch-'0';
}
const int none=1e9+7;
int n,m,s,t,money;
int a[5100],b[5100],c[5100];
/*
强盗：i
时间：i+n 
*/
struct rec{
	int fr,to,ne,vol,cost;
}tmp;
std::vector<rec> Arre;
int Arrmap[16000];
int top;
void ins(int f,int s,int vol,int cost){
	top++;
	tmp.fr=f; tmp.to=s; tmp.vol=vol; tmp.cost=cost;
	tmp.ne=Arrmap[f]; Arrmap[f]=top; Arre.push_back(tmp);
}
void addedge(int f,int s,int vol,int cost){
	ins(f,s,vol,cost); ins(s,f,0,-cost);
}
int Dist[16000],Pre[16000],flag[16000];
int tim;
bool Relax(int u,int v,int p){
	if(Dist[u]+Arre[p].cost>Dist[v]){
		Dist[v]=Dist[u]+Arre[p].cost; Pre[v]=p; return 1;
	}return 0;
}
int Arr[18000]; int  hi,ti;
bool Spfa(){
	int v;
	for(hi=1;hi<=t;hi++)Dist[hi]=-none,Pre[hi]=0; tim++; memset(Arr,0,sizeof(Arr));
	hi=0; ti=1; Arr[1]=s; flag[s]=tim; Dist[s]=0;
	while(hi!=ti){
		hi++; if(hi>17000)hi=1; flag[Arr[hi]]=0;
		for(v=Arrmap[Arr[hi]];v;v=Arre[v].ne){
			if(Arre[v].vol>0)
			if(Relax(Arr[hi],Arre[v].to,v))
			if(flag[Arre[v].to]!=tim){
				ti++; if(ti>17000)ti=1;
				Arr[ti]=Arre[v].to; flag[Arr[ti]]=tim;
			}
		}
	}
	return Dist[t]!=-none;
}
void EK(){
	int p,flow;
	while(Spfa()){
		flow=none;
		for(p=t;Pre[p];p=Arre[Pre[p]].fr)flow=std::min(flow,Arre[Pre[p]].vol);
		for(p=t;Pre[p];p=Arre[Pre[p]].fr)Arre[Pre[p]].vol-=flow,Arre[Pre[p]^1].vol+=flow;
		money+=flow*Dist[t];
	}
}
struct node{
	int l,m,r,s[2];/*线段树*/
}Seg[21000];
int tot;
int Segbuild(int l,int r){
	int p=++tot; Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1; if(l==r)return p;
	Seg[p].s[0]=Segbuild(l,Seg[p].m); Seg[p].s[1]=Segbuild(Seg[p].m+1,r);
	return p;
}
void connect(int p,int v,int l,int r){//连接线段树上的节点
	if(Seg[p].l==l&&Seg[p].r==r){
		addedge(v,p+n,1,c[v]); return;
	}
	if(r<=Seg[p].m)connect(Seg[p].s[0],v,l,r);
	else
	if(Seg[p].m+1<=l)connect(Seg[p].s[1],v,l,r);
	else
	connect(Seg[p].s[0],v,l,Seg[p].m),connect(Seg[p].s[1],v,Seg[p].m+1,r);
}
int main(){
	int i;
	read(n);
	for(i=1;i<=n;i++)read(a[i]),read(b[i]),read(c[i]),m=std::max(m,b[i]);
	Arre.push_back(tmp); Arre.push_back(tmp); top=1;
	Segbuild(1,m);
	s=n+tot+1; t=n+tot+2;
	for(i=1;i<=tot;i++)if(!(Seg[i].s[0])&&!(Seg[i].s[1]))addedge(i+n,t,1,0);//线段树内部连边
	else addedge(i+n,Seg[i].s[0]+n,none,0),addedge(i+n,Seg[i].s[1]+n,none,0);
	for(i=1;i<=n;i++){
		connect(1,i,a[i],b[i]-1);//连接线段树上的节点
		addedge(s,i,1,0);
	}
	EK();//费用流
	printf("%d\n",money);//输出
	return 0;
}