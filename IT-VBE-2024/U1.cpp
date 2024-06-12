// Pastebejimas: Sita uzduotis butu labai lengva su set'ais ar map'ais jeigu
// neprasytu isskirti atskiros funkcijos apskaiciavimui. Gal cia as per daug stipriai ziuriu i taisykles...
// Labai slykstus sprendimas!!

#include <fstream>
#include <iomanip>

using namespace std;

struct KrepsininkoDuomenys {
  int numeris;

  int pataikytos_baudos;
  int mestos_baudos;

  int pataikyti_dvitaskiai;
  int mesti_dvitaskiai;

  int pataikyti_tritaskiai;
  int mesti_tritaskiai;
};

struct KrepsininkoEfektyvumas {
  int numeris;

  int rungtyniu_skaicius = 0;
  double tasku_vidurkis = 0;
  double taiklumas = 0;
};

// Sukurkite funkcija, kuri apskaiciuoja turnyro metu zaidejo suzaistu rungtyniu
// skaiciu, per rungtynes surinktu tasku vidurki ir pataikytu bei mestu metimu
// santyki procentais.
KrepsininkoEfektyvumas apskaiciuoti_krepsininko_efektyvuma(KrepsininkoDuomenys * duomenys, int duomenu_kiekis, int krepsininko_numeris) {
  KrepsininkoEfektyvumas efektyvumas;
  efektyvumas.numeris = krepsininko_numeris;

  int mesti = 0;
  int pataikyti = 0;
  for (int i = 0; i < duomenu_kiekis; i++) {
    if (duomenys[i].numeris != krepsininko_numeris) {
      continue;
    }
    
    efektyvumas.rungtyniu_skaicius++;
    efektyvumas.tasku_vidurkis += duomenys[i].pataikytos_baudos +
                                  duomenys[i].pataikyti_dvitaskiai * 2 +
                                  duomenys[i].pataikyti_tritaskiai * 3;

    mesti += duomenys[i].mestos_baudos
      + duomenys[i].mesti_dvitaskiai
      + duomenys[i].mesti_tritaskiai;
    
    pataikyti += duomenys[i].pataikytos_baudos
      + duomenys[i].pataikyti_dvitaskiai
      + duomenys[i].pataikyti_tritaskiai;
  }

  efektyvumas.tasku_vidurkis /= efektyvumas.rungtyniu_skaicius;
  efektyvumas.taiklumas = ((double)pataikyti) / mesti;
  return efektyvumas;
}

int main() {
  ifstream nuskaitymas("U1.txt");

  int krepsininku_duomenu_skaicius;
  nuskaitymas >> krepsininku_duomenu_skaicius;

  // nuskaitom i struktura
  KrepsininkoDuomenys * krepsininku_duomenys = new KrepsininkoDuomenys[krepsininku_duomenu_skaicius];
  for (int i = 0; i < krepsininku_duomenu_skaicius; i++) {
    nuskaitymas
      >> krepsininku_duomenys[i].numeris
      >> krepsininku_duomenys[i].pataikytos_baudos
      >> krepsininku_duomenys[i].mestos_baudos
      >> krepsininku_duomenys[i].pataikyti_dvitaskiai
      >> krepsininku_duomenys[i].mesti_dvitaskiai
      >> krepsininku_duomenys[i].pataikyti_tritaskiai
      >> krepsininku_duomenys[i].mesti_tritaskiai;
  }

  KrepsininkoEfektyvumas * krepsininku_efektyvumas = new KrepsininkoEfektyvumas[krepsininku_duomenu_skaicius];
  int krepsininku_kiekis = 0;

  int didziausias_krepsininko_rungtyniu_skaicius = 0;
  for (int i = 0; i < krepsininku_duomenu_skaicius; i++) {
    // patikrinam ar krepsininko efektyvumas jau buvo apskaiciuotas (cia set'as labai sueitu, bet tikrinam ranka)
    bool apskaiciuotas_krepsininko_efektyvumas = false;
    for (int j = 0; j < krepsininku_kiekis; j++) {
      if (krepsininku_duomenys[i].numeris ==
          krepsininku_efektyvumas[j].numeris) {
        apskaiciuotas_krepsininko_efektyvumas = true;
      }
    }

    if (apskaiciuotas_krepsininko_efektyvumas) {
      continue;
    }

    krepsininku_efektyvumas[krepsininku_kiekis++] = apskaiciuoti_krepsininko_efektyvuma(krepsininku_duomenys, krepsininku_duomenu_skaicius, krepsininku_duomenys[i].numeris);

    int krepsininko_rungtyniu_skaicius = krepsininku_efektyvumas[i].rungtyniu_skaicius;
    if (krepsininko_rungtyniu_skaicius > didziausias_krepsininko_rungtyniu_skaicius) {
      didziausias_krepsininko_rungtyniu_skaicius = krepsininko_rungtyniu_skaicius;
    }
  }
  delete[] krepsininku_duomenys;

  // israsom i faila
  ofstream israsymas("U1rez.txt");
  
  israsymas << didziausias_krepsininko_rungtyniu_skaicius << '\n';
  for (int i = 0; i < krepsininku_kiekis; i++) {
    // patikrinam ar krepsininko rungtynio skaicius sutampa su didziausiu rungtyniu skaiciumi
    if (krepsininku_efektyvumas[i].rungtyniu_skaicius !=
        didziausias_krepsininko_rungtyniu_skaicius) {
      continue;
    }

    israsymas << krepsininku_efektyvumas[i].numeris << ' '
         << fixed << setprecision(1) << krepsininku_efektyvumas[i].tasku_vidurkis << ' '
         << setprecision(0) << krepsininku_efektyvumas[i].taiklumas * 100 << " %\n";
  }
  delete[] krepsininku_efektyvumas;
  
  israsymas << flush;
}
