/*
求最长公共子串
SAM最辣鸡的题目
*/
#include<cstdio>
#include<algorithm>
#include<cstring>
inline void read(int &a){
	char c=getchar();
	for(a=0;c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())(a*=10)+=c-'0';
}
char a[110000],b[110000];
int len;
struct suffix_automaton{
	struct node{
		int ne[26],step;
	}A[110000*2];
	int pre[110000*2];
	int last,cnt;
	inline void New(int st){
		A[++cnt].step=st;
	}
	int p,np,q,nq,vi;
	void Extend(int ch){
		//在这里ch是已经减过'A'的 了
		New(A[last].step+1);
		p=last; np=cnt;
		for(;p&&!A[p].ne[ch];p=pre[p])A[p].ne[ch]=np;
		if(!p)pre[np]=1;
		else{
			q=A[p].ne[ch];
			if(A[q].step!=A[p].step+1){
				New(A[p].step+1); nq=cnt;
				for(vi=0;vi<26;vi++)A[nq].ne[vi]=A[q].ne[vi];
				pre[nq]=pre[q]; pre[q]=pre[np]=nq;
				for(;A[p].ne[ch]==q;p=pre[p])A[p].ne[ch]=nq;
			}else pre[np]=q;
		}
		last=np;
	}
	int vj;
	void Build(){
		cnt=last=1;
		for(vj=1;vj<=len;vj++)
		Extend(a[vj]-'a');
	}
	int ans,now;
	int Run(){
		ans=now=0;p=1;
		for(vi=1;vi<=len;vi++){
			if(A[p].ne[b[vi]-'a']){
				p=A[p].ne[b[vi]-'a']; now++;
			}else{
				for(;p&&!A[p].ne[b[vi]-'a'];)p=pre[p];
				if(!p){
					p=1; now=0;
				}else{
					now=A[p].step+1;
					p=A[p].ne[b[vi]-'a'];
				}
			}
			ans=std::max(ans,now);
		}
		return ans;
	}
}D;
int ans;
int main(){
	scanf("%s",a+1); len=strlen(a+1); D.Build();
	scanf("%s",b+1); len=strlen(b+1); ans=D.Run();
	printf("%d\n",ans);
}