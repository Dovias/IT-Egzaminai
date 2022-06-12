#include <fstream>

bool uzkrautiDuomenis(const char* failoAdresas, int(& duomenys)[8]);
bool issaugotiDuomenis(const char* failoAdresas, int(& duomenys)[8]);
void apdorotiDuomenis(int(& duomenys)[8], int(& rezultatai)[11]);

int main() {
    int duomenys[8];
    if (!uzkrautiDuomenis("U1.txt", duomenys)) return 1;
    return !issaugotiDuomenis("U1rez.txt", duomenys);
}

bool uzkrautiDuomenis(const char* failoAdresas, int(& duomenys)[8]) {
    std::ifstream failas(failoAdresas);
    if (!failas.is_open()) return false;
    for (int i = 0; i < 8; i++) {
        failas >> duomenys[i];
    }
    return true;
}

bool issaugotiDuomenis(const char* failoAdresas, int(& duomenys)[8]) {
    std::ofstream failas(failoAdresas);
    // Jeigu failas neatidarytas iseinam is funkcijos.
    if (!failas.is_open()) return false;
    int rezultatai[11];
    // Gaunam rezultatus is funkcijos
    apdorotiDuomenis(duomenys, rezultatai);
    // Issaugom rezultatus i faila.
    failas << rezultatai[0] << ' ' << rezultatai[1] << ' ' << rezultatai[2] << ' ' << rezultatai[3] << '\n';
    failas << rezultatai[4] << ' ' << rezultatai[5] << ' ' << rezultatai[6] << '\n';
    failas << rezultatai[7] << ' ' << rezultatai[8] << ' ' << rezultatai[9] << '\n';
    failas << rezultatai[10];
    return true;
}

// Funkcija apskaiciuojanti duomenis issaugojimui faile. (Visus, iskaitant ir nurodymuose prasytus).
void apdorotiDuomenis(int(& duomenys)[8], int(& rezultatai)[11]) {
    rezultatai[3] = duomenys[3];
    rezultatai[10] = -duomenys[4];
    for (int i = 2; i > -1; i--) {
        int litrai = i*2+1;
        // Isgaunam galimu indu kieki (kiek litru turime / litru stiklainis)
        // ir ji palyginame su duotu turimu indu kiekiu duomenu faile.
        int didziausiasKiekis = rezultatai[3] / litrai;
        if (didziausiasKiekis > duomenys[i]) {
            rezultatai[i] = duomenys[i];
            // rezultatai[i+4] - kiek liko nepanaudotu to tipo stiklainiu. 
            // Jeigu galimas kiekis virsija indu skaiciu, tai reiskia, kad indu liks 0.
            rezultatai[i+4] = 0;
        } else {
            // jeigu didziausias indu kiekis yra mazesnis uz turima, reiskias, kad didziausias kiekis
            // yra didziausias galimas pripildytas indu kiekis.
            rezultatai[i] = didziausiasKiekis;
            rezultatai[i+4] = didziausiasKiekis - duomenys[i];
        }
        // Atemam didziausiu indu kiekio litru suma is pagrindines litru sumos.
        rezultatai[3] -= rezultatai[i] * litrai;
    }
    // Pasidarom kopija sumos, kad galetumem apskaiciuoti trukstamus indus ir galima pelna.
    int suma = rezultatai[3];
    for (int i = 2; i > -1; i--) {
        int litrai = i*2+1;
        rezultatai[i+7] = suma / litrai;
        suma -= rezultatai[i+7] * litrai;
        rezultatai[10] += (rezultatai[i+7] + rezultatai[i]) * duomenys[i+5];
    }
}
