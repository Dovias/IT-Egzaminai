#include <fstream>
#include <string>

// Programoje naudokite duomenu tipo strukturos masyva apklaustu mokiniu duomenims saugoti.
struct Subject {
    // Naudojame std::string, nes vardu dydziai nezinomi.
    std::string name;
    std::string students[50];
    int sAmount = 0;
};

bool loadData(const char* path, Subject data[], int& dataSize);
bool saveData(const char* path, Subject data[], int dataSize);
void sortData(Subject data[], int dataSize, Subject* sortData[]);

int main() {
    Subject data[50];
    int dataSize;
    if (!loadData("U2.txt", data, dataSize)) return 1;
    return !saveData("U2rez.txt", data, dataSize);
}

bool loadData(const char* path, Subject data[], int& dataSize) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    int fileDataSize;
    stream >> fileDataSize;
    dataSize = 0;
    for (int i = 0; i < fileDataSize; i++) {
        int gradeAmount;
        int gradeAvg = 0;
        stream >> data[dataSize].students[0] >> data[dataSize].name >> gradeAmount;
        data[dataSize].sAmount = 1;
        for (int j = 0; j < gradeAmount; j++) {
            int grade;
            stream >> grade;
            gradeAvg += grade;
        }
        if (gradeAvg / gradeAmount < 9) continue;
        for (int j = dataSize-1; j > -1; j--) {
            if (data[j].name == data[dataSize].name) {
                data[j].students[data[j].sAmount++] = data[dataSize].students[0];
                dataSize--;
                break;
            }
        }
        dataSize++;
    }
    return true;
}

bool saveData(const char* path, Subject data[], int dataSize) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    if (dataSize == 0) {
        stream << "Neatitinka vidurkis";
    } else {
        Subject* sortedData[dataSize];
        sortData(data, dataSize, sortedData);
        // Nesvarus isspausdinimas, reikia sugalvoti geresni buda isvengti papildomo \n gale.
        stream << sortedData[0]->name << ' ' << sortedData[0]->sAmount;
        for (int j = 0; j < sortedData[0]->sAmount; j++) {
            stream << '\n' << sortedData[0]->students[j] ;
        }
        for (int i = 1; i < dataSize; i++) {
            stream << '\n' << sortedData[i]->name << ' ' << sortedData[i]->sAmount;
            for (int j = 0; j < sortedData[i]->sAmount; j++) {
                stream << '\n' << sortedData[i]->students[j] ;
            }
        }
    }
    return true;
}


// Sukurkite ir parasykite funkcija, kuri surikiuotu populiariausiu dalyku sarasa. (Insertion sort algoritmas)
void sortData(Subject data[], int dataSize, Subject* sData[]) {
    sData[0] = &data[0];
    for (int i = 0; i < dataSize; i++) {
        int j = i-1;
        while (j >= 0 && (data[i].sAmount > sData[j]->sAmount || data[i].sAmount == data[j].sAmount && data[i].name < data[j].name)) {
            sData[j+1] = sData[j];
            j--;
        }
        sData[j+1] = &data[i];
    }
}
