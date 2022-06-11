#include <iomanip>
#include <fstream>

using namespace std;
void funkcija(int & n, int a[], int b[], int c[], int & m) {
  ifstream in ("U1.txt"); in >> n;
  for (int i = 0; i < n; i++) {
    in >> a[i] >> b[i] >> c[i];
    if (a[i] == 4)
      m++;
  }
}
int * poros(int n, int a[], int b[], int c[], int x[]) {
  for (int i = 0; i < n - 1; i++)
    for (int y = 1; y < n; y++) {
      if (i != y && a[i] == 4 && a[y] == 4 && b[i] != b[y] && c[i] == c[y]) {
        x[0]++;
        a[i] = 0;
        b[i] = 0;
        c[i] = 0;
        a[y] = 0;
        b[y] = 0;
        c[y] = 0;
      }
      if (i != y && a[i] == 3 && a[y] == 3 && b[i] != b[y] && c[i] == c[y]) {
        x[1]++;
        a[i] = 0;
        b[i] = 0;
        c[i] = 0;
        a[y] = 0;
        b[y] = 0;
        c[y] = 0;
      }
    }
  return x;
}
int * liko(int n, int m, int x[]) {
  x[2] = m - x[0] * 2;
  x[3] = (n - m) - x[1] * 2;
  return x;
}
int main() {
  ofstream out("U1rez.txt");
  int n, a[100], b[100], c[100], m = 0, x[10];
  for (int i = 0; i < 4; i++)
    x[i] = 0;
  funkcija(n, a, b, c, m);
  poros(n, a, b, c, x);
  liko(n, m, x);

  for (int i = 0; i < 4; i++)
    out << x[i] << endl;
}
