#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP
#include <map>
#include <string>
using namespace std;

class SymbolTable{
    private:
        map<string, int> table;
        int numVars;
        int numLabels;

    public:
        SymbolTable();
        int incNumLabels();
        void addLabel(string label);
        void addVar(string var);
        int lookupSymbol(string var);
        bool isInNotTable(string key);
};
#endif