int n, lev, dfsRoot, rootChilds;
int dfsLow[MAX], dfsNum[MAX], parent[MAX];
vvi adj; set<pii> bridges; set<int> artPoints;

void dfs(int u) {
	dfsLow[u] = dfsNum[u] = lev++;
	for (int i = 0; i<adj[u].size(); i++) {
		int v = adj[u][i];
		if (dfsNum[v] == 0) {
			if (u == dfsRoot) rootChilds++;
			parent[v] = u; dfs(v);

			if (dfsLow[v] >= dfsNum[u] && u != dfsRoot)//u is articulation point
				artPoints.insert(u);

			if (dfsLow[v] > dfsNum[u]) {
				bridges.insert(pii(v, u));
				bridges.insert(pii(u, v));
			}

			dfsLow[u] = min(dfsLow[u], dfsLow[v]);
		}
		else if (parent[u] != v)
			dfsLow[u] = min(dfsLow[u], dfsNum[v]);
	}
}

int main() {
	while (cin >> n) {
		adj.assign(n, vi()); //initialization
		memset(dfsLow, 0, sizeof dfsLow);
		memset(dfsNum, 0, sizeof dfsNum);
		memset(parent, 0, sizeof parent);
		bridges.clear(); artPoints.clear();
		lev = 1; int tmp, u, m;
		for (int i = 0; i<n; i++) { // construct the graph
			scanf("%d (%d", &u, &m); cin.ignore();
			for (int i = 0; i<m; i++) {
				cin >> tmp; adj[u].push_back(tmp);
			}
		}
		for (int i = 0; i<n; i++) {
			if (dfsNum[i] == 0) {
				dfsRoot = i; rootChilds = 0; dfs(i);
				if (rootChilds >= 2) artPoints.insert(dfsRoot);
			}
		}
		printf("%d critical links\n", bridges.size());
		set<pii>::iterator itr; // print answer
		for (itr = bridges.begin(); itr != bridges.end(); itr++)
			printf("%d - %d\n", itr->first, itr->second);
		cout << endl;
	}
	return 0;}