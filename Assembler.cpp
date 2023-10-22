#include "ParserCode.hpp"
#include "SymbolTable.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

SymbolTable UserSymbolTable;
ParserCode Parser;

int main(int argc, char const *argv[]) {
    string testFile, hackFile;
    ifstream fIn;
    ofstream fOut;

    queue<string> queue1, queue2; 

    testFile = string(argv[1]);
    fIn.open(testFile);
    if (fIn.is_open()) {
        if (argc == 2) {
            int i = testFile.find_last_of('.');
            hackFile = testFile.substr(0, i) + ".hack";
        }
        fOut.open(hackFile);
        if (fOut.is_open()){       
            string input;
            while (getline(fIn, input)){//prepass
                int i = input.find("//");
                string removeComments = input.substr(0, i);
                if (removeComments.size() == 0){
                    continue;
                }
                for(int j = 0; j < input.size(); j++){
                    if(removeComments.at(j) == ' '){
                        removeComments.erase(j);
                    }
                }
                queue1.push(removeComments);
            }
            while (!queue1.empty()){//pass1
                input = queue1.front();
                queue1.pop();
                if (input.find('(') != -1 && input.find(')') != -1){
                    int indexL = input.find_last_of('(');
                    int indexR = input.find_first_of(')');
                    input = input.substr(indexL+1, indexR-1);
                    UserSymbolTable.addLabel(input);
                    continue;
                }
                else{
                    UserSymbolTable.incNumLabels();
                }
                queue2.push(input);
            }
            while (!queue2.empty()){//pass2
                input = queue2.front();
                queue2.pop();
                string binary = Parser.findCommandType(input);
                cout << input << "->" << binary << endl;
                fOut << binary << endl;
            }
        }
        fOut.close();
    }
    fIn.close();

    return 0;
}
