#include <fstream>

using namespace std;

///funkcija duomenu surasymui

void funkcija(int & n, int m[]) {
  ifstream in ("U1.txt"); in >> n;
  for (int i = 0; i < n; i++) {
    in >> m[i];
  };
  in.close();
}

///sunkiausios radimas

void funkcija1(int m[], int & didz, int n) {
  int j;
  for (int i = 0; i < n; i++) {
    j = i;
    while (j > 0 && m[j] > m[j - 1]) {
      swap(m[j], m[j - 1]);
      j--;
    }
  }
  didz = m[0];
}

///funkcija sk radimui

void funkcija2(int n, int m[], int & sk, int didz) {
  for (int i = 0; i < n; i++) {
    if (m[i] <= didz / 2) {
      sk++;
    }

  }
}

int main() {
  ofstream out("U1rez.txt");
  int n, didz, sk = 0;
  int m[10000];

  funkcija(n, m);
  funkcija1(m, didz, n);
  funkcija2(n, m, sk, didz);

  out << didz << " ";
  out << sk;
  out.close();
}
