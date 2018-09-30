#include<cstdio>
char ch;
inline void read(int &a){
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar());
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
}
int n,m,top,qtop;
int A[210000];
long long SumA[210000];
struct inf{
	int x,w;//如果是修改，就表示把[1..x]+w，如果是查询，就表示查询[1..x]的修改值，编号为w 
	int opt;//opt为0表示修改，非0表示查询，如特别的，1表示对答案有正贡献，-1表示对答案有负贡献 
}Q[410000],tmp[410000];
long long Ans[210000];
void CDQ(const int &l,const int &r){
	if(l==r)return;
	int m=(l+r)>>1,tl,tr,tt,last=0; long long val=0,sum=0;
	CDQ(l,m); CDQ(m+1,r);
	for(tl=l;tl<=m;tl++)if(!Q[tl].opt)val+=Q[tl].w;
	for(tl=l,tr=m+1;tr<=r;tr++){
		if(!Q[tr].opt)continue;
		while(Q[tl].x<=Q[tr].x&&tl<=m){
			if(!Q[tl].opt){sum+=val*(Q[tl].x-last); last=Q[tl].x; val-=Q[tl].w;} tl++;
		}
		Ans[Q[tr].w]+=(sum+val*(Q[tr].x-last))*Q[tr].opt;
	}
	for(tl=l,tr=m+1,tt=l;tt<=r;tt++)
	if(tr>r||(tl<=m&&Q[tl].x<=Q[tr].x))tmp[tt]=Q[tl++];else tmp[tt]=Q[tr++];
	for(tt=l;tt<=r;tt++)Q[tt]=tmp[tt];
}
int main(){
	int i,opt,l,r,w;
	read(n);
	for(i=1;i<=n;i++)read(A[i]),SumA[i]=SumA[i-1]+A[i];
	read(m);
	for(i=1;i<=m;i++){
		read(opt);
		if(opt==1){
			read(l); read(r); read(w); Q[++top].x=l-1; Q[top].w=-w; Q[++top].x=r; Q[top].w=w;
		}else{
			read(l); read(r); qtop++; Ans[qtop]+=SumA[r]-SumA[l-1];
			Q[++top].x=l-1; Q[top].w=qtop; Q[top].opt=-1; Q[++top].x=r; Q[top].w=qtop; Q[top].opt=1;
		}
	}
	CDQ(1,top);
	for(i=1;i<=qtop;i++)printf("%lld\n",Ans[i]);
}