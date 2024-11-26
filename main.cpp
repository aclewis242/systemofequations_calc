#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "SystemsOfEquations.hpp"

using namespace std;

int main(){
    while(true){
        SystemsOfEquations* sys = new SystemsOfEquations();
        cout << "If you would like to exit, please type 'exit.' Otherwise, type something else." << endl;
        string ex = "";
        cin >> ex;
        if(ex=="exit"){
            break;
        }
    }
}
