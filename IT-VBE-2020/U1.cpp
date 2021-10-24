#include <fstream>

bool loadData(const char* path, int data[]);
bool saveData(const char* path, int data[]);
int calculateData(int data[], int dataSize);

static const int indexMap[] = {0,30,61};

int main() {
    int data[92] = {};
    if (!loadData("U1.txt", data)) return 1;
    return !saveData("U1rez.txt", data);
}

bool loadData(const char* path, int data[]) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    int dataSize;
    stream >> dataSize;
    for (int i = 0; i < dataSize; i++) {
        stream.ignore(INT_MAX, ' ');
        int buffer, j, k;
        stream >> j >> buffer;
        j = indexMap[j-6] + buffer - 1;
        stream >> k >> buffer;
        k = indexMap[k-6] + buffer;
        while (j < k) data[j++]++;
    }
    return true;
}

bool saveData(const char* path, int data[]) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    int sInterval = calculateData(data, 92);
    stream << data[sInterval];
    int eInterval = sInterval;
    while (data[eInterval] == data[sInterval]) eInterval++;
    int sIndex = (++sInterval)/31, eIndex = eInterval/31; // Sie kintamieji yra menesiu santykiai nuo 0 iki 2. Juos naudojam isgauti menesio dienas bei menesius.
    stream << '\n' << sIndex+6 << ' ' << sInterval-indexMap[sIndex] << '\n' << eIndex+6 << ' ' << eInterval-indexMap[eIndex];
    return true;
}

// Sukurkite ir parasykite funkcija, kuri randa pirmos dienos,
// kai zydi daugiausia geliu, vieta vasaros dienu sarase.
int calculateData(int data[], int dataSize) {
    int biggest = 0;
    for (int i = 0; i < dataSize; i++)
        if (data[i] > data[biggest]) biggest = i;
    return biggest;
}
