#include "Header1.h"

struct Clothes
{
    int height;
    int size;
};

class StorageOfClothes : public Storage
{

public:
    StorageOfClothes (std::string t_name, std::string t_city, unsigned int t_capacity)
        : Storage(t_name, t_city, t_capacity)
    {
    }
    int count() {
        return data.size();
    }
    int add() {
        std::cout << "\nAdding into StorageOfClothes";
        if (this->data.size() < capacity) {
            Clothes tmp;
            std::cout << "\nInsert Height:"; std::cin >> tmp.height;
            std::cout << "\nInsert Size:"; std::cin >> tmp.size;
            std::cin;
            this->data.push_back(tmp);
            return 1;
        }
        std::cout << "\nStorage Full";
        return 0;
    }
    std::string toString() {
        std::string s = "\nc " + this->name + " " + this->city + " " + std::to_string(this->capacity)+ " ";
        for (int i = 0; i < this->data.size(); i++) {
            s += std::to_string(this->data[i].size) + " " + std::to_string(this->data[i].height);
        }
        s += "\n";
        return s;
    }
    void setData(std::vector<Clothes> tmpData) {
        this->data = tmpData;
    }
    std::vector<Clothes> getData() {
        return this->data;
    }
protected:
    std::vector<Clothes> data;
};