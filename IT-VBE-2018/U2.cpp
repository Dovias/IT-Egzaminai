#include <fstream>
#include <cstring>

#define MAX_VARDO_ILGIS 20+1
#define MAX_SLIDININKU_KIEKIS 30
#define DISKVALIFIKACIJOS_RODIKLIS 3600

struct Slidininkas {
    char vardas[MAX_VARDO_ILGIS];
    unsigned int uztruko;
};

bool uzkrautiDuomenis(const char* failoAdresas, Slidininkas(& duomenys)[MAX_SLIDININKU_KIEKIS], size_t& duomenuIlgis);
bool issaugotiDuomenis(const char* failoAdresas, Slidininkas(& duomenys)[MAX_SLIDININKU_KIEKIS], const size_t duomenuIlgis);
void apdorotiDuomenis(Slidininkas(& duomenys)[MAX_SLIDININKU_KIEKIS], const size_t duomenuIlgis, Slidininkas* rezultatai[MAX_SLIDININKU_KIEKIS]);

int main() {
    Slidininkas duomenys[MAX_SLIDININKU_KIEKIS];
    size_t duomenuIlgis;
    if (!uzkrautiDuomenis("U2.txt", duomenys, duomenuIlgis)) return 1;
    return !issaugotiDuomenis("U2rez.txt", duomenys, duomenuIlgis);
}

// Uzkraunam duomenis ir sudedam visa slidininku informacij i ju atskirus objektus.
bool uzkrautiDuomenis(const char* failoAdresas, Slidininkas(& duomenys)[MAX_SLIDININKU_KIEKIS], size_t& duomenuIlgis) {
    std::ifstream failas(failoAdresas);
    // Jeigu nebuvo sekmingai nuskaityti duomenys, nustojam uzkrauti duomenis, nes duomenys faile neegzistuoja ar nera teisingi.
    if (!failas.is_open() || !(failas >> duomenuIlgis)) return false;

    failas.ignore();
    for (size_t i = 0; i < duomenuIlgis; i++) {
        // Isgaunam pirmus MAX_VARDO_ILGIS simbolius per failas.get()
        failas.get(duomenys[i].vardas, MAX_VARDO_ILGIS);
        unsigned int val, mins, sek;
        
        // Jeigu nebuvo sekmingai nuskaityti laiko duomenys, nustojam uzkrauti duomenis, nes duomenys nera teisingi.
        if (!(failas >> val >> mins >> sek)) return false;
        // Apskaiciuojam sekundziu   tarp finiso ir pradzios laiko.
        duomenys[i].uztruko = val * 3600  + mins * 60 + sek;
        // Pries simboliu isgavima per failas.get(), butina naudoti failas.ignore(), norint skaityti MAX_VARDO_ILGIS simbolius is kitos eilutes.
        failas.ignore();
    }
    size_t fDuomenuIlgis;
    if (!(failas >> fDuomenuIlgis)) return false;
    // Po simboliu isgavimo per failas.get(), butina naudoti failas.ignore(), norint skaityti MAX_VARDO_ILGIS simbolius is kitos eilutes.
    failas.ignore();
    for (size_t i = 0; i < fDuomenuIlgis; i++) {
        char vardas[MAX_VARDO_ILGIS];
        unsigned int val, mins, sek;

        // Isgaunam pirmus MAX_VARDO_ILGIS simbolius per failas.get()
        failas.get(vardas, MAX_VARDO_ILGIS);
        if (!(failas >> val >> mins >> sek)) return false;
        for (size_t j = 0; j < duomenuIlgis; j++) {
            // Patikrinam ar pavadinimas su pastaraisiais irasais sutampa, jeigu nesutampa ignoruojam praeita reiksme.
            if (strcmp(vardas, duomenys[j].vardas) != 0) continue;
            // Apskaiciuojam sekundziu   tarp finiso ir pradzios laiko.
            duomenys[j].uztruko = val * 3600 + mins * 60 + sek - duomenys[j].uztruko;
            break;
        }
        // Po simboliu isgavimo per failas.get(), butina naudoti failas.ignore(), norint skaityti MAX_VARDO_ILGIS simbolius is kitos eilutes.
        failas.ignore();
    }
    return true;
}

bool issaugotiDuomenis(const char* failoAdresas, Slidininkas(& duomenys)[MAX_SLIDININKU_KIEKIS], const size_t duomenuIlgis) {
    // Jeigu nurodytas duomenu ilgis yra didesnis nei nurodytas limitas, reiskia, kad duomenys nera teisingi.
    if (duomenuIlgis > MAX_SLIDININKU_KIEKIS) return false;
    std::ofstream failas(failoAdresas);
    // Patikrinam ar failas yra atidarytas bei paruostas duomenu rasymui is atminties.
    if (!failas.is_open()) return false;
    Slidininkas* rezultatai[MAX_SLIDININKU_KIEKIS];
    // Rikiuojam duomenis naudojant rikiavimo funkcija parasyta zemiau.
    apdorotiDuomenis(duomenys, duomenuIlgis, rezultatai);
    for (size_t i = 0; i < duomenuIlgis; i++) {
        // Jeigu slidininkas uztruko ilgiau nei DISKVALIFIKACIJOS_RODIKLIS, reiskiasi, kad jis neieis i sarasa faile.
        if (rezultatai[i]->uztruko > DISKVALIFIKACIJOS_RODIKLIS) continue;
        int mins = rezultatai[i]->uztruko / 60;
        int sek = rezultatai[i]->uztruko - mins * 60;
        failas << rezultatai[i]->vardas << mins << ' ' << sek;
        // Jeigu tai yra paskutiniai duomenys, nauja eilute faile nera butina, todel
        // pridedam naujos eilutes simboli tik kada jo reikia
        if (i < duomenuIlgis-1) failas << '\n';
    }
    return true;
}

// Insertion sort algoritmas rikiavimo funkcijai. Funkcija reikalauta uzduoties salygose.
void apdorotiDuomenis(Slidininkas(& duomenys)[MAX_SLIDININKU_KIEKIS], const size_t duomenuIlgis, Slidininkas* rezultatai[MAX_SLIDININKU_KIEKIS]) {
    if (duomenuIlgis > MAX_SLIDININKU_KIEKIS) return;
    rezultatai[0] = &(duomenys[0]);
    for (size_t i = 1; i < duomenuIlgis; i++) {
        int j = i-1;
        // 1. Tikrinam ar reiksme yra didesne uz praeita reiksme masyve
        // 2. Jeigu tuometine reiksme yra didesne uz pastaraja, nustumiam ja i masyvo pradzia.
        // 3. Jeigu tuometine reiksme yra lygi pastarajai, tikrinam su strcmp() funkcija ar pavadinimas
        // prasideda zemesnio indekso raide ('a' < 'b'), jeigu taip, taip pat nustumiam strukturos objekta
        // arciau masyvo pradzios.
        while (
           j > -1 && (duomenys[i].uztruko < rezultatai[j]->uztruko ||
          (duomenys[i].uztruko == rezultatai[j]->uztruko &&
           strcmp(duomenys[i].vardas, rezultatai[j]->vardas) < 0))
        ) {
            rezultatai[j+1] = rezultatai[j];
            j--;
        }
        rezultatai[j+1] = &(duomenys[i]);
    }
}
