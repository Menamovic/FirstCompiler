#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;

int isKey(char[]);
bool isUnderline(char);
bool isChar(char);
bool isNum(char);
bool isPoint(char);
void scanner(int&, int&, char[]);
void runGrammarAnalyzer();
string synChangeToString();
void writeFalses();
void printToken();

void grammarAnalyze();
bool scannerBlock();
bool scannerStmts();
bool scannerIf();
bool scannerWhile();
bool scannerDoWhile();
bool scannerBool();
bool scannerExpr();
bool scannerTerm();
bool scannerFactor();
bool scannerStmt();