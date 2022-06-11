#include <fstream>

using namespace std;

struct dancer {
  string name;
  int points[2][100];
  int score = 0;
};

void read(dancer data[], int & n, int & k) {
  char names[20];

  ifstream fd("U2.txt");
  fd >> n >> k;
  for (int i = 0; i < n; i++) {
    fd.ignore(255, '\n');
    fd.get(names, 20);
    data[i].name = names;
    for (int j = 0; j < 2; j++) {
      for (int y = 0; y < k; y++) {
        fd >> data[i].points[j][y];
      }
    }

  }
  fd.close();
}

void countPoints(dancer data[], int & n, int & k, int & i, int & j) {
  int tempB = 0;
  int tempS = 11;
  for (int y = 0; y < k; y++) {
    data[i].score += data[i].points[j][y];
    if (data[i].points[j][y] > tempB) {
      tempB = data[i].points[j][y];
    }
    if (data[i].points[j][y] < tempS) {
      tempS = data[i].points[j][y];
    }

  }
  data[i].score = data[i].score - tempB - tempS;
  tempB = 0;
  tempS = 11;
}

void sort(dancer data[], int & n, int & k) {

  dancer temp;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (data[i].score < data[j].score) {
        temp = data[i];
        data[i] = data[j];
        data[j] = temp;
      }
    }
  }
}

void write(dancer data[], int & n) {
  ofstream fr("U2rez.txt");
  for (int i = 0; i < n; i++) {
    fr << data[i].name << "  " << data[i].score << endl;
  }
  fr.close();
}

int main() {
  dancer data[100];
  int n, k;

  read(data, n, k);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 2; j++) {
      countPoints(data, n, k, i, j);
    }
  }
  sort(data, n, k);
  write(data, n);
}
