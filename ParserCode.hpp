#ifndef PARSERCODE_HPP
#define PARSERCODE_HPP
#include "SymbolTable.hpp"
#include <string>
#include <bitset>
#include <map>
using namespace std;

extern SymbolTable UserSymbolTable;

class ParserCode{
    private:
        map<string, string> compMap;
        map<string, string> destMap;
        map<string, string> jumpMap;

        string parseA(string currA);
        string parseC(string currC);
    public:
        ParserCode();
        string compLookup(string currComp);
        string destLookup(string currDest);
        string jumpLookup(string currJump);

        string findCommandType(string curr);
};
#endif
