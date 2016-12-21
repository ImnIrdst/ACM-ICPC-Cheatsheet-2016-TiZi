#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define FOR(i,x,y) for(int i = (x) ; i <= (y) ; ++i)
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#define UNIQUE(V) (V).erase(unique((V).begin(),(V).end()),(V).end())

typedef vector<int> vi;
typedef vector<vi > vvi;

struct Episode {
	int s, e;
	Episode(int s=0, int e=0): s(s), e(e) {}
};

#define SCCNODE 1000
struct SCC{
    int num[SCCNODE], low[SCCNODE], col[SCCNODE], cycle[SCCNODE], st[SCCNODE];
    int tail, cnt, cc;
    vi adj[SCCNODE];

    SCC():tail(0),cnt(0),cc(0) {}
    void clear ( int n ) {
        cc += 3;
        FOR(i,0,n) adj[i].clear();
        tail = 0;
    }
    void tarjan ( int s ) {
        num[s] = low[s] = cnt++;
        col[s] = cc + 1;
        st[tail++] = s;
        FOR(i,0,SZ(adj[s])-1) {
            int t = adj[s][i];
            if ( col[t] <= cc ) {
                tarjan ( t );
                low[s]=min(low[s],low[t]);
            }
            /*Back edge*/
            else if (col[t]==cc+1)
                low[s]=min(low[s],low[t]);
        }
        if ( low[s] == num[s] ) {
            while ( 1 ) {
                int temp=st[tail-1];
                tail--;
                col[temp] = cc + 2;
                cycle[temp] = s;
                if ( s == temp ) break;
            }
        }
    }
    void shrink( int n ) {
        FOR(i,0,n){
            FOR(j,0,SZ(adj[i])-1){
                adj[i][j] = cycle[adj[i][j]]; ///Careful. This will create self-loop
            }
        }
        FOR(i,0,n){
            if ( cycle[i] == i ) continue;
            int u = cycle[i];
            FOR(j,0,SZ(adj[i])-1){
                int v = adj[i][j];
                adj[u].push_back( v );
            }
            adj[i].clear();
        }
        FOR(i,0,n){ ///Not always necessary
            sort ( ALL(adj[i]) );
            UNIQUE(adj[i]);
        }
    }
    void findSCC( int n ) {
        FOR(i,0,n) {
            if ( col[i] <= cc ) {
                tarjan ( i );
            }
        }
    }
};

#define SAT2NODE 2000
/*
1. The nodes need to be split. So change convert() accordingly.
2. Using clauses, populate scc edges.
3. Call possible, to find if a valid solution is possible or not.
4. Dont forget to keep space for !A variables
*/
struct SAT2 {
    SCC scc;

    SAT2(): bfscc(1) {}
    void clear( int n ) { scc.clear( n ); }
    int convert ( int n ) { return n * 2; } ///Change here. Depends on how input is provided
    void mustTrue ( int a ) { scc.adj[a^1].push_back( a ); } ///A is True
    void andClause ( int a, int b ) { scc.adj[a].push_back( b ); scc.adj[b].push_back( a ); }
    void orClause ( int a, int b ) { scc.adj[a^1].push_back( b ); scc.adj[b^1].push_back( a ); } /// A || B clause //!a->b !b->a
	void xorClause ( int a, int b ) { orClause( a, b ); orClause( a^1, b^1 ); }
    void notAndClause ( int a, int b ) { scc.adj[a].push_back( b ^ 1 ); scc.adj[b].push_back( a ^ 1 ); }
    void atMostOneClause ( int a[], int n, int flag ) { /// Out of all possible option, only one is true
        if ( flag == 0 ) { /// At most one can be false
            FOR(i,0,n){
                a[i] = a[i] ^ 1;
            }
        }
        FOR(i,0,n) {
            FOR(j,i+1,n) {
                orClause( a[i] ^ 1, a[j] ^ 1 ); /// !a || !b both being true not allowed
            }
        }
    }

    ///Send n, total number of nodes, after expansion
    bool possible( int n ) {
        scc.findSCC( n );

        FOR(i,0,n) {
            int a = i, b = i^1;
            ///Falls on same cycle a and !a.
            if ( scc.cycle[a] == scc.cycle[b] ) return false;
        }

        ///Valid solution exists
        return true;
    }

    ///To determine if A can be true. It cannot be true, if a path exists from A to !A.
    int vis[SAT2NODE], qqq[SAT2NODE], bfscc;
    void bfs( int s ) {
        bfscc++;
        int qs = 0, qt = 0;
        vis[s] = bfscc;
        qqq[qt++] = s;
        while ( qs < qt ) {
            s = qqq[qs++];
            FOR(i,0,SZ(scc.adj[s])-1) {
                int t = scc.adj[s][i];
                if ( vis[t] != bfscc ) {
                    vis[t] = bfscc;
                    qqq[qt++] = t;
                }
            }
        }
    }

} sat2;


vector< Episode > ep;
void build_graph(int l, int r){
	for(int i=l ; i<=r ; i+=2) {
		sat2.xorClause(sat2.convert(i), sat2.convert(i+1));
	}

	for(int i=l ; i<=r ; i++) {
		for(int j=i+1; j<=r ; j++) {
			if(ep[i].e < ep[j].s || ep[j].e < ep[i].s) continue;
			sat2.notAndClause(sat2.convert(i), sat2.convert(j));
		}
	}
}


int main () {
	int tc;
	cin >> tc;
	while(tc--) {
		int n;
		cin >> n;
		n = n * 2;

		ep.assign(n, Episode());
		for(int i=0 ; i<n ; i++) cin >> ep[i].s >> ep[i].e;

		int ansL = -1, ansR = -1, maxDist = -1;

		int l = 0;
		for (int r = 1 ; r<n ; r+=2) {
			sat2.clear(n * 2);
			build_graph(l, r);

			while(sat2.possible(n * 2) == false) {
				l+=2;
				sat2.clear(n * 2);
				build_graph(l, r);
			}
	
			if (r - l > maxDist) {
				ansR = r/2;
				ansL = l/2;
				maxDist = r - l;
			}
		}

		cout << ansL + 1 << " " << ansR + 1 << endl;
	}	
}