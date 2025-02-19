#include <iostream>
#include <vector>

using namespace std;

vector<int> parent;

// for initialization ...

void initialize(int n) {
    parent.resize(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int find(int x) {
    if (parent[x] == x)
        return x;
    return find(parent[x]);
}

void union_sets(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);
    if (root_x != root_y) {
        parent[root_y] = root_x;
    }
}

void print_state() {
    for (int i : parent) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    initialize(n);
    print_state();

    int q=10;
    //cin >> q;
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
            print_state();
        }
    }
    return 0;
}

