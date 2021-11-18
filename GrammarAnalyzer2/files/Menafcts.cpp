#include"Menafcts.h"

//分析表M
map<string, map<string, string>> M;

//非终结符表
string nonTerminators[13] = {"program", "block", "stmts", "stmt", "bool"
, "bool'", "expr", "expr'", "expr''", "term", "term'", "term''", "factor"};

//终结符表
string terminators[17] = {"{", "}", "id", "=", ";", "while", "(", ")"
, "<", "<=", ">", ">=", "+", "-", "*", "/", "num"};

//是否在非终结符表中
map<string, bool> inNonTerminators;
//是否在终结符表中
map<string, bool> inTerminators;

//关键字表
string key[21] = { "if", "else", "while", "do", "main", "int", "float",
"double", "return", "const", "void", "continue", "break", "char", "unsigned",
"enum", "long", "switch", "case", "auto", "static" };

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
            else if (nonTerminators[i] == "expr''"){    // ) < <= > >= + - ;
                if (terminators[j] == ")" || terminators[j] == "<" || terminators[j] == "<=" 
                || terminators[j] == ">" || terminators[j] == ">=" || terminators[j] == ";") {
                    M["expr''"][terminators[j]] = "epsilon";
                }
                else if (terminators[j] == "+" || terminators[j] == "-") {
                    M["expr''"][terminators[j]] = "expr' expr''";
                }
                else {
                    M["expr''"][terminators[j]] = "error";
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
            else if (nonTerminators[i] == "term''"){    // ) < <= > >= + - * / ;
                if (terminators[j] == ")" || terminators[j] == "<" || terminators[j] == "<="
                || terminators[j] == ">" || terminators[j] == ">=" || terminators[j] == ";"
                || terminators[j] == "+" || terminators[j] == "-") {
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

//关键字判断
bool isKey(string str) {
	for (int i = 0; i < 21; i++) {
		if (str == key[i])
            return true;
	}
	return false;
}

//字母判断
bool isChar(char ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else return false;
}

//数字判断
bool isNum(char ch) {
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

//小数点判断
bool isPoint(char ch) {
	if (ch == '.')
		return true;
	return false;
}

//数值判断
bool isNumber(string str) {
    for (int i = 0; i < str.size(); i++) {
        if (!isNum(str[i]))
            return false;
    }
    return true;
}

//下划线判断
bool isUnderline(char ch) {
	if (ch == '_')
		return true;
	return false;
}

//标识符判断
bool isIdentifier(string str) {
    if (isKey(str)) {
        return false;
    }
    else {
        for (int i = 0; i < str.size(); i++) {
            if (i == 0) {
                if (!isChar(str[i]) && !isUnderline(str[i])) {
                    return false;
                }
            }
            else {
                if (!isNum(str[i]) && !isChar(str[i]) && !isUnderline(str[i])) {
                    return false;
                }
            }
        }
        return true;
    }
}

//非递归下降分析语法是否符合文法规范

//输入栈、文法栈
stack<string> inputStr, grammarStr;

//存放字符（单词） 
char token[20];	

//单词种类
int syn;

//字符串下标
int p = 0;

//输入字符串
char s[100];

void printStack1(stack<string> stk) {
    stack<string> tmpStk;
    while (!stk.empty()) {
        string tmpStr = stk.top();
        stk.pop();
        tmpStk.push(tmpStr);
    }
    while (!tmpStk.empty()) {
        string tmpStr = tmpStk.top();
        tmpStk.pop();
        cout << tmpStr;
    }
}

void printStack2(stack<string> stk) {
    stack<string> tmpStk;
    while (!stk.empty()) {
        string tmpStr = stk.top();
        stk.pop();
        cout << tmpStr;
    }
}

bool scanner() {
    cin.getline(s, 100);
    
    //  输入栈处理

    while (!inputStr.empty()) {
        inputStr.pop();
    }
    inputStr.push("#");

    p = 0;
    stack<string> tempInputStack;
    while (p < strlen(s)) {
        memset(token, '\0', sizeof(token));
        scannerToken(syn, p, s);
        string tempToken = "";
        for (int i = 0; i < strlen(token); i++) {
            tempToken += token[i];
        }
        tempInputStack.push(tempToken);
    }
    while (!tempInputStack.empty()) {
        string tempToken = tempInputStack.top();
        tempInputStack.pop();
        inputStr.push(tempToken);
    }

    //  文法栈处理
    while (!grammarStr.empty()) {
        grammarStr.pop();
    }
    grammarStr.push("#");
    grammarStr.push("program");
    while (grammarStr.top() != "#" && inputStr.top() != "#") {
        //  输出文法栈和输入栈
        printStack1(grammarStr); cout << "\t\t"; printStack2(inputStr);

        //  两个栈的栈顶元素
        string tmpInputStr = inputStr.top();
        string tmpGrammStr = grammarStr.top();

        if (inNonTerminators[tmpGrammStr]) {    //  文法栈栈顶为非终结符，弹出栈顶元素，逆序压入产生式右部
            //  产生式有动作，输出制表符，后接产生式动作
            cout << "\t\t";
            //  如果终结符不在分析表M中，则识别失败
            if (!isIdentifier(tmpInputStr) && !isNumber(tmpInputStr) && inTerminators[tmpInputStr] == false) {
                return false;
            }
            //  临时栈处理，以便逆序压入产生式右部
            stack<string> tempStack;
            while (!tempStack.empty()) {
                tempStack.pop();
            }
            //  弹出栈顶元素
            grammarStr.pop();
            //  将产生式右部压入临时栈，符号（终结符或非终结符）以空格分隔
            string rightPartStr;
            if (isIdentifier(tmpInputStr)) {
                rightPartStr = M[tmpGrammStr]["id"];
            }
            else if (isNumber(tmpInputStr)) {
                rightPartStr = M[tmpGrammStr]["num"];
            }
            else {
                rightPartStr = M[tmpGrammStr][tmpInputStr];
            }
            //  输出产生式动作
            cout << tmpGrammStr << "->" << rightPartStr << endl;
            //  空产生式右部，跳过
            if (rightPartStr == "epsilon") {
                continue;
            }
            string tmpStr = "";
            for (int i = 0; i < rightPartStr.size(); i++) {
                if (rightPartStr[i] != ' ') {
                    tmpStr += rightPartStr[i];
                }
                else {  //  读到空格，表示识别到一个符号，将其压入临时栈
                    tempStack.push(tmpStr);
                    tmpStr = "";
                }
            }
            if (tmpStr.size() != 0) {
                tempStack.push(tmpStr);
                tmpStr = "";
            }
            //  逆序入栈
            while (!tempStack.empty()) {
                tmpStr = tempStack.top();
                tempStack.pop();
                grammarStr.push(tmpStr);
            }
        }
        else {  //  文法栈栈顶为终结符，和输入栈栈顶元素比较
        
            //产生式无动作，输出换行
            cout << endl;

            if (tmpGrammStr == "id") { // 标识符
                if (isIdentifier(tmpInputStr)) {   //  两栈顶终结符相同，弹出
                    inputStr.pop();
                    grammarStr.pop();
                }
            }
            else if (tmpGrammStr == "num") {    //  数字
                if (isNumber(tmpInputStr)) {
                    inputStr.pop();
                    grammarStr.pop();
                }
            }
            else {
                if (tmpInputStr != tmpGrammStr) {   //  栈顶元素不同
                    return false;
                }
                else {
                    inputStr.pop();
                    grammarStr.pop();
                }
            }
        }
    }
    return true;
}

string digit0 = "", digit1 = "", digit2 = "";
//能否读入（在注释时使用）
int noteType = 0;// 1 为单行注释，2为多行注释
bool ableToRead = true;

//标识错误是否存在
bool existsFalse = false;

//字符常量报错标识
bool charFalse0 = false;//只读到一个单引号，属于不完整的字符
bool charFalse1 = false;//字符末尾缺少单引号
bool charFalse2 = false;//不允许使用该字符常量
bool charFalse3 = false;//字符格式错误，应输入单个字符

//字符串常量报错标识
bool stringFalse0 = false;//只读到一个双引号，属于不完整的字符串
bool stringFalse1 = false;//字符串末尾缺少双引号
bool stringFalse2 = false;//字符串中存在不允许包含的字符

void scannerToken(int& syn, int& p, char s[]) {

	//token中暂存的单词位数
	int count = 0;
	//小数点个数，大于1个则报错
	int cnt_point = 0;
	digit0 = "0:整型";//数值类型默认为整型
	digit1 = "2:十进制";//进制类型默认为十进制
	digit2 = "0:普通后缀";//后缀默认为普通类型

	while (p < strlen(s) && (s[p] == ' ' || s[p] == '\r' || s[p] == '\t')) p++;

	//遍历完成或读到单行注释则程序结束
	//if (p >= strlen(s) || s[p] == '/' && s[p + 1] == '/') {
	//	syn = 404;
	//	return;
	//}

	//读到单行注释
	if (s[p] == '/' && s[p + 1] == '/') {
		noteType = 1;
		ableToRead = false;
	}

	//读到多行注释
	if (s[p] == '/' && s[p + 1] == '*') {
		p += 2;
		noteType = 2;
		ableToRead = false;
	}
	//恢复读入
	if (s[p] == '*' && s[p + 1] == '/') {
		p += 2;
		noteType = 0;
		ableToRead = true;
	}

	if (p >= strlen(s))
		return;

	//开头是字母
	if (isChar(s[p]) || isUnderline(s[p]))
	{
		while (isNum(s[p]) || isChar(s[p]) || isUnderline(s[p])) {
			if (ableToRead == true)
				token[count++] = s[p++];
			else
				p++;
		}
		if (ableToRead == true) {
			token[count] = '\0';	//'\0'作为结束符 ,将单词分隔开 
			syn = isKey(token);
			if (syn == -1)
			{
				syn = 0;	//标识符letter(letter|digit) * 类型为 0
			}
		}
	}

	//开头是数字 类型 22
	//三种属性：类型、进制、后缀
	//整型 = 0
	//浮点型 = 1
	//二进制 = 0(0b|0B...)
	//八进制 = 1(0...)
	//十进制 = 2(0d|0D...)
	//十六进制 = 3(0x|0X...)
	//普通类型 = 0
	//短类型 = 1(...S)
	//长类型 = 2(...L)
	//科学计数 = 3(...E)
	else if (isNum(s[p]))
	{
		if (s[p] == '0') {
			if (ableToRead == true)
				token[count++] = s[p++];
			else
				p++;
			
			if (ableToRead == true) {
				if (s[p] == 'b' || s[p] == 'B')
					digit1 = "0:二进制", token[count++] = s[p++];
				else if (s[p] == 'd' || s[p] == 'D')
					digit1 = "2:十进制", token[count++] = s[p++];
				else if (s[p] == 'x' || s[p] == 'X')
					digit1 = "3:十六进制", token[count++] = s[p++];
				else if (isNum(s[p])) {
					digit1 = "1:八进制", token[count++] = s[p++];
				}
			}
			else
				p++;
		}

		//判断类型
		while (isNum(s[p]) || isPoint(s[p]))
		{
			if (ableToRead == true) {
				if (s[p] == '.')
					digit0 = "1:浮点型", cnt_point++;
				if (cnt_point > 1)
					digit0 = "浮点数格式错误";
				token[count++] = s[p++];
			}
			else
				p++;
		}

		//判断后缀
		if (s[p] == 'S') {
			if (ableToRead == true)
				digit2 = "1:短类型", token[count++] = s[p++];
			else
				p++;
		}
		else if (s[p] == 'L') {
			if (ableToRead == true)
				digit2 = "2:长类型", token[count++] = s[p++];
			else
				p++;
		}
		else if (s[p] == 'E') {
			if (ableToRead == true)
				digit2 = "3:科学计数", token[count++] = s[p++];
			else
				p++;
			if (s[p] == '+' || s[p] == '-') {
				if (ableToRead == true) {
					token[count++] = s[p++];
				}
				else
					p++;
			}
			while (isNum(s[p])) {
				if (ableToRead == true) {
					token[count++] = s[p++];
				}
				else
					p++;
			}
		}
		/*else if (s[p] == ';' || s[p] == ',') {
			if (ableToRead == true)
				digit2 = '0';
		}
		else {
			if (ableToRead == true) {
				digit2 = "未知的后缀属性";
				token[count++] = s[p++];
			}
			else
				p++;
		}*/
		if (ableToRead == true) {
			token[count] = '\0';//结束标识 
			syn = 22;	//数字digit(digit) * 类型为 22
		}
	}

	//特殊符号、字符常量、字符串常量
	else {
		//无争议的特殊字符
		if (ableToRead == true) {
			switch (s[p]) {
			case '+': syn = 23; token[0] = s[p]; token[1] = '\0'; break;
			case '-': syn = 24; token[0] = s[p]; token[1] = '\0'; break;
			case '*': syn = 25; token[0] = s[p]; token[1] = '\0'; break;
			case '/': syn = 26; token[0] = s[p]; token[1] = '\0'; break;
			case '{': syn = 29; token[0] = s[p]; token[1] = '\0'; break;
			case '}': syn = 30; token[0] = s[p]; token[1] = '\0'; break;
			case ';': syn = 31; token[0] = s[p]; token[1] = '\0'; break;
			case '(': syn = 32; token[0] = s[p]; token[1] = '\0'; break;
			case ')': syn = 33; token[0] = s[p]; token[1] = '\0'; break;
			}
		}
		if (s[p] == '!' && s[p + 1] == '=') {
			if (ableToRead == true)
				syn = 37, token[0] = s[p++], token[1] = s[p], token[2] = '\0';
			else
				p++;
		}
		if (s[p] == '&' && s[p + 1] == '&') {
			if (ableToRead == true)
				syn = 38, token[0] = s[p++], token[1] = s[p], token[2] = '\0';
			else
				p++;
		}
		if (s[p] == '|' && s[p + 1] == '|') {
			if (ableToRead == true)
				syn = 39, token[0] = s[p++], token[1] = s[p], token[2] = '\0';
			else
				p++;
		}
		//有争议的特殊字符
		//= ==
		if (s[p] == '=') {
			if (ableToRead == true)
				token[count++] = s[p];
			if (s[p + 1] == '=') {
				if (ableToRead == true) {
					p++;
					token[count++] = s[p];
					syn = 36;
				}
				else
					p++;
			}
			else {
				if (ableToRead == true)
					syn = 27;
			}
			if (ableToRead == true)
				token[count] = '\0';
		}

		//< <=
		if (s[p] == '<') {
			if (ableToRead == true)
				token[count++] = s[p];
			if (s[p + 1] == '=') {
				if (ableToRead == true) {
					p++;
					token[count++] = s[p];
					syn = 42;
				}
				else
					p++;
			}
			else {
				if (ableToRead == true)
					syn = 28;
			}
			if (ableToRead == true)
				token[count] = '\0';
		}

		//> >=
		if (s[p] == '>') {
			if (ableToRead == true)
				token[count++] = s[p];
			if (s[p + 1] == '=') {
				if (ableToRead == true) {
					p++;
					token[count++] = s[p];
					syn = 41;
				}
				else
					p++;
			}
			else {
				if (ableToRead == true)
					syn = 40;
			}
			if (ableToRead == true)
				token[count] = '\0';
		}

		//字符常量
		if (s[p] == '\'') {
			if (ableToRead == true)
				token[count++] = s[p++];
			else
				p++;
			if (p >= strlen(s)) {
				if (ableToRead == true) {
					existsFalse = true;
					charFalse0 = true;
				}
				return;
			}
			//字符常量为除了 ' \ \r 'a' 之外的字符
			if (s[p] != '\'' && s[p] != '\\'
				&& s[p] != '\r' && s[p] != 'a') {
				if (ableToRead == true) {
					token[count++] = s[p++];
					if (p >= strlen(s)) {
						if (ableToRead == true) {
							existsFalse = true;
							charFalse1 = true;
						}
						return;
					}
				}
				else
					p++;
			}
			else {
				if (ableToRead == true) {
					existsFalse = true;
					charFalse2 = true;
					return;
				}
			}
			//字符末尾要有 '
			if (s[p] == '\'') {
				if (ableToRead == true)
					token[count++] = s[p], syn = 46;
			}
			else {
				if (ableToRead == true) {
					existsFalse = true;
					charFalse3 = true;
				}
			}
		}

		//字符串常量
		if (s[p] == '\"') {
			if (ableToRead == true)
				token[count++] = s[p++];
			else
				p++;
			if (p >= strlen(s)) {
				if (ableToRead == true) {
					existsFalse = true;
					stringFalse0 = true;
				}
				return;
			}
			//字符串常量不包含 " \ \r "a" 等字符
			while (s[p] != '\"' && s[p] != '\\'
				&& s[p] != '\r' && s[p] != 'a') {
				if (ableToRead == true)
					token[count++] = s[p++];
				if (p >= strlen(s)) {
					if (ableToRead == true) {
						existsFalse = true;
						stringFalse1 = true;
					}
					return;
				}
			}
			if (s[p] == '\\' || s[p] == '\r' || s[p] == 'a') {
				if (ableToRead == true) {
					existsFalse = true;
					stringFalse2 = true;
					return;
				}
			}
			if (s[p] == '\"') {
				if (ableToRead == true)
					token[count++] = s[p], syn = 47;
			}
			else {
				if (ableToRead == true) {
					existsFalse = true;
					stringFalse1 = true;
				}
			}
		}

		//后移 
		p++;	//判断运算符和界符的这部分由于指针 p 没有向后指，所以需要将指针 p 向后移一位 
	}
}