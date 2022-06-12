#include <fstream>
#include <cstring>

#define MAX_PAVADINIMO_ILGIS 20+1+1 // +20 - pratimo pavadinimas, +1 tarpo simbolis, += nematomas \0 simbolis
#define MAX_PRATIMU_KIEKIS 100

struct Pratimas {
    char pavadinimas[MAX_PAVADINIMO_ILGIS];
    unsigned int kartai;
};

bool uzkrautiDuomenis(const char* failoAdresas, Pratimas(& duomenys)[MAX_PRATIMU_KIEKIS], size_t& duomenuIlgis);
bool issaugotiDuomenis(const char* failoAdresas, Pratimas(& duomenys)[MAX_PRATIMU_KIEKIS], const size_t duomenuIlgis);
void apdorotiDuomenis(Pratimas(& duomenys)[MAX_PRATIMU_KIEKIS], const size_t duomenuIlgis, Pratimas* rezultatai[MAX_PRATIMU_KIEKIS]);

int main() {
    Pratimas duomenys[MAX_PRATIMU_KIEKIS];
    size_t duomenuIlgis;
    if (!uzkrautiDuomenis("U2.txt", duomenys, duomenuIlgis)) return 1;
    return !issaugotiDuomenis("U2rez.txt", duomenys, duomenuIlgis);
}

// Uzkraunam duomenis ir iskarto surusiuojam ir sudedam visus pavadinimus bei kartus i ju vienerius objektus.
bool uzkrautiDuomenis(const char* failoAdresas, Pratimas(& duomenys)[MAX_PRATIMU_KIEKIS], size_t& duomenuIlgis) {
    std::ifstream failas(failoAdresas);
    size_t pradinisDuomenuIlgis;
    if (!failas.is_open() || !(failas >> pradinisDuomenuIlgis)) return false;
    // Pries simboliu isgavima per failas.get(), butina naudoti failas.ignore(), norint skaityti MAX_PAVADINIMAS_ILGIS simbolius is kitos eilutes.
    failas.ignore();
    
    duomenuIlgis = 0;
    for (size_t i = 0; i < pradinisDuomenuIlgis; i++) {
        // Isgaunam pirmus MAX_PAVADINIMO_ILGIS simbolius per failas.get()
        failas.get(duomenys[i].pavadinimas, MAX_PAVADINIMO_ILGIS);
        if (!(failas >> duomenys[i].kartai)) return false;
        duomenuIlgis++;
        // Tikrinam kitus irasus, kurie galbut sutampa su dabartiniais nuskaitytais duomenimis
        for (size_t j = 0; j < i; j++) {
            // Patikrinam ar pavadinimas su pastaraisiais irasais sutampa, jeigu nesutampa ignoruojam praeita reiksme.
            if (strcmp(duomenys[j].pavadinimas, duomenys[i].pavadinimas) != 0) continue;
            // Pazymim kad sitas irasas nera pagrindinis irasas, kur yra sudeti visi kartai.
            // \0 simbolis neleis strcmp() funkcijai rasti sutapimu su kitais nuskaitytais pavadinimais.
            duomenys[i].pavadinimas[0] = '\0';
            // Pridedam nuskaitytus kartus prie pagrindinio pratimo iraso objekto.
            duomenys[j].kartai += duomenys[i].kartai;
            
            // Kadangi nuskaitytas objektas nera unikalus, turim atimti is duomenu ilgio vieneta, kadangi pradzioje,
            // manyta kad tai yra unikalus objektas bei buvo pridetas vienetas. Jeigu tai butu unikalus objektas
            // pavadinimai nesutaptu su kitu nuskaitytu irasu, kas siuo metu sutapo sioje vietoje. Tai leidzia
            // isgauti tikraji pratimu skaiciu, o ne irasu skaiciu duota uzduoties faile.
            duomenuIlgis--;
            break;
        }
        // Po simboliu isgavimO per failas.get(), butina naudoti failas.ignore(), norint skaityti MAX_PAVADINIMAS_ILGIS simbolius is kitos eilutes.
        failas.ignore();
    }
    return true;
}

bool issaugotiDuomenis(const char* failoAdresas, Pratimas(& duomenys)[MAX_PRATIMU_KIEKIS], const size_t duomenuIlgis) {
    if (duomenuIlgis > MAX_PRATIMU_KIEKIS) return false;
    std::ofstream failas(failoAdresas);
    if (!failas.is_open()) return false;

    Pratimas* rezultatai[MAX_PRATIMU_KIEKIS];
    // Panaudojam pasirasyta funkcija surikiuoti objektus issaugojimui faile.
    apdorotiDuomenis(duomenys, duomenuIlgis, rezultatai);
    for (size_t i = 0; i < duomenuIlgis; i++) {
        failas << rezultatai[i]->pavadinimas << rezultatai[i]->kartai;
        // Jeigu tai yra paskutiniai duomenys, nauja eilute faile nera butina, todel
        // pridedam naujos eilutes simboli tik kada jo reikia.
        if (i != duomenuIlgis-1) failas << '\n';
    }
    return true;
}

// Insertion sort algoritmas rikiavimo funkcijai. Funkcija reikalauta uzduoties salygose.
void apdorotiDuomenis(Pratimas(& duomenys)[MAX_PRATIMU_KIEKIS], const size_t duomenuIlgis, Pratimas* rezultatai[MAX_PRATIMU_KIEKIS]) {
    if (duomenuIlgis > MAX_PRATIMU_KIEKIS) return;
    rezultatai[0] = &(duomenys[0]);
    for (size_t i = 1; i < duomenuIlgis; i++) {
        int j = i-1;
        // 1. Tikrinam ar reiksme yra didesne uz praeita reiksme masyve
        // 2. Jeigu tuometine reiksme yra didesne uz pastaraja, nustumiam ja i masyvo pradzia.
        // 3. Jeigu tuometine reiksme yra lygi pastarajai, tikrinam su strcmp() funkcija ar pavadinimas
        // prasideda zemesnio indekso raide ('a' < 'b'), jeigu taip, taip pat nustumiam strukturos objekta
        // arciau masyvo pradzios.
        while (
           j > -1 && (duomenys[i].kartai > rezultatai[j]->kartai ||
          (duomenys[i].kartai == rezultatai[j]->kartai &&
           strcmp(duomenys[i].pavadinimas, rezultatai[j]->pavadinimas) < 0))
        ) {
            rezultatai[j+1] = rezultatai[j];
            j--;
        }
        rezultatai[j+1] = &(duomenys[i]);
    }
}

