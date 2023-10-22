#include "ParserCode.hpp"

ParserCode::ParserCode(){
    compMap.insert(pair<string, string>("0", "0101010"));
    compMap.insert(pair<string, string>("1", "0111111"));
    compMap.insert(pair<string, string>("-1", "0111010"));
    compMap.insert(pair<string, string>("D", "0001100"));
    compMap.insert(pair<string, string>("A", "0110000"));
    compMap.insert(pair<string, string>("M", "1110000"));
    compMap.insert(pair<string, string>("!D", "0001101"));
    compMap.insert(pair<string, string>("!A", "0110001"));
    compMap.insert(pair<string, string>("!M", "1110001"));
    compMap.insert(pair<string, string>("-D", "0001111"));
    compMap.insert(pair<string, string>("-A", "0110011"));
    compMap.insert(pair<string, string>("-M", "1110011"));
    compMap.insert(pair<string, string>("D+1", "0011111"));
    compMap.insert(pair<string, string>("A+1", "0110111"));
    compMap.insert(pair<string, string>("M+1", "1110111"));
    compMap.insert(pair<string, string>("D-1", "0001110"));
    compMap.insert(pair<string, string>("A-1", "0110010"));
    compMap.insert(pair<string, string>("M-1", "1110010"));
    compMap.insert(pair<string, string>("D+A", "0000010"));
    compMap.insert(pair<string, string>("D+M", "1000010"));
    compMap.insert(pair<string, string>("D-A", "0010011"));
    compMap.insert(pair<string, string>("D-M", "1010011"));
    compMap.insert(pair<string, string>("A-D", "0000111"));
    compMap.insert(pair<string, string>("M-D", "1000111"));
    compMap.insert(pair<string, string>("D&A", "0000000"));
    compMap.insert(pair<string, string>("D&M", "1000000"));
    compMap.insert(pair<string, string>("D|A", "0010101"));
    compMap.insert(pair<string, string>("D|M", "1010101"));

    destMap.insert(pair<string, string>("NULL", "000"));
    destMap.insert(pair<string, string>("M", "001"));
    destMap.insert(pair<string, string>("D", "010"));
    destMap.insert(pair<string, string>("MD", "011"));
    destMap.insert(pair<string, string>("A", "100"));
    destMap.insert(pair<string, string>("AM", "101"));
    destMap.insert(pair<string, string>("AD", "110"));
    destMap.insert(pair<string, string>("AMD", "111"));

    jumpMap.insert(pair<string, string>("NULL", "000"));
    jumpMap.insert(pair<string, string>("JGT", "001"));
    jumpMap.insert(pair<string, string>("JEQ", "010"));
    jumpMap.insert(pair<string, string>("JGE", "011"));
    jumpMap.insert(pair<string, string>("JLT", "100"));
    jumpMap.insert(pair<string, string>("JNE", "101"));
    jumpMap.insert(pair<string, string>("JLE", "110"));
    jumpMap.insert(pair<string, string>("JMP", "111"));
}

string ParserCode::compLookup(string currComp){
    return compMap.find(currComp)->second;
}
string ParserCode::destLookup(string currDest){
    return destMap.find(currDest)->second;
}
string ParserCode::jumpLookup(string currJump){
    return jumpMap.find(currJump)->second;
}

string ParserCode::findCommandType(string curr){
    string tempInstr;
    if(curr.find('@') != -1){
        tempInstr = curr.substr(1, curr.size()-1);
        return parseA(tempInstr);
    }
    else{
        return parseC(curr);
    }
}

string ParserCode::parseA(string currA){
    if(currA.find_first_not_of("0123456789") == -1){
        return "0" + bitset<15>(stoi(currA)).to_string();
    }
    else if(UserSymbolTable.isInNotTable(currA)){
        UserSymbolTable.addVar(currA);
        int addr = UserSymbolTable.lookupSymbol(currA);
        return "0" + bitset<15>(addr).to_string();
    }
    else{
        int addr = UserSymbolTable.lookupSymbol(currA);
        return "0" + bitset<15>(addr).to_string();
    }
}
string ParserCode::parseC(string currC){
    string instrComp, instrDest, instrJump;
    int indexE = currC.find('=');
    int indexS = currC.find(';');

    instrComp = currC.substr(indexE+1, indexS-indexE-1);
    if(indexE == -1){
        instrDest = "NULL";
    }
    else{
        instrDest = currC.substr(0, indexE);
    }

    if(indexS == -1){
        instrJump = "NULL";
    }
    else{
        instrJump = currC.substr(indexS + 1);
    }
    
    return "111" + compLookup(instrComp) + destLookup(instrDest) + jumpLookup(instrJump);

}