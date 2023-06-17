#include <fstream>
#include <iomanip>

void calculateData(int (&data)[50 * 9], float (&resultData)[12 * 3]);

using namespace std;

int main() {
    int n;
    ifstream nuskaitymas("U1.txt");
    nuskaitymas >> n;
    // 50 * 9 nes maks 50 dalyviu ir tiem dalyviam yra priskiriamos po 9 reiksmes atitinkamai.
    int data[50 * 9] = {};
    for (int i = 0; i < n * 9; i++) {
        nuskaitymas >> data[i];
    }
    // uzdarom nuskaitymo saltini, nes likusioje dalyje mes jo nebenaudosim.
    nuskaitymas.close();
    // 12 * 3 nes mes turime 12 kategoriju ir tom kategorijom yra priskiriamos po 3 reiksmes
    // atitinkamai.
    float resultData[12 * 3] = {};
    calculateData(data, resultData);
    // Israsom rezultatus:
    ofstream israsymas("U1rez.txt");
    for (int i = 0; i < 12 * 3; i += 3) {
        if (resultData[i] == 0) {
            break;
        }
        israsymas << resultData[i] << ' ' << resultData[i + 1] << ' ' << fixed << setprecision(2) << resultData[i + 2] << defaultfloat << endl;
    }
    return 0;
}


/* REIKALAVIMAS:
 * Sukurkite ir parasykite viena funkcija,
 * kuri apskaiciuoja kiekvienos klases kategorijos
 * visa nueita atstuma kilometrais ir suskaiciuoja,
 * kiek tos klases kategorijos mokiniu ivede nueitu
 * zingsniu skaiciu kiekviena akcijos savaites diena.
 */
void calculateData(int (&data)[50 * 9], float (&resultData)[12 * 3]) {
    for (int i = 0; i < 50 * 9; i += 9) {
        if (data[i] == 0) {
            break;
        }
        int id = data[i];
        int length = data[i + 1];
        int sum = 0;
        bool flag = false;
        // Surandam ar visi skaiciai nera lygus nuliui
        for (int j = 0; j < 7; j++) {
            int amount = data[i + j + 2];
            if (amount == 0) {
                flag = true;
            }
            sum += amount;
        }
        // Jeigu rastas skaicius, kuris yra nulis nepridedam prie reiksmes
        if (flag) {
            continue;
        }
        // Sukam cikla iki tol kol randam musu klases kategorija arba jeigu
        // jos nera, artimiausios nulines reiksmes, kad pridetumem naujai
        for (int j = 0; j < 12 * 3; j += 3) {
            if (resultData[j] == id || resultData[j] == 0) {
                resultData[j] = id;
                resultData[j + 1]++;
                resultData[j + 2] += (sum * length / 100.0f / 1000.0f);
                break;
            }
        }
    }
}
