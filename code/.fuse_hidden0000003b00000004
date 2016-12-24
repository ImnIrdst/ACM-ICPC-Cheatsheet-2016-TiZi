// ----- Maximum Subrectangle Sum
int main(){
	for(int i=1 ; i<n ; i++)//preprocess
		for(int j=0 ; j<n ; j++)
			a[i][j]+=a[i-1][j];

	int Max=0, ans=0;
	for(int k=0 ; k<n ; k++){//calc
		for(int i=0 ; i<n-k ; i++){ Max=0;
			for(int j=0 ; j<n ; j++){
				if(Max<0) Max=a[i+k][j]-a[i][j];
				else Max+=a[i+k][j]-a[i][j];
				if(Max>ans) ans=Max;
	} } }
	//sub array, finsh and start point p=(val, startidx, finishidx)
	p ans=p(-1,0,0); int sum=0,id=1;
	for(int i=1 ; i<n ; i++){
		if(sum<0){sum=0; id=i;}
		sum+=a[i];
		p tmp=p(sum,id,i+1); ans=Max(ans,tmp);	
	}
}
// ----- Optimal Array Multiplication Sequence (Print Path)
int n,a[10+5],p[10+5][10+5],dp[10+5][10+5];
int solve(int L, int R){
	if(L==R){ return 0; }
	if(dp[L][R]!=-1) return dp[L][R];
	int Min=INF;
	for(int i=L ; i<R ; i++){
		int slv=solve(L,i)+solve(i+1,R)+a[(L-1)]*a[i]*a[R];
		if(Min>slv) 	Min=slv; p[L][R]=i;
	}
	return dp[L][R]=Min;
}
//prints like this => (A1 x (A2 x A3))
void print(int L, int R){
	if(L==R){ cout << "A" <<L; return; }
	cout << "("; print(L,p[L][R]);
	cout << " x ";
	print(p[L][R]+1,R); cout << ")";
}
int main(){	int t=1;
	while(cin >> n && n){
		for(int i=1 ; i<=n ; i++)cin >> a[i-1] >> a[i];
		memset(dp,-1,sizeof dp);
		solve(1,n);//cout << solve(1,n) << endl;
		printf("Case %d: ",t++); print(1,n); printf("\n");
	}
}
// ----- LIS
int main(){
	vector<int> v;
	v.push_back(inf);
	for (int i = 0; i<n; i++) {
		int x = dolls[i].w; // array element
		int id = lower_bound(v.begin(), v.end(), x + 1) - v.begin();

		if (id == v.size() - 1) v.push_back(inf); v[id] = x;
	}
	cout << v.size() - 1 << endl;
}
// -----  LCS
int main(){
	dp[MAX][MAX]={0};
	for(int i=1 ; i<=n ; i++){
				for(int j=1 ; j<=n ; j++){
					if(a[i-1]==b[j-1]) dp[i][j]=dp[i-1][j-1]+1;
					else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
	}}
	cout << dp[n][n] << endl;
}
// ----- TSP
p a[15]; int n, dp[15][1<<15];
int solve(int pos, int bitset){
	int& dpp=dp[pos][bitset]; //dpp = dp poniter
	if(bitset==(1<<n)-1) return dist(a[pos],a[0]);
	if(dpp!=-1) return dpp;
	dpp=INF;
	for(int i=0 ; i<n ; i++){
		if(!(bitset&(1<<i))) dpp=min(dpp,solve(i,bitset|(1<<i))+dist(a[pos],a[i]));
	}
	return dpp;
}
int main(){
	int tc; cin >> tc;
	while(tc--){
		cin >> a[0].X >> a[0].Y;  cin >> n; n++;
		for(int i=1 ; i<n ; i++) cin >> a[i].X >> a[i].Y;
		memset(dp, -1, sizeof dp);
		cout << solve(0,1) << endl;
	}
	return 0;
}