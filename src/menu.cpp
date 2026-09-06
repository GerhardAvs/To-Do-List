#include <iostream>
#include <cstdlib>

#include "menu.hpp"

int displayMenu(void){
    int opc = 0;
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
    while(opc < 1 || opc > 5){
        std::cin>>opc;
    }

    return opc;
    
}

void menuSelection(int opc){
        switch(opc){
            case 1:
                std::cout<<"Selected option 1"<<std::endl;
                break;
            case 2:
                std::cout<<"Selected option 4"<<std::endl;
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
