#pragma once
#include <iostream>
#include <string>

static int processInputArguments(int argc,char* argv[]){
    if (argc==1){
        printf("Running on 3306\n");
        return 3306;
    }
    std::string arg2(argv[1]);
    
    if(arg2=="--h"||arg2=="--h"){
        std::cout<<"--port / --p [] - gives the port number\n nothing will cause running on 3306\n";
    }else if(arg2=="--p"||arg2=="--port"&&argc==3){
        try{
        std::string arg3(argv[2]);
        const int _portNumber=std::stoi(arg3);
        printf("Running on %d \n",_portNumber);
        return _portNumber;
        }catch(const std::exception& e){
            std::cout<<"Port number argument is not a number";
        }
    }
    std::cout<<"Error, AriesDB could not run, for more helprun h\n";
    return -1;
}