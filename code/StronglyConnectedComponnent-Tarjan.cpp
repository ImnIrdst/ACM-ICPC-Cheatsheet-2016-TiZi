#define MAX 100000

using namespace std;

int dfsNum[MAX+10],dfsLow[MAX+10],vis[MAX+10],in[MAX+10],n,m,lev,ans; vector<int> SCC,adj[MAX+10];

void dfs(int u){
	dfsLow[u]=dfsNum[u]=lev++; vis[u]=1; SCC.push_back(u);
	for(int i=0 ; i<adj[u].size() ; i++){
		int v=adj[u][i];
		if(dfsNum[v]==0) dfs(v);
		if(vis[v]) dfsLow[u]=min(dfsLow[u], dfsLow[v]), in[v]--;
	}
	if(dfsLow[u]==dfsNum[u]){ 
	// this prints all vertices v blong to SCC with dfsLow[v] == dfsLow[u]
		bool flag=true;
		for(int i=0, v ; !SCC.empty() ; i++){
			v=SCC.back(); SCC.pop_back(); vis[v]=0;
			printf("%d ", v);
			if(in[v]) flag=false;
			if(v==u) break;
		}
		printf("\n");
		if(flag) ans++; 
	// counts number of SCCs without indegree outside of other SCCs
	}
}

int main(){
	int tc; scanf("%d", &tc);; int x,y;
	while(tc--){
		scanf("%d %d", &n, &m);
		memset(dfsNum,0,sizeof dfsNum); // memset(adj,0,sizeof adj); 
		memset(dfsLow,0,sizeof dfsLow); memset(vis,0,sizeof vis);
		memset(in,0,sizeof in); lev=1; ans=0;
		
		for(int i=0, j=0 ; i<m ; i++){
			scanf("%d %d", &x, &y); x--; y--;
			adj[x].push_back(y); in[y]++;
		}
		for(int i=0 ; i<n ; i++){
			if(dfsNum[i]==0) dfs(i);
		}
		cout << ans << endl;
	}
	return 0;
}