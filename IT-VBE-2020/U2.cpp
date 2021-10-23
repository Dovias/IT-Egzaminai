#include <fstream>
#include <cstring>

struct Pair {
    char key[21];
    int value = 0;
};

bool loadData(const char* path, Pair data[], int& fmDataSize, int& fDataSize);
bool saveData(const char* path, Pair data[], int fmDataSize, int fDataSize);
void sortData(Pair data[], int dataSize, Pair* sData[]);

int main() {
    Pair data[30+30];
    int fmDataSize, fDataSize;
    if (!loadData("U2.txt", data, fmDataSize, fDataSize)) return 1;
    return !saveData("U2rez.txt", data, fmDataSize, fDataSize);
}

bool loadData(const char* path, Pair data[], int& fmDataSize, int& fDataSize) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    stream >> fmDataSize;
    Pair fData[fmDataSize*5];
    for (int i = 0; i < fmDataSize; i++) {
        stream.ignore();
        stream.get(data[i].key, 21);
        int k;
        stream >> k;
        k += i*5;
        for (int j = i*5; j < k; j++) {
            stream.ignore();
            stream.get(fData[j].key, 21);
            stream >> fData[j].value;
        }
    }
    stream >> fDataSize;
    for (int i = fmDataSize; i < fmDataSize+fDataSize; i++) {
        stream.ignore();
        stream.get(data[i].key, 21);
        stream >> data[i].value;
        int mass = 0;
        for (int j = 0; j < fmDataSize*5; j++) {
            if (strcmp(data[i].key, fData[j].key) == 0) {
                data[j/5].value += data[i].value + (fData[j].value < 200 ? 10 : 30);
                mass += fData[j].value;
            }
        }
        data[i].value = mass;
    }
    return true;
}

bool saveData(const char* path, Pair data[], int fmDataSize, int fDataSize) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    stream << "Dalyviai";
    Pair* sData[30+30];
    sortData(data, fmDataSize, sData);
    for (int i = 0; i < fmDataSize; i++)
        stream << '\n' << sData[i]->key << sData[i]->value;
    stream << "\nLaimikis";
    sortData(&data[fmDataSize], fmDataSize+fDataSize, &sData[fmDataSize]);
    for (int i = fmDataSize; i < fmDataSize+fDataSize; i++)
        stream << '\n' << sData[i]->key << sData[i]->value;
    return true;
}

// Parasykite funkcija, kuri rikiuoja duota sarasa pagal skaicius mazejanciai.
// Jeigu skaiciai vienodi - pagal simboliu eilute abeceliskai. (Insertion sort algoritmas)
void sortData(Pair data[], int dataSize, Pair* sData[]) {
    sData[0] = &data[0];
    for (int i = 0; i < dataSize; i++) {
        int j = i-1;
        while (j >= 0 && (data[i].value > sData[j]->value || data[i].value == data[j].value && strcmp(data[i].key, sData[j]->key) < 0)) {
            sData[j+1] = sData[j];
            j--;
        }
        sData[j+1] = &data[i];
    }
}
