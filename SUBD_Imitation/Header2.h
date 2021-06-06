#include "Header1.h"

struct Boots
{
    int size;
};

class StorageOfBoots : public Storage
{

public:
    StorageOfBoots(std::string t_name,std::string t_city,unsigned int t_capacity)
        : Storage(name,t_city, t_capacity)
    {
    }
    int add() {
        std::cout << "\nAdding into StorageOfBoots";
        if (this->data.size() < capacity) {
        Boots tmp;
        std::cout << "\nInsert Size:"; std::cin >> tmp.size;
        std::cin;
        this->data.push_back(tmp);
        return 1;
        }
        std::cout << "\nStorage Full";
        return 0;
    }
    std::string toString() {
        std::string s = "\nb "+this->name + " " + this->city + " " + std::to_string(this->capacity) + " ";
        for (int i = 0; i < this->data.size(); i++) {
            s += std::to_string(this->data[i].size);
        }
        s += "\n";
        return s;
    }

protected:
    std::vector<Boots> data;
};