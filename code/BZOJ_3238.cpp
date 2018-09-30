#include<cstdio>
#include<cstring>
char an[500010]; int lena;
long long ans;
struct rec{
	int x,ne;
}Arre[500010<<1];
int Arrmap[500010<<1];
int top;
void ins(int f,int s){
	top++; Arre[top].x=s; Arre[top].ne=Arrmap[f]; Arrmap[f]=top;
}
struct SAM{
	struct node{
		int ne[26],maxn,size;
	}A[500010<<1];
	int Fa[500010<<1]; bool ifs[500010<<1];
	int cnt,last;
	inline void New(const int &st){
		A[++cnt].maxn=st;
	}
	int p,np,q,nq,vi;
	void Extend(const int &ch){
		New(A[last].maxn+1); p=last; np=cnt; A[np].size=ifs[np]=1;
		for(;p&&!A[p].ne[ch];p=Fa[p])A[p].ne[ch]=np;
		if(!p)Fa[np]=1;else{
			q=A[p].ne[ch];
			if(A[q].maxn!=A[p].maxn+1){
				New(A[p].maxn+1); nq=cnt;
				for(vi=0;vi<26;vi++)A[nq].ne[vi]=A[q].ne[vi];
				Fa[nq]=Fa[q]; Fa[q]=Fa[np]=nq;
				for(;p&&A[p].ne[ch]==q;p=Fa[p])A[p].ne[ch]=nq;
			}else Fa[np]=q;
		}
		last=np;
	}
	int vj;
	void Build(const char *x,const int &len){
		cnt=last=1;
		for(vj=len;vj>=1;vj--)Extend(x[vj]-'a');
	}
	int stk[500010<<1],Fin[500010<<1],stktop,tmp;
	void Topu(){
		for(vi=1;vi<=cnt;vi++)Fin[Fa[vi]]++;
		for(vi=1;vi<=cnt;vi++)if(!Fin[vi])stk[++stktop]=vi;
		while(stktop){
			vi=stk[stktop]; stk[stktop--]=0; tmp=A[vi].size-ifs[vi];
			for(vj=Arrmap[vi];vj;vj=Arre[vj].ne)ans+=(long long)A[Arre[vj].x].size*((long long)tmp-A[Arre[vj].x].size)*(long long)A[vi].maxn;
			if(ifs[vi])ans+=(long long)tmp*A[vi].maxn<<1;
			ins(Fa[vi],vi); A[Fa[vi]].size+=A[vi].size; Fin[Fa[vi]]--; if(!Fin[Fa[vi]])stk[++stktop]=Fa[vi];
		}
	}
}D;
int main(){
	int i;
	scanf("%s",an+1); lena=strlen(an+1);
	D.Build(an,lena);
	D.Topu(); ans=-ans;
	for(i=1;i<=lena;i++){
		ans+=((long long)lena-i)*i+(((long long)lena+i+1)*((long long)lena-i)>>1);
	}
	printf("%lld\n",ans);
}