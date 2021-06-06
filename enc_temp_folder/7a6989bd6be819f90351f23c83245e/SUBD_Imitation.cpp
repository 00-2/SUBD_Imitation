// SUBD_Imitation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include "Header3.h"
#include "Header2.h"
#include <filesystem>
#include <fstream>
#include <iomanip>

namespace fs = std::filesystem;

enum Commands {
    Option_Invalid,
    show,
    create,
    use,
    drop,
    renamer,
};
Commands resolveOption(std::string input) {
    if (input == "show") return show;
    if (input == "create") return create;
    if (input == "use") return use;
    if (input == "drop") return drop;
    if (input == "rename") return renamer;
    return Option_Invalid;
}


void showDatabases() {//показать список баз данных

    std::string path = fs::current_path().u8string()+"/db";

    for (const auto& entry : fs::directory_iterator(path))
        std::cout << entry.path().filename() << std::endl;
}
void createDatabase(std::string s) {//создать базу данных
    std::string path = fs::current_path().u8string() + "\\db\\";
    path += s;
    std::ofstream file(path);
    std::string data("");
    file << data;
    file.close();
}
void dropDatabase(std::string path) {//удалить базу данных
    fs::remove(path);
}
void renameDatabase(std::string path) {//переименовать базу данных
    std::string s; std::cout << "\nInsert new name:"; std::cin >> s; s = fs::current_path().u8string() + "\\db\\" + s;
    fs::rename(path,s);
}
void appendRecord(std::string data, std::string path) {//добавить запись
    std::ofstream file(path, std::ios_base::app);
    file << data;
    file.close();
}   
bool exist(std::string filename) {
    std::string path = fs::current_path().u8string() + "/db";
    for (const auto& entry : fs::directory_iterator(path))
    {
        if (entry.path().filename() == filename) {
            return true;
        }
    }
    return false;
}
std::vector<StorageOfClothes> selectAll(std::string path) {
    std::ifstream in(path);
    std::string line;
    int id = 0;
    std::vector<StorageOfClothes> dataRes;//представление db
    while (std::getline(in, line))
    {
        std::istringstream iss(line);
        char type;
        unsigned int capacity;
        std::string city,name;
        if (!(iss >> type >>name>> city >> capacity)) { break; } // error
        StorageOfClothes tmpSOC(name,city, capacity);
        if (type == 'c') {
            Clothes tmpObject;
            std::vector<Clothes> data;
            while (iss >> tmpObject.size >> tmpObject.height) {
                data.push_back(tmpObject);
            }
            tmpSOC.setData(data);
        }
        else {
            Clothes tmpObject;
            std::vector<Clothes> data;
            while (iss >> tmpObject.size) {
                tmpObject.height = -1;
                data.push_back(tmpObject);
            }
            tmpSOC.setData(data);
        }
        dataRes.push_back(tmpSOC);
    }
    return dataRes;
}
void writeAll(std::vector<StorageOfClothes> data) {
    std::cout<<std::setw(3) << "\nID "
        << std::setw(8) << "type"
        << std::setw(8) << "name"
        << std::setw(8) << "capacity"
        << std::setw(8) << "city"
        << std::setw(6) << "size"
        << std::setw(8) << "height"
        << std::endl;
    for (int i = 0; i < data.size(); i++) {
        std::vector<Clothes> tmpV = data[i].getData();
        std::string type;
        if (tmpV.size()>0 && tmpV[0].height != -1) {
            type = "clothing";
        }
        else {
            type = "boots";
        }
        for (int j = 0; j < tmpV.size(); j++) {
            std::cout<< std::setw(3) <<i<<"."<<j << std::setw(8) << type
                << std::setw(8) << data[i].getName()
                << std::setw(8) << data[i].getCapacity()
                << std::setw(8) << data[i].getCity()
                << std::setw(6) << tmpV[j].size
                << std::setw(8) << tmpV[j].height
                << std::endl;
        }
    }
}
void menu() {
    std::cout << "\n\n----------------\n\tHello, username\n\nTo create new DB enter\"create <db name>\"\n\nToShow list of DB enter\"show databases\"\n\nToShow DB enter\"use <db name>\"\n\nToUse DB enter \"use <db name>\"\n\nToDrop DB enter \"drop <db name>\"\n\nToRenameDb enter \"rename <db name>\"\n\n ";
    std::string s;
    std::getline(std::cin,s);
    std::vector<std::string> VecStr;
    std::istringstream ss(s);
    std::string String;
    while (ss >> String)
        VecStr.push_back(String);
    try
    {
        switch (resolveOption(VecStr[0]))
        {
        case show:
            if (VecStr.size() == 2 && VecStr[1] == "databases") {
                showDatabases();
                break;
            }
            else{
                std::cout << "\nCommand was not responced";
            }
        case create:
            if (VecStr.size() == 2) {
                createDatabase(VecStr[1]);
            }
            else {
                std::cout << "\nCommand was not responced";
            }
            break;

        case use:
            if (VecStr.size()==2){
                if (exist(VecStr[1])) {
                    std::string dbInUse = VecStr[1];//аргумент - название файла
                    std::cout << "\n\tinsert \"exit\" to exit\n \"add\" to add data in " + VecStr[1] + "\n\"remove\" to remove record from " + VecStr[1] + "\n\"select\" to show data from " + VecStr[1] + "\n";
                    std::string command = "";
                    std::cin >> command;
                    while (command != "exit") {
                        if (command == "add") {
                            std::cout << "\nclassification - insert (0(for boots)/1(for clothing)) ";
                            std::string classification = "-1";
                            std::cin >> classification;
                            while (classification != "0" && classification != "1") {
                                std::cout << "\nclassification - insert (0(for boots)/1(for clothing)) ";
                                std::cin >> classification;
                            }
                            std::string city,name;
                            unsigned int capacity;
                            std::cout << "Insert name:"; std::cin >> name;
                            std::cout << "Insert city:"; std::cin >> city;
                            std::cout << "Insert capacity:"; std::cin >> capacity;
                            int n; std::cout << "How many records u want add? "; std::cin >> n;
                            if (classification == "1") {
                                StorageOfClothes sOC(name, city, capacity); //добавляем склад одежды
                                for (int i = 0; i < n; i++) {
                                    sOC.add();
                                }
                                std::cout << sOC.toString();
                                appendRecord(sOC.toString(), fs::current_path().u8string() + "\\db\\" + VecStr[1]);
                            }
                            else {
                                StorageOfBoots sOB(name, city, capacity); //добавляем склад обуви
                                for (int i = 0; i < n; i++) {
                                    sOB.add();
                                }
                                std::cout << sOB.toString();
                                appendRecord(sOB.toString(), fs::current_path().u8string() + "\\db\\" + VecStr[1]);
                            }
                            std::string data;
                        }
                        else if (command == "remove") {
                            int count;
                            std::string city;
                            unsigned int capacity;
                            std::string path = fs::current_path().u8string() + "\\db\\" + VecStr[1];
                            auto dataRes = selectAll(path);
                            writeAll(dataRes);
                            std::cout << "\ninsert attributes(city, capacity) of storage:\ncity:"; std::cin >> city; std::cout << "\ncapacity:"; std::cin >> capacity;
                            for (int i = 0; i < dataRes.size(); i++) {
                                if (dataRes[i].getCapacity() == capacity && dataRes[i].getCity() == city) {
                                    dataRes.erase(dataRes.begin() + i);
                                    break;
                                }
                            }
                        }
                        else if (command == "select") {
                            std::string describe;
                            std::string path = fs::current_path().u8string() + "\\db\\" + VecStr[1];
                            std::cout << "\n* - show all\n1-show 1\n2-show 2";
                            std::cin >> describe;
                            if (describe == "*") {
                                writeAll(selectAll(path));
                            }
                        }
                        else if (command == "count") {
                            std::string path = fs::current_path().u8string() + "\\db\\" + VecStr[1];
                            auto dataRes = selectAll(path);
                            writeAll(dataRes);
                            int count;
                            std::string name; std::cout << "Insert name"; std::cin >> name;
                            for (int i = 0; i < dataRes.size(); i++) {
                                if (dataRes[i].getName() == name) {
                                    count = dataRes[i].count();
                                }
                            }
                            std::cout << std::to_string(count) + " - count of products in storage\"" + name + "\"";
                        }
                        std::cout << "\n\tinsert \"exit\" to exit\n \"add\" to add data in " + VecStr[1] + "\n\"remove\" to remove record from " + VecStr[1] + "\n\"select\" to show data from " + VecStr[1] + "\n\"count\" to get count of product in storage in db" + VecStr[1] + "\n";
                        std::cin >> command;
                    }
                }
                else {
                    std::cout << "\nDB doesn't exist";
                }
            }
            else {
                std::cout << "\nCommand was not responced";
            }
            break;

        case drop:
            if (VecStr.size() == 2) {
                if (exist(VecStr[1])) {
                    dropDatabase(fs::current_path().u8string() + "\\db\\" + VecStr[1]);
                }
            }
            else {
                std::cout << "\nCommand was not responced";
            }
            break;

        case renamer:
            if (VecStr.size() == 2) {
                if (exist(VecStr[1])) {
                    renameDatabase(fs::current_path().u8string() + "\\db\\" + VecStr[1]);
                }
            }
            else {
                std::cout << "\nCommand was not responced";
            }
            break;

        default:
            break;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }
   
}

int main()
{
    std::cout << "Greetings From Your's new SUBD";
    std::string path = fs::current_path().u8string() + "\\db\\db2.txt";
    //writeAll(selectAll(path));
    while(true)menu();
    //StorageOfClothes sOB("Barbara",1);
    //sOB.add();
    //sOB.add();
    //sOB.out();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
