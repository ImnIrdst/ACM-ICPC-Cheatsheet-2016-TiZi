#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

typedef vector<int> vi;
typedef vector<vi > vvi;


map<string, int> mpsi;
map<int, string> mpis;

int mapId;
int ID(string name){
	if(mpsi.count(name)) return mpsi[name];
	mpsi[name] = mapId;
	mpis[mapId] = name;
	return mapId++;
}

vvi adjOrg, adjRev;  vi vis, ord, col; int n, m;

void dfsOrg(int u){
	if (vis[u]) return; vis[u] = true;
	for (int i = 0; i < adjOrg[u].size(); i++){
		dfsOrg(adjOrg[u][i]);
	}
	ord.push_back(u);
}

int dfsRev(int u, int color){
	if (col[u]) return 0; col[u] = color;

	int ret = 1;
	for (int i = 0; i < adjRev[u].size(); i++){
		ret += dfsRev(adjRev[u][i], color);
	}
	return ret;
}

int main(){
	int cs = 1;
	while (cin >> n >> m && (n+m)) {
		mpsi.clear(); mpis.clear(); mapId = 0;

		adjOrg.assign(n, vi());
		adjRev.assign(n, vi());

		for (int i=0 ; i<m ; i++){
			string uname, vname;
			cin >> uname >> vname;
			int u = ID(uname);
			int v = ID(vname);
			adjOrg[u].push_back(v);
			adjRev[v].push_back(u);
		}

		ord.clear();
		vis.assign(n, 0);
		for (int u = 0; u < n; u++){
			if (!vis[u]) dfsOrg(u);
		}

		int color = 1;
		col.assign(n, 0);
		while (!ord.empty()){
			int u = ord.back();
			if (!col[u]){
				int size = dfsRev(u, color); // SCC Size
				color++;
			}
			ord.pop_back();
		}
		if (cs != 1) cout << endl;
		cout << "Calling circles for data set " << cs++ << ":" << endl;
		for (int c = 1; c<color ; c++) {
			string ws = "";
			for (int u=0 ; u<n ; u++) {
				if(col[u] == c) cout << ws << mpis[u], ws=", ";
			}
			cout << endl;
		}
	}
}
