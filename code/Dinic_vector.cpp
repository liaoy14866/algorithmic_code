#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int none=1e9+7;
char ch;
void read(int &x){
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
	for(x=0;ch>='0'&&ch<='9';ch=getchar())x=((x+(x<<2))<<1)+(ch^'0');
}
struct rec{
	int x,vol,ne;
}tmp,form;
int n,m,s,t,top,ans;
int Arrmap[60010];
vector<rec> Arre;
void ins(int f,int s,int vol){
	top++; tmp.x=s; tmp.vol=vol; tmp.ne=Arrmap[f]; Arrmap[f]=top; Arre.push_back(tmp);
}
void addedge(int f,int s,int vol){
	ins(f,s,vol); ins(s,f,0);
}
int Arr[60010],Depth[60010],flag[60010];
int tim,hi,ti,v;
bool BFS(){
	hi=0; ti=1; Arr[1]=s; Depth[s]=1; tim++; flag[s]=tim;
	while(hi!=ti){
		hi++;
		for(v=Arrmap[Arr[hi]];v;v=Arre[v].ne)
		if(Arre[v].vol>0&&flag[Arre[v].x]!=tim){
			ti++; Arr[ti]=Arre[v].x; Depth[Arr[ti]]=Depth[Arr[hi]]+1; flag[Arr[ti]]=tim;
		}
	}
	return flag[t]==tim;
}
int DFS(int x,int flow){
	if(x==t)return flow; int v,tmp,sum=0;
	for(v=Arrmap[x];v;v=Arre[v].ne)
	if(Arre[v].vol>0&&Depth[Arre[v].x]==Depth[x]+1&&flag[Arre[v].x]==tim){
		tmp=DFS(Arre[v].x,min(Arre[v].vol,flow));
		sum+=tmp; flow-=tmp; Arre[v].vol-=tmp; Arre[v^1].vol+=tmp;
		if(!flow)break;
	}
	if(!sum)Depth[x]=-1;
	return sum;
}
void Dinic(){
	while(BFS())ans-=DFS(s,none);
}
int main(){
	int i,u,v,w;
	read(n); read(m);
	s=n+m+1; t=n+m+2; top=1; Arre.push_back(form); Arre.push_back(form);
	for(i=1;i<=n;i++){
		read(w); addedge(i,t,w);
	}
	for(i=1;i<=m;i++){
		read(u); read(v); read(w); ans+=w;
		addedge(s,i+n,w); addedge(i+n,u,none); addedge(i+n,v,none);
	}
	Dinic();
	printf("%d\n",ans);
}