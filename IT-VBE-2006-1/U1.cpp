#include <cmath>
#include <fstream>

#define MAX_RESISTANCE_CHAINS 100
#define MAX_PARALLEL_CIRCUITS 50


bool loadData(const char* path, int data[], int& dataSize);
bool saveData(const char* path, double resultData);
double calculateData(int data[], int dataSize);

int main()
{
    int data[MAX_PARALLEL_CIRCUITS * MAX_RESISTANCE_CHAINS];
    int dataSize;

    if (!loadData("Duom1.txt", data, dataSize)) return 1;
    double resultData = calculateData(data, dataSize);
    return !saveData("Rez1.txt", resultData);
}

double calculateData(int data[], int dataSize) {
    double generalResistance = 0;
    for (int i = 0; i < dataSize; i++) {
        double chainResistance = 0;
        int amount = data[i];
        for (int j = 0; j < amount; j++) {
            chainResistance += 1.d / data[++i];

        }
        generalResistance += 1.d / chainResistance;

    }
    return round(generalResistance * 100.d) / 100.d;
}

bool loadData(const char* path, int data[], int& dataSize) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    dataSize = 0;

    int streamSize;
    stream >> streamSize;
    for (int i = 0; i < streamSize; i++) {
        int index = dataSize++;

        stream >> data[index];
        for (int j = 0; j < data[index]; j++) {
            stream >> data[dataSize++];
        }
    }
    return true;
}

bool saveData(const char* path, double resultData) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    stream << resultData;
    return true;
}
