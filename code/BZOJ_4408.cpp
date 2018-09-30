/*
题目大意：求区间可重集合的mex
假设[1..sum]都可被表示，然后如果存在某一个数，这个数比它前面的数的sum至少大2，那么答案就是它前面那个数的sum+1。
那么假设现在处理了前面较小的一些数之后的答案为ans，
然后可以求出比ans小的数的总和sum，如果sum<ans，那么答案就是ans；否则将ans更新为sum+1。
*/
#include<cstdio>
#include<algorithm>
int none=0;
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
int n,m,top;
/*simplify*/
struct inf{
	int x,p;
}A[110000];
inline bool Acmp(const inf &a,const inf &b){
	return a.x<b.x;
}
int cnt;
int B[110000],Q[110000],Temp[110000];
/*Segment tree*/
struct node{
	int l,r,m,s[2];
	int sum;
};
node Seg[2100000];
/*Chairman tree*/
int root[110000];
int Segbuild(int l,int r){
	int p=++top; Seg[p].l=l; Seg[p].r=r; Seg[p].m=(l+r)>>1; if(l==r)return p;
	Seg[p].s[0]=Segbuild(l,Seg[p].m); Seg[p].s[1]=Segbuild(Seg[p].m+1,r);
	return p;
}
int Update(int p,int k,int w){
	int q=++top; Seg[q]=Seg[p]; Seg[q].sum+=w; if(Seg[p].l==Seg[p].r)return q;
	if(k<=Seg[p].m)Seg[q].s[0]=Update(Seg[p].s[0],k,w);else Seg[q].s[1]=Update(Seg[p].s[1],k,w);
	return q;
}
int SegGetsum(int x,int y,int l,int r){
	if(Seg[x].l==l&&Seg[x].r==r)return Seg[y].sum-Seg[x].sum;
	if(r<=Seg[x].m)return SegGetsum(Seg[x].s[0],Seg[y].s[0],l,r);
	else
	if(Seg[x].m+1<=l)return SegGetsum(Seg[x].s[1],Seg[y].s[1],l,r);
	else return
	SegGetsum(Seg[x].s[0],Seg[y].s[0],l,Seg[x].m)+SegGetsum(Seg[x].s[1],Seg[y].s[1],Seg[x].m+1,r);
}
int main(){
	int i,l,r,tl,tr,mid,line,ans,sum;
	freopen("mystic.in","r",stdin); freopen("mystic.out","w",stdout);
	read(n);
	for(i=1;i<=n;i++){
		read(A[i].x); A[i].p=i; Q[i]=A[i].x;
	}
	std::sort(A+1,A+n+1,Acmp);
	for(i=1;i<=n;i++)if(A[i].x!=A[i-1].x){
		B[A[i].p]=B[A[i-1].p]+1; Temp[++cnt]=A[i].x;
	}else B[A[i].p]=B[A[i-1].p];
	root[0]=Segbuild(1,cnt);
	for(i=1;i<=n;i++)
	root[i]=Update(root[i-1],B[i],Q[i]);
	read(m);
	for(i=1;i<=m;i++){
		read(l);read(r);ans=1;
		for(;;){
			if(ans<Temp[1])line=0;else{
				tl=1;tr=cnt;
				while(tl!=tr){
					mid=((tl+tr)>>1)+1;
					if(Temp[mid]<=ans)tl=mid;else tr=mid-1;
				}
				line=tl;
			}
			if(!line)sum=0;else sum=SegGetsum(root[l-1],root[r],1,line);
			if(sum<ans)break;else ans=sum+1;
		}
		printf("%d\n",ans);
	}
}