#include <fstream>
#include <cstring>

#define MAX_STUDENT_AMOUNT 50

#define MAX_STUDENT_NAME 40
#define MAX_SUBJECT_NAME 40
#define MAX_STUDENT_GRADES 50

struct StudentData {
    char firstName[MAX_STUDENT_NAME];
    char subjectName[MAX_SUBJECT_NAME];

    int studentGrades[MAX_STUDENT_GRADES];
    int studentsGradesSize;

    bool found = false;
};

struct SubjectData {
    StudentData* studentData[MAX_STUDENT_AMOUNT];
    int studentDataSize = 0;
};

bool loadData(const char* path, StudentData data[], int& dataSize);
bool saveData(const char* path, SubjectData resultData[], int resultDataSize);
void calculateData(StudentData data[], int dataSize, SubjectData resultData[], int& resultDataSize);
void sortData(SubjectData data[], int dataSize);

int main() {
    StudentData data[MAX_STUDENT_AMOUNT];
    int dataSize;
    if (!loadData("U2.txt", data, dataSize)) return 1;

    SubjectData resultData[MAX_STUDENT_AMOUNT];
    int resultDataSize;
    calculateData(data, dataSize, resultData, resultDataSize);

    sortData(resultData, resultDataSize);

    return saveData("U2Rez.txt", resultData, resultDataSize);

}

bool loadData(const char* path, StudentData data[], int& dataSize) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    stream >> dataSize;
    for (int i = 0; i < dataSize; i++) {
        StudentData studentData;
        stream >> studentData.firstName >> studentData.subjectName >> studentData.studentsGradesSize;
        for (int j = 0; j < studentData.studentsGradesSize; j++) {
            stream >> studentData.studentGrades[j];
        }
        data[i] = studentData;
    }
    // Destruktorius uzdaro failo saltini, nes stream objektas yra lokalus kintamasis, kuris iseina is funkcijos.
    return true;
}

bool saveData(const char* path, SubjectData resultData[], int resultDataSize) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    if (resultDataSize == 0) {
        stream << "Neatitinka vidurkis";
        return false;
    }
    for (int i = 0; i < resultDataSize; i++) {
        stream << resultData[i].studentData[0]->subjectName << " " << resultData[i].studentDataSize << "\n";

        for (int j = 0; j < resultData[i].studentDataSize; j++) {
            stream << resultData[i].studentData[j]->firstName << "\n";
        }

    }
    // Destruktorius uzdaro failo saltini, nes stream objektas yra lokalus kintamasis, kuris iseina is funkcijos.
    return true;

}

void calculateData(StudentData data[], int dataSize, SubjectData resultData[], int& resultDataSize) {
    resultDataSize = 0;
    for (int i = 0; i < dataSize; i++) {
        //Pazymetus kaip jau surastus objektus nebeieskoti per naujo, nes jie jau yra masyve per kitus iterationus.
        if (data[i].found) {
            data[i].found = false;
            continue;
        }
        SubjectData subjectData;
        for (int j = i; j < dataSize; j++) {
            if (strcmp(data[i].subjectName, data[j].subjectName) != 0) {
                continue;
            }
            data[j].found = true;
            int average = 0;
            for (int k = 0; k < data[j].studentsGradesSize; k++) {
                average += data[j].studentGrades[k];
            }
            if (average / data[j].studentsGradesSize < 9) {
                continue;
            }
            subjectData.studentData[subjectData.studentDataSize++] = &data[j];
        }
        if (subjectData.studentDataSize != 0) {
            resultData[resultDataSize++] = subjectData;
        }
    }
}

// Insertion sort algoritmas rusiuojantis duomenis pagal dydi.
void sortData(SubjectData data[], int dataSize) {
    for (int i = 1; i < dataSize; i++) {
        for (int j = 0; j < i; j++) {
            if (data[i].studentDataSize > data[i].studentDataSize) {
                continue;
            }
            SubjectData temp = data[i];
            for (int k = i+1; --k > j;) {
                data[k] = data[k-1];
            }
            data[j] = temp;
        }
    }
}
