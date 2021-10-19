#include <fstream>

bool loadData(const char* path, int data[]);
bool saveData(const char* path, int data[]);
int calculateData(int data[]);

int main() {
    int data[3] = {};
    if (!loadData("U1.txt", data)) return false;
    return !saveData("U1rez.txt", data);
}

bool loadData(const char* path, int data[]) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    int dataSize;
    stream >> dataSize;
    for (int i = 0; i < dataSize; i++) {
        char letter;
        stream >> letter;
        int amount;
        stream >> amount;
        // Iseina perfect hash. R, G, Z ASCII reiksmes isideda i skirtingus indeksus.
        data[letter % 3] += amount;
    }
    return true;
}

bool saveData(const char* path, int data[]) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    int amount = calculateData(data);
    stream << amount << '\n';
    amount *= 2;
    stream << "G = " << data[2]-amount << "\nZ = " << data[0]-amount << "\nR = " << data[1]-amount;
    return true;
}

// Sukurkite ir parasykite funkcija, kuri suskaiciuoti, kiek buvo suklijuota veliaveliu.
int calculateData(int data[]) {
    // Ternary operatoriai, nelabai gerai nestinti juos, bet kadangi cia 3 indeksai tik todel taip darau.
    int lowest = data[0] < data[1] ? (data[0] < data[2] ? data[0] : data[2]) : (data[1] < data[2] ? data[1] : data[2]);
    return lowest / 2;
}
