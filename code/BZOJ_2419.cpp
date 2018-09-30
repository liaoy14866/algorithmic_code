#include<cstdio>
#include<cstring>
struct func{
	double A[110][110];
}D;
double x[110],y[110];
int n,m;
int Arrmap[110];
struct rec{
	int x,ne;
	double R;
}Arre[21000];
int top;
void ins(int f,int s,double R){
	top++; Arre[top].x=s; Arre[top].R=R; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
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
int main(){
	int i,u,v; double r;
	while(scanf("%d%d",&n,&m)!=EOF){
		memset(Arrmap,0,sizeof(Arrmap)); memset(Arre,0,sizeof(Arre));
		memset(x,0,sizeof(x)); memset(y,0,sizeof(y)); top=0; memset(D.A,0,sizeof(D.A));
		for(i=1;i<=m;i++){
			scanf("%d%d%lf",&u,&v,&r); if(u==v)continue;
			ins(u,v,r); ins(v,u,r);
		}
		D.A[n-1][n-1]=1;
		for(i=1;i<n;i++){
			//填在i-1这一行里头
			for(v=Arrmap[i];v;v=Arre[v].ne){
				D.A[i-1][Arre[v].x-1]+=1/Arre[v].R;
				D.A[i-1][i-1]-=1/Arre[v].R;
			}
		}
		y[0]=-1;
		Gauss(D,x,y,n);
		printf("%.2lf\n",x[0]);
	}
}