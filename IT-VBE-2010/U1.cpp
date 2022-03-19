#include <fstream>

#define MAX_STUDENT_AMOUNT 100

bool loadData(const char* path, int(& data)[MAX_STUDENT_AMOUNT]);
bool saveData(const char* path, int(& data)[MAX_STUDENT_AMOUNT]);
int calculateData(int (& data)[MAX_STUDENT_AMOUNT]);

int main() {
    int data[MAX_STUDENT_AMOUNT];
    if (!loadData("U1.txt", data)) return 1;
    return !saveData("U1rez.txt", data);
}

bool loadData(const char* path, int(& data)[MAX_STUDENT_AMOUNT]) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    int dataSize = 0;
    while (stream >> data[dataSize++]) {}
    return true;
}

bool saveData(const char* path, int(& data)[MAX_STUDENT_AMOUNT]) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    stream << calculateData(data);
    return true;
}

// Parasykite funkcija, kuri skaiciuotu, kiek sachmatu komplektu galima sudaryti is mokiniu atnestu baltu figuru.
int calculateData(int(& data)[MAX_STUDENT_AMOUNT]) {
    static int chessTable[6] = {8, 2, 2, 2, 1, 1};

    int addedData[6] = {};
    for (int i = 1; i < data[0] * 6 + 1; i++) {
        addedData[(i-1) % 6] += data[i];
    }
    int result = INT_MAX;
    for (int i = 0; i < 6; i++) {
        int amount = addedData[i] / chessTable[i];
        if (amount < result) result = amount;
    }
    return result;
}
