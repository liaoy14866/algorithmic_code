#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int none=2147483647;
int n,m,S;
struct rec {
	int u,w;
};
vector<rec> Arre[10010];
int Dist[10010];
bool flag[10010];
struct inf {
	int x,dist;
	bool operator <(const inf &a)const {
		return dist>a.dist;
	}
};
priority_queue<inf> A;
void Dijkstral(int x) {
	int vi,pos;
	for(vi=1; vi<=n; vi++)Dist[vi]=none;
	Dist[x]=0;
	A.push((inf) {
		x,0
	});
	for(;;) {
		while(flag[A.top().x]&&A.size())A.pop();
		if(!A.size())break;
		pos=A.top().x;
		flag[pos]=1;
		for(vi=0; vi<Arre[pos].size(); vi++)
			if(Dist[Arre[pos][vi].u]>Dist[pos]+Arre[pos][vi].w) {
				Dist[Arre[pos][vi].u]=Dist[pos]+Arre[pos][vi].w;
				A.push((inf) {
					Arre[pos][vi].u,Dist[Arre[pos][vi].u]
				});
			}
	}
}
int main() {
	int i,u,v,w;
	scanf("%d%d%d",&n,&m,&S);
	for(i=1; i<=m; i++) {
		scanf("%d%d%d",&u,&v,&w);
		Arre[u].push_back((rec) {
			v,w
		});
	}
	Dijkstral(S);
	for(i=1; i<=n; i++)printf("%d%c",Dist[i],i!=n?' ':'\n');
}
