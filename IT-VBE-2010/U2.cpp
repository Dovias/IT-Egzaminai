#include <fstream>

#define MAX_PRODUCT_AMOUNT 10
#define MAX_DISH_AMOUNT 12
#define MAX_DISH_NAME 15 + 1

struct Dish {
    char name[MAX_DISH_NAME];
    int products[MAX_PRODUCT_AMOUNT];
    struct DishSet* dishSet;

    int calculateData();
};

struct DishSet {
    Dish dishes[MAX_DISH_AMOUNT];
    int productCosts[MAX_PRODUCT_AMOUNT];
    size_t dishAmount, productAmount;

    int calculateData();
};

bool loadData(const char* path, DishSet& data);
bool saveData(const char* path, DishSet& data);

int main() {
    DishSet data;
    if (!loadData("U2.txt", data)) return 1;
    return !saveData("U2rez.txt", data);
}

bool loadData(const char* path, DishSet& data) {
    std::ifstream stream(path);
    if (!stream.is_open()) return false;
    stream >> data.productAmount >> data.dishAmount;
    for (size_t i = 0; i < data.productAmount; i++) {
        stream >> data.productCosts[i];
    }
    for (size_t i = 0; i < data.dishAmount; i++) {
        stream.ignore();
        stream.get(data.dishes[i].name, sizeof(data.dishes[i].name));
        for (size_t j = 0; j < data.productAmount; j++) {
            stream >> data.dishes[i].products[j];
        }
        data.dishes[i].dishSet = &data;
    }
    return true;
}

bool saveData(const char* path, DishSet& data) {
    std::ofstream stream(path);
    if (!stream.is_open()) return false;
    for (size_t i = 0; i < data.dishAmount; i++) {
        stream << data.dishes[i].name << data.dishes[i].calculateData() << '\n';
    }
    int cents = data.calculateData();
    int lt = cents / 100;
    cents -= lt * 100;
    stream << lt << ' ' << cents;
    return true;
}

// Parasykite funkcija, kuri suskaiciuotu vieno patiekalo kaina centais.
int Dish::calculateData() {
    int sum = 0;
    for (size_t i = 0; i < this->dishSet->productAmount; i++) {
        sum += this->products[i] * this->dishSet->productCosts[i];
    }
    return sum;
}

/* Parasykite funkcija, kuri suskaiciuotu vieno svecio pietu kaina centais.
 * Visiskai nereikalinga funkcija, bereikalingas ciklo sukimas, mes vistiek
 * israsinejam patiekalu kainas atskirai. */
int DishSet::calculateData() {
    int sum = 0;
    for (size_t i = 0; i < this->dishAmount; i++) {
        sum += this->dishes[i].calculateData();
    }
    return sum;
}
