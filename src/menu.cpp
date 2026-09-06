#include <iostream>
#include <cstdlib>
#include <limits>

#include "menu.hpp"

int displayMenu(void){
    int opc = 0;

    do{ 
    system("clear");
    
    std::cout<<"╔══════════════════════════════════════════════╗"<<std::endl;
    std::cout<<"║         C++ To Do List Manager               ║"<<std::endl;
    std::cout<<"╚══════════════════════════════════════════════╝"<<std::endl;
    std::cout<<"                                                "<<std::endl;
    std::cout<<"  [1] Create a task                             "<<std::endl;
    std::cout<<"  [2] Read task/s                               "<<std::endl;
    std::cout<<"  [3] Update task                               "<<std::endl;
    std::cout<<"  [4] Delete a task                             "<<std::endl;
    std::cout<<std::endl;
    std::cout<<"  [5] Exit                                      "<<std::endl;
    std::cout<<"────────────────────────────────────────────────"<<std::endl;

    std::cout<<"Select an option: ";
    opc = readOption();

    }while(opc < 1 || opc > 5);
        
    return opc;
    
}

void menuSelection(int opc){
        switch(opc){

            case 1:
                std::cout<<"Selected option 1"<<std::endl;
                break;
            case 2:
                std::cout<<"Selected option 2"<<std::endl;
                break;
            case 3:
                std::cout<<"Selected option 3"<<std::endl;
                break;
            case 4:
                std::cout<<"Selected option 4"<<std::endl;
                break;
            case 5:
                std::cout<<"Selected option 5"<<std::endl;
                break;
        }
}

int readOption(){
    int opc;
    
    std::cin>>opc;
    if(std::cin.fail() || opc < 1 || opc > 5){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout<<"\n>> Please Enter a valid option."<<std::endl;
        std::cout<<"Press Enter to restart...";
        std::cin.get();

        return -1;
    }
    return opc;
}