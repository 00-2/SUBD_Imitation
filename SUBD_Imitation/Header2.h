#include "Header1.h"

struct Boots
{
    int size;
};

class StorageOfBoots : public Storage
{

public:
    StorageOfBoots(std::string t_city,unsigned int t_capacity)
        : Storage(t_city, t_capacity)
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
    int out() {
            std::cout << "\n";
            for (int i = 0; i < this->data.size(); i++) {
                std::cout << data[i].size << " ";
            }
            return 1;        
    }
protected:
    std::vector<Boots> data;
};