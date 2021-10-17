#include <fstream>

struct BusStop {
    char name[21];
    int routeAmount;
    // Is stoteles yra 99 galimos kitos stoteles, kur galima sustoti (Is dabartines stoteles i dabartine stotele nevaziuosi :D)
    bool routes[99] = {};
};

bool loadData(const char* path, BusStop busData[], int& busDataSize, int routeData[]);
bool saveData(const char* path, BusStop busData[], int busDataSize, int targetRoute);
int calculateData(int destData[]);

int main() {
    // Rasydami programa naudokite masyvus su iraso tipo elementais. Papildomai gali buti naudojami ir kitokio tipo masyvai.
    BusStop busData[100];
    int busDataSize;
    int routeData[100] = {};

    if (!loadData("U2.txt", busData, busDataSize, routeData)) return true;
    return !saveData("U2rez.txt", busData, busDataSize, calculateData(routeData));
}

bool loadData(const char* path, BusStop busData[], int& busDataSize, int routeData[]) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    stream >> busDataSize;
    // Parasykite procedura, skirta tik duomenims skaityti is failo.
    for (int i = 0; i < busDataSize; i++) {
        stream.ignore();
        stream.get(busData[i].name, 21);
        stream >> busData[i].routeAmount;
        for (int j = 0; j < busData[i].routeAmount; j++) {
            int buffer;
            stream >> buffer;
            busData[i].routes[buffer-1] = true;
            // Papildomai gali buti naudojami ir kitokio tipo masyvai. (Pernaudojam cikla, kada nereiktu sukti dar kart)
            routeData[buffer-1] += 1;
        }
    }
    return true;
}

bool saveData(const char* path, BusStop busData[], int busDataSize, int targetRoute) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    stream << targetRoute;
    // Parasykite procedura, kuri spausdintu i tekstini faila nurodyto marsruto stoteliu pavadinimus.
    for (int i = 0; i < busDataSize; i++) {
        if (busData[i].routes[targetRoute-1]) {
            stream << '\n' << busData[i].name;
        }
    }
    return true;
}

// Parasykite funkcija ilgiausio marsruto numeriui rasti.
int calculateData(int routeData[]) {
    int biggest = -1;
    for (int i = 0; i < 100; i++) {
        if (routeData[i] > biggest) {
            biggest = routeData[i];
        }
    }
    return biggest+1;
}
