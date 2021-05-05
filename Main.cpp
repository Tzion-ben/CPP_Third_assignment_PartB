#include "NumberWithUnits.hpp"
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <chrono>
#include <thread>
#include <sstream>
#include <fstream>


using namespace ariel;
using namespace std;

int main (){
    ifstream myfile("filename.txt");
    NumberWithUnits::read_units(myfile);

    NumberWithUnits a(7, "r_ILS");
    NumberWithUnits b(7, "r_ILS");
    NumberWithUnits c(7, "r_ILS");
    // istringstream iss{" -16 [r_m]   -7 [r_hour ]  8.8 [r_min ]"};

    // iss >> a >> b >> c;
    
    // cout << "a:" << a <<"\n";
    // cout << "b:" << b <<"\n";
    // cout << "c:" << c <<"\n";


    NumberWithUnits d(7, "r_ILS");
    NumberWithUnits e(7, "r_ILS");
    NumberWithUnits f(7, "r_ILS");
    istringstream iss{" 8 [   r_EUR     ]   -1 [r_school ] 29.7 [r_halfMin ]"};

    iss >> d >> e >> f;
    
    cout << "d:" << d <<"\n";
    cout << "e:" << e <<"\n";
    cout << "f:" << f <<"\n";

    return 0;
}