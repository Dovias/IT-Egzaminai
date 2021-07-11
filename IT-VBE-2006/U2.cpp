#include <fstream>
#include <cmath>

#define MAX_STOP_AMOUNT 100
#define MAX_STOP_NAME 15

struct BusStop {
    char name[MAX_STOP_NAME];
    float distance;

    int arrivalTime = 0;
};

struct Bus {
    float avgSpeed;
    int departureTime, busStopAmount;
    BusStop busStops[MAX_STOP_AMOUNT];
};

bool loadData(const char* path, Bus& data);
bool saveData(const char* path, Bus& data);
void calculateData(Bus& data);
int calculateTime(float distance, float velocity);

int main()
{
    Bus data;
    if (!loadData("Duom2.txt", data)) return 1;
    calculateData(data);
    return !saveData("Rez2.txt", data);
}

bool loadData(const char* path, Bus& data) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    stream >> data.busStopAmount >> data.avgSpeed >> data.departureTime;

    // Pasiverciam automatiskai isvykimo laika i minutes
    data.departureTime *= 60;
    int temp;
    stream >> temp;
    data.departureTime += temp;

    // kadangi .get() metodas nepersoksta new line simbolio automatiskai, tenka ji persokti rankiniu budu su .ignore() metodu.
    stream.ignore();
    for (int i = 0; i < data.busStopAmount; i++) {
        BusStop stop;
        //Isgaunam 15 poziciju is failo saltinio
        stream.get(stop.name, MAX_STOP_NAME);
        stream >> stop.distance;
        data.busStops[i] = stop;
        // kadangi .get() metodas nepersoksta new line simbolio automatiskai, tenka ji persokti rankiniu budu su .ignore() metodu.
        stream.ignore();
    }
    return true;
    // Uzdaryti nereikia, nes tai daro destruktorius kai iseina is funkcijos.
}

bool saveData(const char* path, Bus& data) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    for (int i = 0; i < data.busStopAmount; i++) {
        // Galima padaryti tapati su dalyba ir modulus operatoriumi,
        // bet as megstu taip rasyti, nes tada bent matosi, ka tu darai su skaiciais.
        int hour = data.busStops[i].arrivalTime / 60;
        int mins = data.busStops[i].arrivalTime - hour * 60;

        stream << data.busStops[i].name << hour << " val. " << mins << "min.\n";
    }
    return true;
    // Uzdaryti nereikia, nes tai daro destruktorius kai iseina is funkcijos.
}

// Galima deklaruoti sita funkcija strukturoj, bet del lengvesnio suprantamumo ja palieku labiau globalioj vietoj.
void calculateData(Bus& data) {
    int overallDistance = 0;
    for (int i = 0; i < data.busStopAmount; i++) {
        overallDistance += data.busStops[i].distance;
        // Pridedam isvykimo laika prie apskaiciuoto laiko is visos tuo metu sukauptos distancijos bei autobuso greicio.
        data.busStops[i].arrivalTime = data.departureTime + calculateTime(overallDistance, data.avgSpeed);
    }
}

// Nereikalinga funkcija, bet reikalauja praktine uzduotis..
int calculateTime(float distance, float velocity) {
    return round(distance / velocity * 60);
}
