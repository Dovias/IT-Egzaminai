#include <fstream>

#define MAX_PINIGU_KIEKIS 3000

bool uzkrautiDuomenis(const char* failoAdresas, unsigned int(& duomenys)[MAX_PINIGU_KIEKIS*4+2]);
bool issaugotiDuomenis(const char* failoAdresas, unsigned int(& duomenys)[MAX_PINIGU_KIEKIS*4+2]);
unsigned int apdorotiDuomenis(unsigned int(& duomenys)[MAX_PINIGU_KIEKIS*2+1]);

int main() {
    unsigned int duomenys[MAX_PINIGU_KIEKIS*4+2];
    if (!uzkrautiDuomenis("U1.txt", duomenys)) return 1;
    return !issaugotiDuomenis("U1rez.txt", duomenys);
}

bool uzkrautiDuomenis(const char* failoAdresas, unsigned int(& duomenys)[MAX_PINIGU_KIEKIS*4+2]) {
    std::ifstream failas(failoAdresas);
    // Patikrina ar yra kokia nors duomenys, kad galetumem apdoroti,
    // o jeigu yra dar patikrina ar jie atitinka reikalavimus.
    if (!failas.is_open() || !(failas >> duomenys[0]) || duomenys[0] > MAX_PINIGU_KIEKIS) return false;
    // Isgauna pirmo studento duomenis
    size_t indeksas = duomenys[0]*2+1;
    for (size_t i = 1; i < indeksas; i++) {
        // Patikrina ar yra kokia nors duomenys, kad galetumem apdoroti,
        // o jeigu yra dar patikrina ar jie atitinka reikalavimus.
        if (!(failas >> duomenys[i]) || duomenys[i] > MAX_PINIGU_KIEKIS) return false;
    }
    // Isgauna kitus studento duomenis
    failas >> duomenys[indeksas];
    for (size_t i = indeksas+1, j = indeksas+duomenys[indeksas]*2; i < j; i++) {
        if (!(failas >> duomenys[i]) || duomenys[i] > MAX_PINIGU_KIEKIS) return false;
    }
    return true;
}

bool issaugotiDuomenis(const char* failoAdresas, unsigned int(& duomenys)[MAX_PINIGU_KIEKIS*4+2]) {
    std::ofstream failas(failoAdresas);
    if (!failas.is_open()) return false;
    // (unsigned int(&)[MAX_PINIGU_KIEKIS*2+1])duomenys - pavercia masyva duomenys i
    // to studento duomenu submasyva, kuris leidzia apskaiciuoti studento skirta suma.
    unsigned int piniguSuma = apdorotiDuomenis((unsigned int(&)[MAX_PINIGU_KIEKIS*2+1])duomenys);
    unsigned int monetuSuma = 0;

    // duomenys[0]*2+2 - antro studento valstybes monetu indekso pradzia
    // i+duomenys[i-1] - antro studento valstybes monetu indekso pabaiga
    for (int i = duomenys[0]*2+2, j = i+duomenys[i-1]; i < j; i++) {
        unsigned int monetos = piniguSuma / duomenys[i];
        piniguSuma -= monetos * duomenys[i];
        failas << duomenys[i] << ' ' << monetos << '\n';
        monetuSuma += monetos;
    }
    failas << monetuSuma << '\n';

    // Apskaiciuojamos monetos antram studentui, taip pat kaip pirmam.
    // duomenys[duomenys[0]*2+1] - antro studento submasyvo pradzia
    // duomenys[0]+1 - pirmo studento valstybes monetu indekso pabaiga
    piniguSuma = apdorotiDuomenis((unsigned int(&)[MAX_PINIGU_KIEKIS*2+1])(duomenys[duomenys[0]*2+1]));
    monetuSuma = 0;
    for (int i = 1, j = duomenys[0]+1; i < j; i++) {
        unsigned int monetos = piniguSuma / duomenys[i];
        piniguSuma -= monetos * duomenys[i];
        failas << duomenys[i] << ' ' << monetos << '\n';
        monetuSuma += monetos;
    }
    failas << monetuSuma;
    return true;
}

// Funkcija skaiciuojanti kokia suma skaiciuos studentas. Si funkcija gali buti
// pernaudota daugelio tokios pacios strukturos studentu pinigu apskaiciavimui.
unsigned int apdorotiDuomenis(unsigned int(& duomenys)[MAX_PINIGU_KIEKIS*2+1]) {
    int suma = 0;
    for (int i = 1; i < duomenys[0]+1; i++) {
        suma += duomenys[i] * duomenys[i+duomenys[0]];
    }
    return suma;
}

