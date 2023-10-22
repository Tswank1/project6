#include "SymbolTable.hpp"

SymbolTable::SymbolTable(){
    table.insert(pair<string, int>("SP",0));
    table.insert(pair<string, int>("LCL",1));
    table.insert(pair<string, int>("ARG",2));
    table.insert(pair<string, int>("THIS",3));
    table.insert(pair<string, int>("THAT",4));
    table.insert(pair<string, int>("R0",0));
    table.insert(pair<string, int>("R1",1));
    table.insert(pair<string, int>("R2",2));
    table.insert(pair<string, int>("R3",3));
    table.insert(pair<string, int>("R4",4));
    table.insert(pair<string, int>("R5",5));
    table.insert(pair<string, int>("R6",6));
    table.insert(pair<string, int>("R7",7));
    table.insert(pair<string, int>("R8",8));
    table.insert(pair<string, int>("R9",9));
    table.insert(pair<string, int>("R10",10));
    table.insert(pair<string, int>("R11",11));
    table.insert(pair<string, int>("R12",12));
    table.insert(pair<string, int>("R13",13));
    table.insert(pair<string, int>("R14",14));
    table.insert(pair<string, int>("R15",15));
    table.insert(pair<string, int>("SCREEN",16384));
    table.insert(pair<string, int>("KBD",24576));
    numVars = 16;
    numLabels = 0;
}

int SymbolTable::incNumLabels(){
    return numLabels++;
}

void SymbolTable::addLabel(string label){
    table.insert(pair<string, int>(label, numLabels));
}

void SymbolTable::addVar(string var){
    table.insert(pair<string, int>(var, numVars));
    numVars++;
}

bool SymbolTable::isInNotTable(string key){
    if(table.find(key) != table.end()){
        return false;
    }
    return true;
}

int SymbolTable::lookupSymbol(string var){
    return table.find(var)->second;
}