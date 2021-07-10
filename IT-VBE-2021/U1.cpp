#include <fstream>
#include <limits>

#define MAX_DAYS 31

int loadData(const char* path, int data[], int& dataSize);
int saveData(const char* path, int resultData[], int resultDataSize);
void calculateData(int data[], int dataSize, int resultData[], int& resultDataSize);

int main()
{
    int data[MAX_DAYS*9];
    int dataSize;
    if (!loadData("U1.txt", data, dataSize)) return 1;
    int resultData[1+MAX_DAYS];
    int resultDataSize;
    calculateData(data, dataSize, resultData, resultDataSize);
    return !saveData("U1rez.txt", resultData, resultDataSize);
}


int loadData(const char* path, int data[], int& dataSize) {
    std::ifstream stream(path);
    if (!stream.is_open()) return 0;
    stream >> dataSize;
    dataSize *= 9;
    for (int i = 0; i < dataSize; i++) {
        stream >> data[i];
    }
    // Destruktorius uzdaro failo saltini, nes stream objektas yra lokalus kintamasis, kuris iseina is funkcijos.
    return 1;
}

int saveData(const char* path, int resultData[], int resultDataSize) {
    std::ofstream stream(path);
    if (!stream.is_open()) return 0;
    stream << "Minimalus laikas\n" << resultData[0] << "\nDienos\n";
    stream << resultData[1];
    for (int i = 2; i < resultDataSize; i++) {
        stream << " " << resultData[i];
    }
    // Destruktorius uzdaro failo saltini ir iraso tuo paciu momentu i faila, nes stream objektas yra lokalus kintamasis, kuris iseina is funkcijos.
    return 1;
}

void calculateData(int data[], int dataSize, int resultData[], int& resultDataSize) {
    resultData[0] = std::numeric_limits<int>::max();
    resultDataSize = 0;
    for (int i = 0; i < dataSize; i++) {
        int day = data[i];
        int morningTime = (data[++i]*60 + data[++i]) - (data[++i]*60 + data[++i]);
        int eveningTime = (data[++i]*60 + data[++i]) - (data[++i]*60 + data[++i]);
        if (morningTime == 0 || eveningTime == 0) continue;

        int overallTime = (morningTime < 0 ? -morningTime : morningTime) + (eveningTime < 0 ? -eveningTime : eveningTime);
        if (overallTime < resultData[0]) {
            resultData[0] = overallTime;
            resultData[1] = day;
            resultDataSize = 2;
        } else if (overallTime == resultData[0]) {
            resultData[resultDataSize++] = day;
        }
    }
}
