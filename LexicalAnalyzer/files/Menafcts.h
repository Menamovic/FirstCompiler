#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;

int isKey(char []);
bool isUnderline(char);
bool isChar(char);
bool isNum(char);
bool isPoint(char);
void scanner(int&, int&, char []);
void getToken();
string synChangeToString();