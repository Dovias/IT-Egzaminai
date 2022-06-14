#include <fstream>

#define MOKINIU_SKAICIUS 5
#define MAX_VARDO_ILGIS 10+1
#define MAX_UZDAVINIU_KIEKIS 12

struct Mokinys {
    char vardas[20];
    unsigned int laikai[MAX_UZDAVINIU_KIEKIS];
    unsigned int isspresta, taskai, laikas;

    void apskaiciuoti(unsigned int duomenys[], const size_t duomenuIlgis);
};

int main() {
    // Nuskaitom duomenis
    std::ifstream sFailas("U1.txt");
    // Jeigu failas neatidarytas, nieko nebedarom
    if (!sFailas.is_open()) return 1;

    // Jeigu uzdaviniu kiekis nebuvo rastas faile, arba jis yra didesnis uz MAX_UZDAVINIU
    // kieki, nieko nebedarom, nes duomenys neteisingi.
    unsigned int uzdKiekis;
    if (!(sFailas >> uzdKiekis) || uzdKiekis > MAX_UZDAVINIU_KIEKIS) return 2;
    // Issaugom uzduociu duomenis i skaiciu masyva 
    unsigned int uzdDuomenuIlgis = uzdKiekis*2;
    unsigned int uzdDuomenys[uzdDuomenuIlgis];
    for (size_t i = 0; i < uzdDuomenuIlgis; i++) {
        if (!(sFailas >> uzdDuomenys[i])) return 3;
    }

    Mokinys mokDuomenys[MOKINIU_SKAICIUS];
    unsigned int didTaskai = 0;
    sFailas.ignore();
    for (size_t i = 0; i < MOKINIU_SKAICIUS; i++) {
        sFailas.get(mokDuomenys[i].vardas, MAX_VARDO_ILGIS);
        for (size_t j = 0; j < uzdKiekis; j++) {
            if (!(sFailas >> mokDuomenys[i].laikai[j])) return 4;
        }
        // Apskaiciuojam mokinio rezultatus.
        mokDuomenys[i].apskaiciuoti(uzdDuomenys, uzdDuomenuIlgis);

        // Isgaunam didziausia tasku kieki finale.
        if (mokDuomenys[i].taskai > didTaskai) {
            didTaskai = mokDuomenys[i].taskai;
        }
        sFailas.ignore();
    }
    sFailas.close();

    // Insertion sort algoritmas isrusiuojantis mokiniu duomenis.
    Mokinys* rezultatai[MOKINIU_SKAICIUS];
    rezultatai[0] = &(mokDuomenys[0]);
    for (size_t i = 1; i < MOKINIU_SKAICIUS; i++) {
        int j = i-1;
        while (j > -1 && (mokDuomenys[i].isspresta > rezultatai[j]->isspresta || mokDuomenys[i].laikas < rezultatai[j]->laikas)) {
            rezultatai[j+1] = rezultatai[j];
            j--;
        }
        rezultatai[j+1] = &(mokDuomenys[i]);
    }

    // Issaugom duomenis.
    std::ofstream oFailas("U1rez.txt");
    if (!oFailas.is_open()) return 5;
    oFailas << didTaskai;
    // Kadangi tai yra finalas, reikia ismesti vieno paskutinio zmogaus rezultatus,
    // todel ji ignoruojam cikla nustatydami iki MOKINIU-SKAICIUS-1
    for (size_t i = 0; i < MOKINIU_SKAICIUS-1; i++) {
        oFailas << '\n' << rezultatai[i]->vardas << ' ' << rezultatai[i]->isspresta << ' ' << rezultatai[i]->laikas;
    }
    oFailas.close();

    return 0;
}

// Apskaiciuoja mokinio duomenis naudojant strukturos metoda ir this pointeri, leidzianti
// isgauti mokinio duomenis (mokinys.apskaiciuoti())
void Mokinys::apskaiciuoti(unsigned int duomenys[], const size_t duomenuIlgis) {
    const size_t uzdKiekis = duomenuIlgis / 2;
    if (uzdKiekis > MAX_UZDAVINIU_KIEKIS) return;

    this->isspresta = 0;
    this->taskai = 0;
    this->laikas = 0;
    for (size_t i = 0; i < uzdKiekis; i++) {
        int laikas = this->laikai[i];
        if (laikas == 0) continue;
        this->taskai += laikas > duomenys[i+1] ? duomenys[i+1+uzdKiekis] / 2 : duomenys[i+1+uzdKiekis];
        this->laikas += laikas;
        this->isspresta++;
    }
}
