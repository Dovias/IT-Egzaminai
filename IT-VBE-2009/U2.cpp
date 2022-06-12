#include <fstream>

#define MAX_VARDO_ILGIS 20+1 // +1 reikalingas saugoti \0 nematoma simboli pazyminti vardo pabaiga, atmintyje.
#define MAX_BEGIKU_SKAICIUS 50
#define MAX_TAKELIU_SKAICIUS 8

// Naudojamas duomenu iraso tipas, kurio reikalauja uzduoties salygos
struct Begikas {
    char vardas[MAX_VARDO_ILGIS];
    // unsigned prierasas pazymi kad skaitinis duomenu tipas negali tureti zemesniu nei 0 reiksmiu kintamajame (x >= 0)
    unsigned int laikas;
};

// Naudojamas duomenu iraso tipas, kurio reikalauja uzduoties salygos
struct Takelis {
    Begikas begikai[MAX_BEGIKU_SKAICIUS];
    size_t begikuKiekis;
};

bool uzkrautiDuomenis(const char* failoAdresas, Takelis(& duomenys)[MAX_TAKELIU_SKAICIUS], size_t& duomenuIlgis);
bool issaugotiDuomenis(const char* failoAdresas, Takelis(& duomenys)[MAX_TAKELIU_SKAICIUS], const size_t duomenuIlgis);

int main() {
    Takelis duomenys[MAX_TAKELIU_SKAICIUS];
    size_t duomenuIlgis;
    if (!uzkrautiDuomenis("U2.txt", duomenys, duomenuIlgis)) return 1;
    return !issaugotiDuomenis("U2rez.txt", duomenys, duomenuIlgis);
}

bool uzkrautiDuomenis(const char* failoAdresas, Takelis(& duomenys)[MAX_TAKELIU_SKAICIUS], size_t& duomenuIlgis) {
    std::ifstream failas(failoAdresas);
    if (!failas.is_open() || !(failas >> duomenuIlgis) || duomenuIlgis > MAX_TAKELIU_SKAICIUS) return false;
    for (size_t i = 0; i < duomenuIlgis; i++) {
        if (!(failas >> duomenys[i].begikuKiekis) || duomenys[i].begikuKiekis > MAX_BEGIKU_SKAICIUS) return false;
        // Pries simboliu isgavima per failas.get(), butina naudoti failas.ignore(), norint skaityti MAX_VARDAS_ILGIS simbolius is kitos eilutes.
        failas.ignore();
        for (size_t j = 0; j < duomenys[i].begikuKiekis; j++) {
            // Isgaunam pirmus MAX_VARDO_ILGIS simbolius per failas.get()
            failas.get(duomenys[i].begikai[j].vardas, MAX_VARDO_ILGIS);
            // unsigned prierasas pazymi kad skaitinis duomenu tipas negali tureti zemesniu nei 0 reiksmiu kintamajame (x >= 0)
            unsigned int mins, sek;
            // Jeigu nepavyko isgauti reiksmiu, nebekraunam duomenu nes duomenys neteisingi.
            if (!(failas >> mins >> sek)) return false;
            // Paverciam minutes ir sekundes tiesiog i sekundes, kadangi juos bus lengviau manipuliuoti sekundemis.
            duomenys[i].begikai[j].laikas = mins * 60 + sek;
            // Po simboliu isgavimo per failas.get(), butina naudoti failas.ignore(), norint skaityti kitus MAX_VARDAS_ILGIS simbolius is kitos eilutes.
            failas.ignore();
        }
    }
    return true;
}

// Issaugant duomenis naudojamas insertion sort algoritmas surikiuoti duomenis pagal reikalavimus.
bool issaugotiDuomenis(const char* failoAdresas, Takelis(& duomenys)[MAX_TAKELIU_SKAICIUS], const size_t duomenuIlgis) {
    // Jeigu duomenys neatitinka reikalavimu, neissaugom.
    if (duomenuIlgis > MAX_TAKELIU_SKAICIUS) return false;
    std::ofstream failas(failoAdresas);
    // Jeigu failas neatidarytas, nera ka saugoti.
    if (!failas.is_open()) return false;
    // MAX_TAKELIU_SKAICIUS*MAX_BEGIKU_SKAICIUS lygus tiek kiek galima maksimaliai tureti begiku duomenyse.
    Begikas* rezultatas[MAX_TAKELIU_SKAICIUS*MAX_BEGIKU_SKAICIUS];
    size_t l = 0;
    for (size_t i = 0; i < duomenuIlgis; i++) {
        // Jeigu duomenys neatitinka reikalavimu, net neskaiciuojam.
        if (duomenys[i].begikuKiekis > MAX_BEGIKU_SKAICIUS) return false;
        rezultatas[l] = &(duomenys[i].begikai[0]);
        //Surusiuojam tam tikro takelio begikus nuo maziausio iki didziausio (Insertion Sort).
        for (size_t j = 1; j < duomenys[i].begikuKiekis; j++) {
            int k = j+l-1;
            while (k > -1 && duomenys[i].begikai[j].laikas < rezultatas[k]->laikas) {
                rezultatas[k+1] = rezultatas[k];
                k--;
            }
            rezultatas[k+1] = &(duomenys[i].begikai[j]);
        }
        // Kad nereiketu naudoti daug masyvu, naudojam indeksa, kuris leis mums perrasyti masyvo nereikalingus duomenis.
        // Masyve lieka pirmos puses takelio rezultatai, o kita puse yra perrasoma kitu takeliu informacija.
        l+= duomenys[i].begikuKiekis / 2;

    }
    //Surusiuojam atrinktus greiciausius begikus nuo maziausio iki didziausio (Insertion Sort rikiavimas dar karta).
    for (size_t i = 1; i < l; i++) {
        Begikas* begikas = rezultatas[i];
        int j = i-1;
        while (j > -1 && begikas->laikas < rezultatas[j]->laikas) {
            rezultatas[j+1] = rezultatas[j];
            j--;
        }
        rezultatas[j+1] = begikas;
    }
    // Issaugom gautus duomenis i faila
    for (size_t i = 0; i < l; i++) {
        int mins = rezultatas[i]->laikas / 60;
        int sek = rezultatas[i]->laikas - mins * 60;
        failas << rezultatas[i]->vardas << ' ' << mins << ' ' << sek;
        if (i != l-1) failas << '\n';
    }
    return true;
}
