#pragma once
#include <string>
#include <vector>
#include <iostream>

class Storage // это абстрактный родительский класс
{
protected:
    std::string name;
    std::string city;
    unsigned int capacity;
public:
    Storage(std::string t_name,std::string t_city, unsigned int t_capacity)
    {
        this->name = t_name;
        this->city = t_city;
        this->capacity = t_capacity;
    }
    std::string getCity() { return this->city; }
    std::string getName() { return this->name; }

    unsigned int getCapacity() { return this->capacity; }

    virtual int add() = 0; //виртуальная функция добавления записи
    virtual std::string toString() = 0;//виртуальная функция визуализации склада

};
