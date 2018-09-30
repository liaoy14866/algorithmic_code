#include<cstdio>
#include<algorithm>
struct func{
	double A[310][310];
}D;
double x[310],y[310];
int n,m,top;
double P,Q;
struct rec{
	int u,v;
}E[45000];
int Ord[310];
void Gauss(func &M,double *x,double *y,const int &len){
	int vi,vj,vk;
	for(vk=1;vk<=len;vk++){
		for(vi=vk+1;vi<=len;vi++){
			M.A[vi][vk]/=M.A[vk][vk];
			for(vj=vk+1;vj<=len;vj++)M.A[vi][vj]-=M.A[vi][vk]*M.A[vk][vj];
			y[vi]-=M.A[vi][vk]*y[vk]; 
		}
	}
	for(vi=len;vi>=1;vi--){
		x[vi]=y[vi];
		for(vj=vi+1;vj<=len;vj++)x[vi]-=x[vj]*M.A[vi][vj];
		x[vi]/=M.A[vi][vi];
	}
}
int main(){
	int i,j;
	scanf("%d%d%lf%lf",&n,&m,&P,&Q);
	for(i=1;i<=m;i++){
		top++; scanf("%d%d",&E[top].u,&E[top].v); Ord[E[top].u]++; Ord[E[top].v]++;
	}
	for(i=1;i<=m;i++){
		D.A[E[i].u][E[i].v]=-(1-P/Q)/Ord[E[i].u]; D.A[E[i].v][E[i].u]=-(1-P/Q)/Ord[E[i].v];
	}
	/*E是下标1开始*/
	for(i=1;i<=n;i++)D.A[i][i]+=1;
	y[1]=P/Q;
	for(i=1;i<=n;i++)
	for(j=i+1;j<=n;j++)std::swap(D.A[i][j],D.A[j][i]);
	Gauss(D,x,y,n);
	for(i=1;i<=n;i++)printf("%.9lf\n",x[i]);
}