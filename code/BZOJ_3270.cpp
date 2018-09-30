#include<cstdio>
#include<algorithm>
struct func{
	double A[410][410];
}D;
double x[410],y[410];
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
struct rec{
	int x,ne;
}Arre[400];
int top;
int Arrmap[25],Ou[25];
double P[25];
void ins(int f,int s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
int n,m,a,b;
int stk[2][30];
inline int ptc(int x,int y){
	return (x-1)*n+y;
}
int main(){
	int i,j,u,v,stktop[2];
	scanf("%d%d%d%d",&n,&m,&a,&b);
	for(i=1;i<=m;i++){
		scanf("%d%d",&u,&v); ins(u,v); ins(v,u); Ou[u]++; Ou[v]++;
	}
	for(i=1;i<=n;i++)scanf("%lf",&P[i]);
	/*F[x][y]转移到F[x][y],F[vx][y],F[x][vy],F[vx][vy],F[x][x]不做任何贡献*/
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++){
		if(i==j)continue;
		stktop[0]=stktop[1]=0;
		for(u=Arrmap[i];u;u=Arre[u].ne)stk[0][++stktop[0]]=Arre[u].x;
		for(u=Arrmap[j];u;u=Arre[u].ne)stk[1][++stktop[1]]=Arre[u].x;
		D.A[ptc(i,j)][ptc(i,j)]=-P[i]*P[j];
		for(u=1;u<=stktop[0];u++)D.A[ptc(i,j)][ptc(stk[0][u],j)]=-(1-P[i])*P[j]/Ou[i];
		for(u=1;u<=stktop[1];u++)D.A[ptc(i,j)][ptc(i,stk[1][u])]=-(1-P[j])*P[i]/Ou[j];
		for(u=1;u<=stktop[0];u++)
		for(v=1;v<=stktop[1];v++)
		D.A[ptc(i,j)][ptc(stk[0][u],stk[1][v])]=-(1-P[i])*(1-P[j])/(Ou[i]*Ou[j]);
	}
	for(i=1;i<=n*n;i++)D.A[i][i]+=1;
	for(i=1;i<=n*n;i++)
	for(j=i+1;j<=n*n;j++)std::swap(D.A[i][j],D.A[j][i]);
	y[ptc(a,b)]=1;
	Gauss(D,x,y,n*n);
	for(i=1;i<=n;i++){
//		if(x[ptc(i,i)]<0)x[ptc(i,i)]=0;
		printf("%.6lf ",x[ptc(i,i)]);
	}
}