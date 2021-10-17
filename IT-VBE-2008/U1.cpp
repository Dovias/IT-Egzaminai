#include <fstream>
#include <iomanip>

bool loadData(const char* path, int data[]);
bool saveData(const char* path, int data[]);
int calculateData(int data[]);

int main() {
    // Rasydami programa naudokite tik vienmacius sveikuju skaiciu masyvus. (Naudojam viena vienmati masyva)
    int data[100*3] = {};

    if (!loadData("U1.txt", data)) return false;
    return !saveData("U1rez.txt", data);
}

bool loadData(const char* path, int data[]) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    // Parasykite procedura duomenims is failo skaityti.
    int dataSize;
    stream >> dataSize;
    for (int i = 0; i < dataSize; i++) {
        int index, buffer;
        stream >> index >> buffer;
        data[index-1] = index;
        if (buffer > 0) {
            data[index+99] += buffer;
        } else {
            data[index+199] += buffer;
        }
    }
    return true;
}

bool saveData(const char* path, int data[]) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    // Parasykite procedura tik marsrutu numeriams spausdinti didejimo tvarka.
    for (int i = 0; i < 100; i++) {
        if (data[i] == 0) continue;
        stream << std::setw(6) << data[i];
    }
    // Procedura skirta tik marsruto duomenims skaityti (Nurodymuose nera sito)
    for (int i = 100; i < 201; i+=100) {
        stream << '\n';
        for (int j = 0; j < 100; j++) {
            if (data[j] == 0) continue;
            stream << std::setw(6) << data[i+j];
        }
    }
    stream << '\n' << std::setw(6) << calculateData(data);
    return true;
}

// Parasykite funkcija marsruto, kuriuo vezta daugiausia keleiviu, numeriui rasti.
int calculateData(int data[]) {
    int index = 100;
    for (int i = 100; i < 201; i++) {
        if (data[i] > data[index]) {
            index = i;
        }
    }
    return data[index-100];
}
