bool judge(int x){
	long long con=1;
	for(int vi=x;vi;vi/=base)con|=(con<<(vi%base));
	return con&(1ll<<sum);
}