#pragma once
#include <string>
#include <vector>
#include <iostream>

class Storage // это абстрактный родительский класс
{
protected:
    std::string city;
    unsigned int capacity;
public:
    Storage(std::string t_city, unsigned int t_capacity)
    {
        this->city = t_city;
        this->capacity = t_capacity;
    }
    std::string getCity() { return this->city; }
    unsigned int getCapacity() { return this->capacity; }
    virtual int add() = 0; //виртуальная функция добавления записи
    virtual std::string toString() = 0;//виртуальная функция визуализации склада

};
