#pragma once
#include <iostream>
#include <string>

static int processInputArguments(int argc,char* argv[]){
    if (argc==1){
        std::cout<<"Running on 3306";
        return 3306;
    }
    if(argv[2]=="--h"||argv[2]=="--help"){
        std::cout<<"--port / --p [] - gives the port number\n nothing will cause running on 3306\n";
    }else if(argv[2]=="--p"||argv[2]=="--port"){
        try{
        const int _portNumber=std::stoi(argv[3]);
        std::cout<<"Running on "+_portNumber<<std::endl;
        return _portNumber;
        }catch(const std::exception& e){
            std::cout<<"Port number argument is not a number";
        }
    }else{
        std::cout<<"Error, AriesDB could not run, for more helprun --help";
        return -1;
    }
}