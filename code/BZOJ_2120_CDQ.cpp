#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
char ch; bool f;
inline void read(int &a){
	f=1;
	for(ch=getchar();ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=0;
	for(a=0;ch<='9'&&ch>='0';ch=getchar())(a*=10)+=ch-'0';
	if(!f)a=-a;
}
int n,m,qtop,top;
set<int> Pos[1000010];
set<int>::iterator pre,suf;
int prenum,sufnum;
int Bucket[1000010];
int A[10010],B[10010],last[10010];
struct ope{
	int p,x,y,num;
	/*
	对于修改，表示把p位置x这个权值-1，y这个权值+1（也就是把x改为y，注意这里是last数组的操作）。
	对于询问，查询p位置在[x..y]的权值。（贡献） 
	*/
	int ope;//0表示修改，1表示查询，特别的，1为正查询，-1为负查询 
}O[10010*3],tmp[10010*3];
int BIT[10010];
void Change(int p,int w){
	if(!p)return;
	for(;p<=n;p+=p&-p)BIT[p]+=w;
}
int Getsum(int p){
	int sum=0; for(;p;p-=p&-p)sum+=BIT[p]; return sum;
}
void Cancel(int p){
	if(!p)return;
	for(;p<=n;p+=p&-p)BIT[p]=0;
}
int Ans[10010];
void CDQ(int l,int r){
	if(l==r)return;
	int m=(l+r)>>1,tl,tr,tt;
	CDQ(l,m);
	CDQ(m+1,r);
	for(tl=l,tr=m+1;tr<=r;tr++){
		if(!O[tr].ope)continue;
		while(O[tl].p<=O[tr].p&&tl<=m){
			if(!O[tl].ope)Change(O[tl].x,-1),Change(O[tl].y,1); tl++;
		}
		Ans[O[tr].num]-=(Getsum(O[tr].y)-Getsum(O[tr].x-1))*O[tr].ope;
	}
	for(tl--;tl>=l;tl--)if(!O[tl].ope)Cancel(O[tl].x),Cancel(O[tl].y);
	for(tl=l,tr=m+1,tt=l;tt<=r;tt++)if((tr>r)||(tl<=m&&O[tl].p<=O[tr].p))tmp[tt]=O[tl++];else tmp[tt]=O[tr++];
	for(tt=l;tt<=r;tt++)O[tt]=tmp[tt];
}
int main(){
	int i,l,r,p,w;
	read(n); read(m);
	for(i=1;i<=n;i++)read(A[i]),Pos[A[i]].insert(i);
	for(i=1;i<=n;i++)last[i]=Bucket[A[i]],Bucket[A[i]]=i,B[i]=last[i];
	for(i=1;i<=m;i++){
		for(ch=getchar();ch!='Q'&&ch!='R';ch=getchar());
		if(ch=='Q'){
			qtop++;
			read(l); read(r); Ans[qtop]+=r-l+1;
			O[++top].p=l-1; O[top].x=l; O[top].y=r; O[top].num=qtop; O[top].ope=-1;
			O[++top].p=r; O[top].x=l; O[top].y=r; O[top].num=qtop; O[top].ope=1;
		}else{
			read(p); read(w);
			/*要做的操作：
			1.找到A[p]集合中p的前驱。
			2.找到A[p]集合中p的后继
			3.令last[suf]=pre 
			*/
			/*
			1.把p插入到w集合中
			2.查找w集合中p的前驱
			3.查找w集合中p的后继
			4.last[p]=pre
			5.last[suf]=p 
			*/
			suf=Pos[A[p]].upper_bound(p);
			if(suf!=Pos[A[p]].end()){
				prenum=(*Pos[A[p]].begin()!=p?(*(--Pos[A[p]].find(p))):0);
				top++; O[top].p=*suf; O[top].x=last[*suf]; O[top].y=prenum;
				last[*suf]=prenum;
			}
			Pos[A[p]].erase(p); Pos[w].insert(p);
			prenum=(*Pos[w].begin()!=p?(*(--Pos[w].find(p))):0);
			top++; O[top].p=p; O[top].x=last[p]; O[top].y=prenum;
			last[p]=prenum;
			suf=Pos[w].upper_bound(p);
			if(suf!=Pos[w].end()){
				top++; O[top].p=*suf; O[top].x=last[*suf]; O[top].y=p;
				last[*suf]=p;
			}
			A[p]=w;
		}
	}
	CDQ(1,top);
	for(p=1,i=1;i<=top;i++){
		if(!O[i].ope)continue;
		while(p<=O[i].p){
			Change(B[p],1); p++;
		}
		Ans[O[i].num]-=(Getsum(O[i].y)-Getsum(O[i].x-1))*O[i].ope;
	}
	for(i=1;i<=qtop;i++)printf("%d\n",Ans[i]);
}