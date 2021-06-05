#include "Header1.h"

class Boots
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
protected:
    std::vector<Boots> data;
};