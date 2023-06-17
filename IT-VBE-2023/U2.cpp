#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

struct Password {
    char word[15+1];
    char tag[9+1];
    int data[5];
};

int calculateSimilarity(Password password1, Password password2);
bool isSimilar(Password password1, Password password2);

int main() {
    int n, k;
    ifstream nuskaitymas("U2.txt");
    nuskaitymas >> n >> k;
    // Issaugom paprastus slaptazodzius
    Password passwords[5];
    for (int i = 0; i < n; i++) {
        nuskaitymas.ignore();
        nuskaitymas.get(passwords[i].word, 15+1);
        for (int j = 0; j < 5; j++) {
            nuskaitymas >> passwords[i].data[j];
        }
    }
    // Issaugom su zymemis slaptazodzius
    Password strongPasswords[25];
    for (int i = 0; i < k; i++) {
        nuskaitymas.ignore();
        nuskaitymas.get(strongPasswords[i].word, 15+1);
        for (int j = 0; j < 5; j++) {
            nuskaitymas >> strongPasswords[i].data[j];
        }
        nuskaitymas.ignore();
        nuskaitymas.get(strongPasswords[i].tag, 9+1);
    }
    // uzdarom nuskaitymo saltini, nes jo nebenaudojam,
    nuskaitymas.close();
    ofstream israsymas("U2rez.txt");
    for (int i = 0; i < n; i++) {
        israsymas << passwords[i].word << ' ';

        int similarity = 15;
        Password *similar = nullptr;
        // Randam daugiausiai panasu slaptazodi ir panasumo reiksme
        for (int j = 0; j < k; j++) {
            int candidate = calculateSimilarity(passwords[i], strongPasswords[j]);
            if (candidate < similarity) {
                similarity = candidate;
                similar = &strongPasswords[j];
            }
        }
        israsymas << similar->tag << ' ' << similarity << endl;
        Password *list[25];
        // Isrenkam bent kazkiek panasius slaptazodzius i atskira sarasa
        int l = 0;
        for (int j = 0; j < k; j++) {
            if (isSimilar(*similar, strongPasswords[j])) {
                list[l++] = &strongPasswords[j];
            }
        }
        // Surusiuojam sarasa naudojant bubble sort algoritma
        // (algorithm bibliotekos sort() irgi cia tinka vietoj to)
        for (int j = 0; j < l; j++) {
            for (int m = j+1; m < l; m++) {
                if (list[j]->data[0] < list[m]->data[0]) {
                    Password *temp = list[j];
                    list[j] = list[m];
                    list[m] = temp;
                }
            }
        }
        // Israsom panasiu slaptazodziu sarasa
        for (int j = 0; j < l; j++) {
            israsymas << list[j]->word << std::endl;
        }
    }
    return 0;
}

int calculateSimilarity(Password password1, Password password2) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += abs(password1.data[i] - password2.data[i]);
    }
    return sum;
}


bool isSimilar(Password password1, Password password2) {
    // jeigu slaptazodziu zymes skirtingos, tai jie ir nepanasus.
    if (strcmp(password1.tag, password2.tag) != 0) {
        return false;
    }
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (password1.data[i] == password2.data[i]) {
            count++;
        }
    }
    // jeigu bent viena zyme yra tokia pati, slaptazodziai panasus.
    return count > 0;
}
