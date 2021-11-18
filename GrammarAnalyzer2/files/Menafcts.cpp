#include"Menafcts.h"

//分析表M
map<string, map<string, string>> M;

//非终结符表
string nonTerminators[13] = {"program", "block", "stmts", "stmt", "bool", "bool'", "expr", "expr'", "expr''", "term", "term'", "term''", "factor"};
//终结符表
string terminators[17] = {"{", "}", "id", "=", ";", "while", "(", ")", "<", "<=", ">", ">=", "+", "-", "*", "/", "num"};
//是否在非终结符表中
map<string, bool> inNonTerminators;
//是否在终结符表中
map<string, bool> inTerminators;

//打印分析表M
void printMap(map<string, map<string, string>> M) {
    map<string, map<string, string>>::iterator p1;
    map<string, string>::iterator p2;
    for (p1 = M.begin(); p1 != M.end(); p1++) {
        for (p2 = p1->second.begin(); p2 != p1->second.end(); p2++) {
            cout << "[" << p1->first << "][" << p2->first << "]: " << p1->first << "->" << p2->second << endl;
        }
        cout << endl;
    }
}

//手工构造分析表M
void initMap() {    //以空格分隔各符号（终结符与非终结符）
    //初始化非终结符表
    inNonTerminators.clear();
    for (int i = 0; i < 13; i++) {
        inNonTerminators[nonTerminators[i]] = true;
    }
    //初始化终结符表
    inTerminators.clear();
    for (int i = 0; i < 17; i++) {
        inTerminators[terminators[i]] = true;
    }
    //构造分析表M
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 17; j++) {
            if (nonTerminators[i] == "program") {   // {
                if (terminators[j] == "{") {
                    M["program"]["{"] = "block";
                }
                else {
                    M["program"][terminators[j]] = "error";
                }
            }
            else if (nonTerminators[i] == "block") {    // {
                if (terminators[j] == "{") {
                    M["block"]["{"] = "{ stmts }";
                }
                else {
                    M["block"][terminators[j]] = "error";
                }
            }
            else if (nonTerminators[i] == "stmts") {    // { id while }
                if (terminators[j] == "{" || terminators[j] == "id" || terminators[j] == "while") {
                    M["stmts"][terminators[j]] = "stmt stmts";
                }
                else if (terminators[j] == "}") {
                    M["stmts"]["}"] = "epsilon";
                }
                else {
                    M["stmts"][terminators[j]] = "error";
                }
            }
            else if (nonTerminators[i] == "stmt") { // { id while
                if (terminators[j] == "{") {
                    M["stmt"]["{"] = "block";
                }
                else if (terminators[j] == "id") {
                    M["stmt"]["id"] = "id = expr ;";
                }
                else if (terminators[j] == "while") {
                    M["stmt"]["while"] = "while ( bool ) stmt";
                }
                else {
                    M["stmt"][terminators[j]] = "error";
                }
            }
            else if (nonTerminators[i] == "bool") { // id ( num
                if (terminators[j] == "id" || terminators[j] == "(" || terminators[j] == "num") {
                    M["bool"][terminators[j]] = "expr bool'";
                }
                else {
                    M["bool"][terminators[j]] == "error";
                }
            }
            else if (nonTerminators[i] == "bool'"){ // ( < <= > >=
                if (terminators[j] == ")") {
                    M["bool'"][")"] = "epsilon";
                }
                else if (terminators[j] == "<") {
                    M["bool'"]["<"] = "< expr";
                }
                else if (terminators[j] == "<=") {
                    M["bool'"]["<="] = "<= expr";
                }
                else if (terminators[j] == ">") {
                    M["bool'"][">"] = "> expr";
                }
                else if (terminators[j] == ">=") {
                    M["bool'"][">="] = ">= expr";
                }
                else {
                    M["bool'"][terminators[j]] = "error";
                }
            }
            else if (nonTerminators[i] == "expr") { // id ( num
                if (terminators[j] == "id" || terminators[j] == "(" || terminators[j] == "num") {
                    M["expr"][terminators[j]] = "term expr''";
                }
                else {
                    M["expr"][terminators[j]] = "error";
                }
            }
            else if (nonTerminators[i] == "expr'") {    // + -
                if (terminators[j] == "+") {
                    M["expr'"]["+"] = "+ term";
                }
                else if (terminators[j] == "-") {
                    M["expr'"]["-"] = "- term";
                }
                else {
                    M["expr'"][terminators[j]] = "error";
                }
            }
            else if (nonTerminators[i] == "expr''"){    // ) < <= > >= + -
                if (terminators[j] == ")" || terminators[j] == "<" || terminators[j] == "<=" 
                || terminators[j] == ">" || terminators[j] == ">=") {
                    M["expr''"][terminators[j]] = "epsilon";
                }
                else if (terminators[j] == "+" || terminators[j] == "-") {
                    M["expr'"][terminators[j]] = "expr' expr''";
                }
                else {
                    M["expr'"][terminators[j]] = "error";
                }
            }
            else if (nonTerminators[i] == "term") { // id ( num
                if (terminators[j] == "id" || terminators[j] == "(" || terminators[j] == "num") {
                    M["term"][terminators[j]] = "factor term''";
                }
                else {
                    M["term"][terminators[j]] = "error";
                }
            }
            else if (nonTerminators[i] == "term'") {    // * /
                if (terminators[j] == "*") {
                    M["term'"][terminators[j]] = "* factor";
                }
                else if (terminators[j] == "/") {
                    M["term'"][terminators[j]] = "/ factor";
                }
                else {
                    M["term'"][terminators[j]] = "error";
                }
            }
            else if (nonTerminators[i] == "term''"){    // ) < <= > >= * /
                if (terminators[j] == ")" || terminators[j] == "<" || terminators[j] == "<="
                || terminators[j] == ">" || terminators[j] == ">=") {
                    M["term''"][terminators[j]] = "epsilon";
                }
                else if (terminators[j] == "*" || terminators[j] == "/") {
                    M["term''"][terminators[j]] = "term' term''";
                }
                else {
                    M["term''"][terminators[j]] = "error";
                }
            }
            else if (nonTerminators[i] == "factor"){    // id ( num
                if (terminators[j] == "id") {
                    M["factor"]["id"] = "id";
                }
                else if (terminators[j] == "(") {
                    M["factor"]["("] = "( expr )";
                }
                else if (terminators[j] == "num") {
                    M["factor"]["num"] = "num";
                }
                else {
                    M["factor"][terminators[j]] = "error";
                }
            }
        }
    }
}

//非递归下降分析语法是否符合文法规范
bool scanner() {

}