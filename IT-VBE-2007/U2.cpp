#include <fstream>
#include <iomanip> // Biblioteka reikalinga pozicionuoti skaicius.

#define MAX_GRYBAUTOJU_SKAICIUS 100
#define MAX_DIENU_SKAICIUS 50
#define MAX_VARDO_ILGIS 15+1 // +1 reikalingas saugoti \0 simboli, kuris pazymi teksto pabaiga atmintyje.

// Naudojamas duomenu irasu tipas, kuri prasoma naudoti uzduoties salygose.
struct Grybautojas {
    char vardas[MAX_VARDO_ILGIS];
    // unsigned prierasas reiskia kad kintamasis siuo atveju negales tureti zemesniu reiksmiu nei 0.
    unsigned int a = 0, b = 0, c = 0;
};

bool uzkrautiDuomenis(const char* failoAdresas, Grybautojas(& duomenys)[MAX_GRYBAUTOJU_SKAICIUS], size_t& duomenuIlgis);
bool issaugotiDuomenis(const char* failoAdresas, Grybautojas(& duomenys)[MAX_GRYBAUTOJU_SKAICIUS], const size_t duomenuIlgis);
Grybautojas& apdorotiDuomenis(Grybautojas(& duomenys)[MAX_GRYBAUTOJU_SKAICIUS], const size_t duomenuIlgis);

int main() {
    Grybautojas duomenys[MAX_GRYBAUTOJU_SKAICIUS];
    size_t duomenuIlgis;
    if (!uzkrautiDuomenis("U2.txt", duomenys, duomenuIlgis)) return 1;
    return !issaugotiDuomenis("U2rez.txt", duomenys, duomenuIlgis);
}

// Uzkrauna duomenis i duomenu iraso tipo masyva.
// Ignoruoja dienas, kadangi tai nereikalinga informacija bei visus grybu kiekius sudeda i tris kintamuosius (a, b, c).
bool uzkrautiDuomenis(const char* failoAdresas, Grybautojas(& duomenys)[MAX_GRYBAUTOJU_SKAICIUS], size_t& duomenuIlgis) {
    std::ifstream failas(failoAdresas);
    if (!failas.is_open()) return false;
    // Patikrinam ar isgautas duomenu ilgis atitinka reikalavimus.
    if (!(failas >> duomenuIlgis) || duomenuIlgis > MAX_GRYBAUTOJU_SKAICIUS) return false;

    failas.ignore(); // Pries simboliu isgavima naudojant failas.get(), siuo atveju butina ignoruoti nematomus \r\n simbolius faile.
    for (size_t i = 0; i < duomenuIlgis; i++) {
        // isgauna pirmus MAX_VARDO_ILGIS simbolius i duomenys[i].vardas kintamaji.
        failas.get(duomenys[i].vardas, MAX_VARDO_ILGIS);
        size_t dienuSkaicius;
        if (!(failas >> dienuSkaicius) || dienuSkaicius > MAX_DIENU_SKAICIUS) return false;
        for (size_t j = 0; j < dienuSkaicius; j++) {
            // unsigned prierasas reiskia kad kintamasis siuo atveju negales tureti zemesniu reiksmiu nei 0.
            unsigned int a, b, c;
            // Patikrinam ar reiksmes buvo isgautos.
            if (!(failas >> a >> b >> c)) return false;

            duomenys[i].a += a;
            duomenys[i].b += b;
            duomenys[i].c += c;
        }
        failas.ignore(); // Po simboliu isgavimo naudojant failas.get(), siuo atveju butina ignoruoti nematomus \r\n simbolius faile.
    }

    // Failo saltinio objekto destruktorius uzdaro failo saltini, todel jo uzdaryti nereikia.
    return true;
}

bool issaugotiDuomenis(const char* failoAdresas, Grybautojas(& duomenys)[MAX_GRYBAUTOJU_SKAICIUS], const size_t duomenuIlgis) {
    // Patikrinam ar nurodytas duomenuIlgis kintamasis atitinka reikalavimus.
    if (duomenuIlgis > MAX_GRYBAUTOJU_SKAICIUS) return false;

    std::ofstream failas(failoAdresas);
    if (!failas.is_open()) return false;
    for (size_t i = 0; i < duomenuIlgis; i++) {
        // 1. std::right pozicionuoja skaicius is desines puses
        // 2. std::setw(5) sudaro 5 simboliu bloka kiekvienam skaiciui.
        failas << duomenys[i].vardas << std::right << std::setw(5) << duomenys[i].a << std::setw(5) << duomenys[i].b << std::setw(5) << duomenys[i].c << '\n';
    }
    Grybautojas& grybautojas = apdorotiDuomenis(duomenys, duomenuIlgis);
    failas << grybautojas.vardas << grybautojas.a + grybautojas.b + grybautojas.c;

    // Failo saltinio objekto destruktorius uzdaro failo saltini, todel jo uzdaryti nereikia.
    return true;

}

Grybautojas& apdorotiDuomenis(Grybautojas(& duomenys)[MAX_GRYBAUTOJU_SKAICIUS], const size_t duomenuIlgis) {
    Grybautojas& grybautojas = duomenys[0];
    if (duomenuIlgis > MAX_GRYBAUTOJU_SKAICIUS) return grybautojas;

    // unsigned prierasas reiskia kad kintamasis siuo atveju negales tureti zemesniu reiksmiu nei 0.
    unsigned int didziausiaSuma = 0;
    for (size_t i = 1; i < duomenuIlgis; i++) {
        unsigned int suma = duomenys[i].a + duomenys[i].b + duomenys[i].c;
        if (suma > didziausiaSuma) {
            grybautojas = duomenys[i];
            didziausiaSuma = suma;
        }
    }
    return grybautojas;
}
