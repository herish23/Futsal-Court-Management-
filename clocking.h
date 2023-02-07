
#ifndef CLOCKING_H
#define CLOCKING_H
#include<iostream>
#include <ctime>


#include<string>

using namespace std;


class clocking {

public:

    time_t now = time(0);
    tm* ltm = localtime(&now);
    time_t current = time(0);

    string plat = "20" + to_string(ltm->tm_year - 99) + "-" + to_string(ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday - 1);
    string platex1 = "20" + to_string(ltm->tm_year - 99) + "-" + to_string(ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday - 1);//extra year 2024;

    string tommorow = "20" + to_string(ltm->tm_year - 100) + "-" + "" + to_string(ltm->tm_mon+1) + "-" + "" + to_string(ltm->tm_mday);
    string time1 = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);

    string gold = "20" + to_string(ltm->tm_year - 99) + "-" + to_string(ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday - 1);
    string goldex1 = "20" + to_string(ltm->tm_year - 99) + "-" + to_string(ltm->tm_mon +1) + "-" + to_string(ltm->tm_mday - 1);




};
#endif

