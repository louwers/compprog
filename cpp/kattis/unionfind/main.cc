// https://open.kattis.com/problems/unionfind

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class UnionFind {
private:
  vi p;
  vi size;

public:
  UnionFind(int N) {
    p.assign(N, 0);
    for (int i = 0; i != N; ++i)
      p[i] = i;
    size.assign(N, 1);
  }

  int findSet(int i) {
    if (p[i] == i)
      return i;
    p[i] = findSet(p[i]);
    return p[i];
  }

  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  void unionSet(int i, int j) {
    int x = findSet(i);
    int y = findSet(j);
    if (x == y)
      return;
    if (size[x] < size[y])
      swap(x, y);
    p[y] = x;
    size[x] += size[y];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  int q;
  cin >> n >> q;
  auto set = UnionFind(n);
  while (q--) {
    char ch;
    cin >> ch;
    int x;
    int y;
    cin >> x >> y;
    if (ch == '=') {
      set.unionSet(x, y);
    } else if (ch == '?') {
      if (set.isSameSet(x, y))
        cout << "yes" << '\n';
      else
        cout << "no" << '\n';
    }
  }
}

