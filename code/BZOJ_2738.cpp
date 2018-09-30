#include<cstdio>
#include<algorithm>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
struct pos{
	int x,y,val;
}T[260000];
inline bool Acmp(const pos &a,const pos &b){
	return a.val==b.val?a.x<b.x:a.val<b.val;
}
int n,q,maxn;
struct que{
	int x[2],y[2],k,num,ans;
}Q[61000],tmp[61000];
int C[510][510];//二维树状数组
void Change(int x,int y,int w){
	int vi,vj;
	for(vi=x;vi<=n;vi+=vi&-vi)for(vj=y;vj<=n;vj+=vj&-vj)C[vi][vj]+=w;
}
int Getsum(int x,int y){
	int vi,vj,sum=0;
	for(vi=x;vi;vi-=vi&-vi)for(vj=y;vj;vj-=vj&-vj)sum+=C[vi][vj];
	return sum;
}
int Ans[61000];
void Div(int ansl,int ansr,int quel,int quer){
	if(quel>quer)return;//集合为空的边界
	int mid=(ansl+ansr)>>1,vi,sum,lt=quel-1,rt=quer+1;
	if(ansl==ansr){
		for(vi=quel;vi<=quer;vi++)Q[vi].ans=T[ansl].val;//二分答案底部的边界
		return;
	}
	for(vi=ansl;vi<=mid;vi++)Change(T[vi].x,T[vi].y,1);
	for(vi=quel;vi<=quer;vi++){
		sum=Getsum(Q[vi].x[1],Q[vi].y[1])+Getsum(Q[vi].x[0]-1,Q[vi].y[0]-1);
		sum-=Getsum(Q[vi].x[1],Q[vi].y[0]-1)+Getsum(Q[vi].x[0]-1,Q[vi].y[1]);
		if(sum>=Q[vi].k){
			lt++; tmp[lt]=Q[vi];
		}else{
			rt--; Q[vi].k-=sum; tmp[rt]=Q[vi];
		}
	}
	for(vi=quel;vi<=quer;vi++)Q[vi]=tmp[vi];
	for(vi=ansl;vi<=mid;vi++)Change(T[vi].x,T[vi].y,-1);
	Div(ansl,mid,quel,lt); Div(mid+1,ansr,rt,quer);
}
int main(){
	int i,j,k;
	read(n); read(q);//读入
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++){
		k=(i-1)*n+j; T[k].x=i; T[k].y=j; read(T[k].val);
	}
	std::sort(T+1,T+n*n+1,Acmp);//排序
	for(i=1;i<=q;i++){
		read(Q[i].x[0]); read(Q[i].y[0]); read(Q[i].x[1]); read(Q[i].y[1]); read(Q[i].k); Q[i].num=i;
	}
	Div(1,n*n,1,q);//整体二分
	for(i=1;i<=q;i++)Ans[Q[i].num]=Q[i].ans;
	for(i=1;i<=q;i++)printf("%d\n",Ans[i]);//输出答案
}