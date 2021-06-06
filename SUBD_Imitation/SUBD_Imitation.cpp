// SUBD_Imitation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include "Header3.h"
#include "Header2.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

enum Commands {
    Option_Invalid,
    show,
    create,
};
Commands resolveOption(std::string input) {
    if (input == "show") return show;
    if (input == "create") return create;
    return Option_Invalid;
}


void showDatabases() {

    std::string path = fs::current_path().u8string()+"/db";

    for (const auto& entry : fs::directory_iterator(path))
        std::cout << entry.path().filename() << std::endl;
}
void createDatabase(std::string s) {
    std::string path = fs::current_path().u8string() + "\\db\\";
    path += s;
    
    std::ofstream file(path);
    std::string data("");
    file << data;
    file.close();
}

void appendRecord(std::string data, std::string path) {
    std::ofstream file(path, std::ios_base::app);
    file << data;
    
}

void menu() {
    std::cout << "\n\nHello, username\n\nTo create new DB enter\"create <db name>\"\n\nToShow list of DB enter\"show databases\"\n\nToShow DB enter\"show database <db name>\"\n\n";
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
            if (VecStr.size() == 3 && VecStr[1] == "database") {
                //вывести бд
                break;
            }
            else if (VecStr.size() == 2 && VecStr[1] == "databases") {
                showDatabases();
                break;
            }
            else{
                std::cout << "Command was not responced";
            }
        case create:
            if (VecStr.size() == 2) {
                createDatabase(VecStr[1]);
            }
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
    menu();
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
