#include <fstream>
#include <limits>

#define MAX_FLOWERS 30

bool loadData(const char* path, int data[], int& dataSize);
bool saveData(const char* path, int resultData[]);
void calculateData(int data[], int dataSize, int resultData[]);


int main()
{
    int data[MAX_FLOWERS*4];
    int dataSize;
    if (!loadData("U1.txt", data, dataSize)) return 1;
    int resultData[5];
    calculateData(data, dataSize, resultData);
    return !saveData("U1rez.txt", resultData);
}

/*
 * Nesaugios funkcijos! Kadangi C/C++ kalbos netikrina masyvu, gali ivykti buffer overflow,
 * bet kadangi uzduotys yra hardcoded, del to galima nesirupinti.
 */


bool loadData(const char* path, int data[], int& dataSize) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    stream >> dataSize;
    /*
     * Mums geliu numerio nereikia, tai kodel ji laikyti atmintyje.
     * Nemaciau tokiu geliu, kurios zydi kelis sezonus, o gal tiesiog i lauka per mazai iseinu :D
     */
    dataSize *= 4;
    for (int i = 0; i < dataSize;) {
        /*
         * Reikia praleisti kazkaip pirma reiksme, kuri nereikalinga. Galima ja perasyti i kita kintamaji ir nenaudoti arba
         * galima naudoti tai: stream.ignore(std::numeric_limits<streamsize>::max(), ' '). Si funkcija praleis viska iki pirmo
         * pasitaikiusio tarpo.
         */
        stream >> data[i] >> data[i++] >> data[i++] >> data[i++] >> data[i++] ;
    }
    // Destruktorius uzdaro failo saltini, nes stream objektas yra lokalus kintamasis, kuris iseina is funkcijos.
    return true;
}

bool saveData(const char* path, int resultData[]) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    stream << resultData[0] << "\n" << resultData[1] << " " << resultData[2] << "\n" << resultData[3] << " " << resultData[4];
    // Destruktorius uzdaro failo saltini, nes stream objektas yra lokalus kintamasis, kuris iseina is funkcijos.
    return true;

}

void calculateData(int data[], int dataSize, int resultData[]) {
    resultData[0] = 0;
    for (int i = 0; i < dataSize; ) {
        int range1StartMonth = data[i++],
            range1StartDay= data[i++],
            range1EndMonth = data[i++],
            range1EndDay = data[i++];

        int counter = 0;

        // Ieskom kitu intervalu atitikmenu siam intervalui auksciau
        for (int j = 0; j < dataSize;) {
            int range2StartMonth = data[j++],
                range2StartDay = data[j++],
                range2EndMonth = data[j++],
                range2EndDay = data[j++];
            /* Tikrinam ar intervalas pilnai ieina i kita intervala.
             if (range2StartMonth <= range1StartMonth && range2EndMonth >= range1EndMonth && range2StartDay <= range1StartDay && range2EndDay <= range1EndDay) {
                counter++;
             }
             * Sitas apacioje turetu but pagal viska greitesnis, nes jis prideda viena
             * salyga tikrinancia ar menesiai skirtingi, jei skirtingi, kiti tikrinimai nereikalingi,
             * nes jau ir taip aisku, kad ieis i intervala. Sioje vietoje geriausiai butu suskaldyti conditionus i booleanus.
             */
            if (range2StartMonth < range1StartMonth && range2EndMonth > range1EndMonth || range2StartMonth == range1StartMonth && range2EndMonth == range1EndMonth && range2StartDay <= range1StartDay && range2EndDay <= range1EndDay) {
                counter++;
            }
        }
        /*
         * Jei apskaiciuota intervalu reiksme yra didesne, reiskiasi, kad reiksme tuo
         * metu yra didziausia ir reikia keisti reiksmes
         */
        if (counter > resultData[0]) {
            resultData[0] = counter;
            resultData[1] = range1StartMonth;
            resultData[2] = range1StartDay;
            resultData[3] = range1EndMonth;
            resultData[4] = range1EndDay;
        }
    }
}
