#include<iostream>
#include<map>
#include<string>
#include<stack>
#include<cstring>
using namespace std;

void printMap(map<string, map<string, string>>);
void initMap();
bool scanner();
bool isIdentifier(string);
bool isKey(string);
bool isChar(char);
bool isNum(char);
bool isNumber(string);
bool isUnderline(char);
void scannerToken(int&, int&, char[]);
void printStack1(stack<string>);
void printStack2(stack<string>);