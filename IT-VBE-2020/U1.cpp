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
    return true;
}

bool saveData(const char* path, int resultData[]) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    stream << resultData[0] << "\n" << resultData[1] << " " << resultData[2] << "\n" << resultData[3] << " " << resultData[4];
    return true;

}

void calculateData(int data[], int dataSize, int resultData[]) {
    resultData[0] = 0;
    for (int i = 0; i < dataSize; ) {
        /*
         * Galima naudoti naujas C++17 inline tipo funkcijas, bet tikriausiai neveiks egzamine nes dar vis standartas C++11
         * Taip pat siuos datu konvertavimus galima perkelti i loadData() funkcija, bet tada reikia papildomai juos saugoti
         * greta datu nes reikia datu failo irasymui.
         */

        int range1Start = (data[i++] == 6 ? 30 : 31) + data[i++];
        int range1End = (data[i++] == 6 ? 30 : 31) + data[i++];
        int counter = 0;

        // Ieskom kitu intervalu atitikmenu siam intervalui auksciau
        for (int j = 0; j < dataSize;) {
            int range2Start = (data[j++] == 6 ? 30 : 31) + data[j++];
            int range2End = (data[j++] == 6 ? 30 : 31) + data[j++];
            // Tikrinam ar intervalas pilnai ieina i kita intervala
            if (range2Start >= range1Start && range2End <= range1End) {
                counter++;
            }
        }
        /*
         * Jei apskaiciuota intervalu reiksme yra didesne, reiskiasi, kad reiksme tuo
         * metu yra didziausia ir reikia keisti reiksmes
         */
        if (counter > resultData[0]) {
            resultData[0] = counter;
            resultData[1] = data[i-4];
            resultData[2] = data[i-3];
            resultData[3] = data[i-2];
            resultData[4] = data[i-1];
        }
    }
}
