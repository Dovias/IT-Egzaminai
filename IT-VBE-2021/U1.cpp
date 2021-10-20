#include <fstream>

bool loadData(const char* path, int data[], int& dataSize);
bool saveData(const char* path, int data[], int dataSize);
int calculateData(int hrMin, int minsMin, int hrMax, int minsMax);

int main() {
    int data[31*9];
    int dataSize;
    if (!loadData("U1.txt", data, dataSize));
    return !saveData("U1rez.txt", data, dataSize);
}

bool loadData(const char* path, int data[], int& dataSize) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    stream >> dataSize;
    dataSize *= 9;
    for (int i = 0; i < dataSize; i++) {
        stream >> data[i];
    }
    return true;
}

bool saveData(const char* path, int data[], int dataSize) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    int lowest = INT_MAX, dDataSize;
    int dData[dataSize/9];
    for (int i = 0; i < dataSize; i+=9) {
        int eTime = calculateData(data[i+5], data[i+6], data[i+7], data[i+8]);
        int mTime = calculateData(data[i+1], data[i+2], data[i+3], data[i+4]);
        if (mTime == 0 || eTime == 0) continue;
        int time = mTime + eTime;
        if (time < lowest) {
            lowest = time;
            dData[0] = data[i];
            dDataSize = 1;
        } else if (time == lowest) {
            dData[dDataSize++] = data[i];
        }
    }
    stream << "Minimalus laikas\n" << lowest << "\nDienos\n" << dData[0];
    for (int i = 1; i < dDataSize; i++)
        stream << ' ' << dData[i];
    return true;
}

// Sukurkite ir parasykite funkcija, kuri apskaiciuoja, kiek laiko (minutemis) Laurynas sugaiso begimui.
int calculateData(int hrMin, int minsMin, int hrMax, int minsMax) {
    return (hrMax*60+minsMax)-(hrMin*60+minsMin);
}
