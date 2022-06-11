#include <fstream>

#define MAX_DIENU_SKAICIUS 100

bool uzkrautiDuomenis(const char* failoAdresas, int(& duomenys)[MAX_DIENU_SKAICIUS*3+2]);
bool issaugotiDuomenis(const char* failoAdresas, const int(& duomenys)[MAX_DIENU_SKAICIUS*3+2]);
int apdorotiDuomenis(const int(& duomenys)[MAX_DIENU_SKAICIUS*3+2]);

int main() {
    int duomenys[MAX_DIENU_SKAICIUS*3+2] = {}; // {} reikalingas, kad masyvas turetu visas reiksmes nustatytas i nulius.
    if (!uzkrautiDuomenis("U1.txt", duomenys)) return 1;
    return !issaugotiDuomenis("U1rez.txt", duomenys);
}

// Uzkrauna duomenis hash'inimo pavidalu. Naudoja dienu skaicius kaip indeksus,
// duomenims saugoti, taip greitai surusiuodamas ir suskaiciuodamas dienomis surinktus grybus.
bool uzkrautiDuomenis(const char* failoAdresas, int(& duomenys)[MAX_DIENU_SKAICIUS*3+2]) {
    std::ifstream failas(failoAdresas);
    if (!failas.is_open()) return false; // Patikrina ar failas yra skaitomas.
    int dienuSkaicius;
    // Patikrina ar yra kokia nors duomenys, kad galetumem apdoroti,
    // o jeigu yra dar patikrina ar jie atitinka reikalavimus.
    if (!(failas >> dienuSkaicius) || entrySize < 0 || entrySize > MAX_DIENU_SKAICIUS) return false;

    duomenys[0] = MAX_DIENU_SKAICIUS;
    for (size_t i = 0; i < dienuSkaicius; i++) {
        int id, a, b, c;
        // Patikrina ar yra kokia nors duomenys, kad galetumem apdoroti.
        // Jeigu yra, patikrina ar jie atitinka uzduoties reikalavimus.
        if (!(failas >> id >> a >> b >> c) || id < 1 || id > MAX_DIENU_SKAICIUS || a < 0 || b < 0 || c < 0) return false;

        // Optimizuoja velesni duomenu apdorojima, isrenka didziausius indeksus,
        // kad nereiktu tusciai sukti cikla kur nera duomenu.
        if (id < duomenys[0]) {
            duomenys[0] = id;
        }
        if (id >= duomenys[1]) {
            duomenys[1] = id;
        }

        // Prideda uzkrautas reiksmes i dienos skaiciumi sugeneruota indeksa masyve:
        // Indekso formule: ((id-1) * 3 grybu indeksai + 2 optimizavimo indeksai)
        int keyIndex = (id-1)*3+2;
        duomenys[keyIndex] += a;
        duomenys[keyIndex+1] += b;
        duomenys[keyIndex+2] += c;
    }
    duomenys[0] = (duomenys[0]-1)*3+2; // Konvertuoja optimizacijos dienas i masyvo indeksus.
    duomenys[1] = duomenys[1]*3+2; // Konvertuoja optimizacijos dienas i masyvo indeksus.
    // Funkcijos destruktorius uzdaro failo saltini todel jo uzdaryti nereikia.
    return true;
}

bool issaugotiDuomenis(const char* failoAdresas, const int(& duomenys)[MAX_DIENU_SKAICIUS*3+2]) {
    std::ofstream failas(failoAdresas);
    if (!failas.is_open()) return false; // Patikrina ar failas yra skaitomas.
    for (size_t i = duomenys[0], j = duomenys[1]; i < j; i+=3) {
        int a = duomenys[i], b = duomenys[i+1], c = duomenys[i+2];
        if (a == 0 && b == 0 && c == 0) continue;
        failas << i/3+1 << ' ' << a << ' ' << b << ' ' << c << '\n';
    }
    int id = apdorotiDuomenis(duomenys);
    failas << id << ' ' << duomenys[(id-1)*3+2] + duomenys[(id-1)*3+3] + duomenys[(id-1)*3+4];

    // Funkcijos destruktorius uzdaro failo saltini todel jo uzdaryti nereikia.
    return true;
}

// Funkcija dienos, kuria surinkta daugiausia grybu, numeriui rasti.
int apdorotiDuomenis(const int(& duomenys)[MAX_DIENU_SKAICIUS*3+2]) {
    int didziausiasIndeksas = 3;
    for (size_t i = duomenys[0], j = duomenys[1]; i < j; i+=3) {
        int suma = duomenys[i] + duomenys[i+1] + duomenys[i+2];
        if (suma > duomenys[didziausiasIndeksas] + duomenys[didziausiasIndeksas+1] + duomenys[didziausiasIndeksas+2]) {
            didziausiasIndeksas = i;
        }
    }
    return didziausiasIndeksas/3+1; // Isgauna diena is masyvo indekso;
}
