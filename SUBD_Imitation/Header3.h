#include "Header1.h"

class Clothes
{
    int height;
    int size;
};

class StorageOfClothes : public Storage
{

public:
    StorageOfClothes (std::string t_city, unsigned int t_capacity)
        : Storage(t_city, t_capacity)
    {
    }
protected:
    std::vector<Clothes> data;
};