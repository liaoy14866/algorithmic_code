#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int none=2147483647;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
struct rec{
	int x,w;
};
int n,m,S;
vector<rec> Arre[10010];
struct num{
	int x,dist;
	bool operator <(const num &a)const{
		return dist>a.dist;
	}
};
bool flag[500010];
int Dist[500010];
num A[500010]; int Atop;
void Dijkstral(int s){
	int vi,pos;
	Atop=1; A[1]=(num){s,0}; for(vi=1;vi<=n;vi++)Dist[vi]=none; Dist[s]=0;
	for(;;){
		while(flag[A[1].x]&&Atop){
			pop_heap(A+1,A+Atop+1); Atop--;
		}
		if(!Atop)break;
		pos=A[1].x; flag[pos]=1;
		for(vi=0;vi<Arre[pos].size();vi++)
		if(Dist[Arre[pos][vi].x]>Dist[pos]+Arre[pos][vi].w){
			Dist[Arre[pos][vi].x]=Dist[pos]+Arre[pos][vi].w;
			Atop++; A[Atop]=(num){Arre[pos][vi].x,Dist[Arre[pos][vi].x]};
			push_heap(A+1,A+Atop+1);
		}
	}
}
int main(){
	int i,u,v,w;
	read(n); read(m); read(S);
	for(i=1;i<=m;i++){
		read(u); read(v); read(w); Arre[u].push_back((rec){v,w});
	}
	Dijkstral(S);
	for(i=1;i<=n;i++)printf("%d%c",Dist[i],i!=n?' ':'\n');
}