#include <iostream>
#include <vector>

using namespace std;

vector<int> parent, rankDSU;

void initialize(int n) {
    parent.resize(n);
    rankDSU.resize(n, 0);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

void print_state() {
    for (size_t i = 0; i < parent.size(); i++) {
        cout << parent[i] << "(" << rankDSU[i] << ") ";
    }
    cout << endl;
}

void union_sets(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);
    if (root_x != root_y) {
        if (rankDSU[root_x] > rankDSU[root_y]) {
            parent[root_y] = root_x;
        } else if (rankDSU[root_x] < rankDSU[root_y]) {
            parent[root_x] = root_y;
        } else {
            parent[root_y] = root_x;
            rankDSU[root_x]++;
        }
    }
    print_state();
}



int main() {
    int n;
    cin >> n;
    initialize(n);
    print_state();

    int q;
    cin >> q; // Lire le nombre total d'opérations
    for (int i = 0; i < q; i++) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            print_state();
        } else if (cmd == 2) {
            int x;
            cin >> x;
            cout << find(x) << endl;
        } else if (cmd == 3) {
            int x, y;
            cin >> x >> y;
            union_sets(x, y);
        } else if (cmd == 4) {
            print_state();
        }
    }
    return 0;
}
