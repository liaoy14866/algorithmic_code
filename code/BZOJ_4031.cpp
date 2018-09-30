#include<cstdio>
#include<algorithm>
#include<map>
const int intp=1e9;
struct func{
	long long A[90][90];
}D;
const int dx[2]={0,-1};
const int dy[2]={-1,0};
char c[12][12];
std::map<int,int> ma;
int Ou[12];
int n,m,cnt;
inline int ptc(const int &x,const int &y){
	return (x-1)*m+y;
}
long long sum=1;
void LU(func &M,const int &len){
	int vi,vj,vk,tmp;
	for(vi=1;vi<=len;vi++)
	for(vj=1;vj<=len;vj++)(M.A[vi][vj]+=intp)%=intp;
	for(vk=1;vk<=len;vk++){
		if(!M.A[vk][vk]){
			for(vi=vk+1;vi<=len;vi++)if(M.A[vi][vk])break;
			for(vj=vk;vj<=len;vj++)std::swap(M.A[vi][vj],M.A[vk][vj]);
			(sum*=(intp-1))%=intp;
		}
		for(vi=vk+1;vi<=len;vi++){
			while(M.A[vi][vk]){
				tmp=M.A[vi][vk]/M.A[vk][vk];
				for(vj=vk;vj<=len;vj++)(((M.A[vi][vj]-=tmp*M.A[vk][vj])%=intp)+=intp)%=intp;
				if(!M.A[vi][vk])break;
				(sum*=(intp-1))%=intp;
				for(vj=vk;vj<=len;vj++)std::swap(M.A[vi][vj],M.A[vk][vj]);
			}
		}
		(sum*=M.A[vk][vk])%=intp;
	}
}
int  main(){
	int i,j,k,vx,vy;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%s",c[i]+1);
	for(i=1;i<=n;i++)
	for(j=1;j<=m;j++){
		if(c[i][j]=='*')continue;
		ma[ptc(i,j)]=++cnt;
		for(k=0;k<=1;k++){
			vx=i+dx[k]; vy=j+dy[k];
			if(vx>=1&&vy>=1&&c[vx][vy]!='*'){
				D.A[ma[ptc(i,j)]][ma[ptc(vx,vy)]]=-1; D.A[ma[ptc(vx,vy)]][ma[ptc(i,j)]]=-1;
				D.A[ma[ptc(i,j)]][ma[ptc(i,j)]]+=1;
				D.A[ma[ptc(vx,vy)]][ma[ptc(vx,vy)]]+=1;
			}
		}
	}
	int siz=ma.size();
	LU(D,siz-1);
	printf("%lld\n",sum);
}