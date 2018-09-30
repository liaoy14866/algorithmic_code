#include<cstdio>
#include<algorithm>
using namespace std;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
int n,a,b;
struct inf{
	int x,y;
	void get(){
		read(x); read(y);
	}
};
inf S[2]; int DIS;
inf P[510];
inf Hate[1100],Fine[1100];
int Arrmap[510*2];
struct rec{
	int x,ne;
}Arre[1100*2*4+510*2*510*2*8];
int top;
inline void ins(int f,int s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
int tmp[2];
inline int dis(const inf &u,const inf &v){
	tmp[0]=u.x-v.x; if(tmp[0]<0)tmp[0]=-tmp[0]; tmp[1]=u.y-v.y; if(tmp[1]<0)tmp[1]=-tmp[1]; return tmp[0]+tmp[1];
}
int tim;
int Nar[510*2],stk[510*2],vis[510*2],flag[510*2],dfn[510*2],low[510*2];
int stktop,cnt,ant;
void Tarjan(int x){
	low[x]=dfn[x]=++cnt; vis[x]=flag[x]=tim; stk[++stktop]=x; int v;
	for(v=Arrmap[x];v;v=Arre[v].ne)
	if(vis[Arre[v].x]!=tim){
		Tarjan(Arre[v].x); low[x]=min(low[x],low[Arre[v].x]);
	}else if(flag[Arre[v].x]==tim)low[x]=min(low[x],low[Arre[v].x]);
	if(low[x]==dfn[x]){
		ant++;
		while(stk[stktop]!=x){
			Nar[stk[stktop]]=ant; flag[stk[stktop]]=0; stk[stktop--]=0;
		}
		Nar[x]=ant; flag[x]=0; stk[stktop--]=0;
	}
}
bool check(int maxn){
	int vi,vj,now;
	for(vi=1;vi<=top;vi++)Arre[vi].x=Arre[vi].ne=0; for(vi=1;vi<=n;vi++)Arrmap[vi]=Arrmap[vi+n]=0; top=0;
	for(vi=1;vi<=n;vi++)
	for(vj=vi+1;vj<=n;vj++){
		now=top;
		if(dis(P[vi],S[0])+dis(P[vj],S[1])+DIS>maxn)ins(vi,vj),ins(vj+n,vi+n);
		if(dis(P[vi],S[0])+dis(P[vj],S[0])>maxn)ins(vi,vj+n),ins(vj,vi+n);
		if(dis(P[vi],S[1])+dis(P[vj],S[0])+DIS>maxn)ins(vi+n,vj+n),ins(vj,vi);
		if(dis(P[vi],S[1])+dis(P[vj],S[1])>maxn)ins(vi+n,vj),ins(vj+n,vi);
		if(top-now==8)return 0;
	}
	for(vi=1;vi<=a;vi++){
		ins(Hate[vi].x,Hate[vi].y+n); ins(Hate[vi].x+n,Hate[vi].y);
		ins(Hate[vi].y,Hate[vi].x+n); ins(Hate[vi].y+n,Hate[vi].x);
	}
	for(vi=1;vi<=b;vi++){
		ins(Fine[vi].x,Fine[vi].y); ins(Fine[vi].x+n,Fine[vi].y+n);
		ins(Fine[vi].y,Fine[vi].x); ins(Fine[vi].y+n,Fine[vi].x+n);
	}
	tim++;cnt=ant=0;
	for(vi=1;vi<=(n<<1);vi++)if(vis[vi]!=tim)Tarjan(vi);
	for(vi=1;vi<=n;vi++)if(Nar[vi]==Nar[vi+n])return 0;
	return 1;
}
int main(){
	int i;
	read(n); read(a); read(b); S[0].get(); S[1].get(); DIS=dis(S[0],S[1]);
	for(i=1;i<=n;i++)P[i].get();
	for(i=1;i<=a;i++)Hate[i].get();
	for(i=1;i<=b;i++)Fine[i].get();
	int tl=0,tr=1e7+7,mid;
	while(tl!=tr){
		mid=(tl+tr)>>1;
		if(check(mid))tr=mid;else tl=mid+1;
	}
	if(tr==1e7+7)printf("-1\n");else printf("%d\n",tr);
}