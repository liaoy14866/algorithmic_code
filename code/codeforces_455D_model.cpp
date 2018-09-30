int A[100010];
struct link{
	int top,ne;
	int Bucket[100010],A[2100];
}C[210];
void flip(const int &bp){
	int vi;
	top++; C[top].ne=C[bp].ne; C[bp].ne=top;
	for(vi=C[bp].top;vi>=Threshold+1;vi--){
		C[top].A[vi-Threshold]=C[bp].A[vi];
		C[top].Bucket[C[top].A[vi-Threshold]]++; C[bp].Bucket[C[bp].A[vi]]--;
		C[bp].A[vi]=0;
		C[bp].top--; C[top].top++;
	}
}
void Ins(int p,const int &w){
	int vi,bp,now=0;
	for(bp=1;now+C[bp].top<p;bp=C[bp].ne)now+=C[bp].top;
	p-=now; C[bp].top++; for(vi=C[bp].top;vi>=p+1;vi--)C[bp].A[vi]=C[bp].A[vi-1];
	C[bp].Bucket[w]++; C[bp].A[p]=w;
	if(C[bp].top>Threshold<<1)flip(bp);
}
void Del(int p){
	int vi,bp,now=0;
	for(bp=1;now+C[bp].top<p;bp=C[bp].ne)now+=C[bp].top;
	p-=now; C[bp].Bucket[C[bp].A[p]]--;
	for(vi=p;vi<=C[bp].top;vi++)C[bp].A[vi]=C[bp].A[vi+1]; C[bp].A[vi]=0;
}
int Getsum(int l,int r,const int &k){
	int bl,br,now=0,sum=0,vi;
	for(bl=1;now+C[bl].top<l;bl=C[bl].ne)now+=C[bl].top; l-=now;
	for(br=bl;now+C[br].top<r;br=C[br].ne)now+=C[br].top; r-=now;
	if(bl!=br&&C[bl].ne!=br)for(vi=C[bl].ne;vi!=br;vi=C[vi].ne)sum+=C[vi].Bucket[k];
	if(bl!=br){
		for(vi=l;vi<=C[bl].top;vi++)sum+=(C[bl].A[vi]==k);
		for(vi=1;vi<=r;vi++)sum+=(C[br].A[vi]==k);
	}else{
		for(vi=l;vi<=r;vi++)sum+=(C[bl].A[vi]==k);
	}
	return sum;
}