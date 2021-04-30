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
    ifstream myfile("tempTest.txt");
    NumberWithUnits::read_units(myfile);
   
    

    return 0;
}