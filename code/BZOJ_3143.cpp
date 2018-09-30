#include<cstdio>
#include<algorithm>
struct func{
	double A[510][510];
}D;
double P[510],y[510];
int n,m;
int Arrmap[510];
struct rec{
	int x,ne;
}Arre[501000];
struct link{
	int u,v;
	double p;
}Q[251000];
inline bool Acmp(const link &a,const link &b){
	return a.p>b.p;
}
int Out[510];
int top;
void ins(int f,int s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
void Gauss(func &M,double *x,double *y,const int &len){
	int vi,vj,vk;
	for(vk=0;vk<len;vk++){
		for(vi=vk+1;vi<len;vi++){
			M.A[vi][vk]/=M.A[vk][vk];
			for(vj=vk+1;vj<len;vj++)M.A[vi][vj]-=M.A[vi][vk]*M.A[vk][vj];
			y[vi]-=M.A[vi][vk]*y[vk];
		}
	}
	for(vi=len-1;vi>=0;vi--){
		x[vi]=y[vi];
		for(vj=vi+1;vj<len;vj++)x[vi]-=x[vj]*M.A[vi][vj];
		x[vi]/=M.A[vi][vi];
	}
}
double ans;
int main(){
	int i,v;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d%d",&Q[i].u,&Q[i].v); ins(Q[i].u,Q[i].v); ins(Q[i].v,Q[i].u);
		Out[Q[i].u]++; Out[Q[i].v]++;
	}
	for(i=1;i<=n-1;i++){
		//填在i-1里头 
		D.A[i-1][i-1]=-1;
		for(v=Arrmap[i];v;v=Arre[v].ne)if(Arre[v].x!=n)D.A[i-1][Arre[v].x-1]=(double)1/Out[Arre[v].x];
	}
	y[0]=-1;
	Gauss(D,P,y,n-1);
	P[n-1]=0;
	for(i=1;i<=m;i++)Q[i].p=P[Q[i].u-1]/Out[Q[i].u]+P[Q[i].v-1]/Out[Q[i].v];
	std::sort(Q+1,Q+m+1,Acmp);
	for(i=1;i<=m;i++)ans+=Q[i].p*i;
	printf("%.3lf\n",ans);
}