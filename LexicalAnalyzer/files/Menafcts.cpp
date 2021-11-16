#include"Menafcts.h"

//存放关键字
char key[21][20] = { "if", "else", "while", "do", "main", "int", "float",
"double", "return", "const", "void", "continue", "break", "char", "unsigned",
"enum", "long", "switch", "case", "auto", "static" };

//存放字符（单词） 
char token[20];	

//数值常量的三个属性：类型、进制、后缀
string digit0, digit1, digit2; 

//输入字符串
char s[100];
//字符串下标
int p = 0;

//行号
int id = 0;

//单词种类
int syn;

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

//判断关键字种类
int isKey(char s[]) {
	for (int i = 0; i < 21; i++) {
		if (strcmp(s, key[i]) == 0)	{
			return i + 1;	//关键字的种别码
		}
	}
	return -1;
}

//判断是不是下划线
bool isUnderline(char ch) {
	if (ch == '_')
		return true;
	return false;
}

//判断是不是字母 
bool isChar(char ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else return false;
}

//判断是不是数字 
bool isNum(char ch) {
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

//判断是不是小数点
bool isPoint(char ch) {
	if (ch == '.')
		return true;
	return false;
}

//核心子程序
void scanner(int& syn, int& p, char s[]) {

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

string synChangeToString() {
	string res = "";
	int tempNum = syn;
	if (tempNum == 0)
		res = "0";
	while (tempNum) {
		res = char(tempNum % 10 + 48) + res;
		tempNum /= 10;
	}
	res += ":";
	if (syn == 0) res += "标识符";
	else if (1 <= syn && syn <= 21) res += "关键字或保留字";
	else if (syn == 22) res += "整型";
	else if (23 <= syn && syn <= 42) res += "特殊字符";
	else if (syn == 46) res += "字符常量";
	else if (syn == 47) res += "字符串常量";
	return res;
}

void getToken() {

	while (true) {
		cout << "请输入C语言代码：" << endl;
		cin.getline(s, 100);
		// if (s == "Stop Running") {
		// 	break;
		// }
		//cnt++;
		//if (cnt == 10) break;
		//空白符（空字符数组，空格，回车符，制表符）
		if ( strlen(s) == 0
			|| strcmp(s, "\t") == 0 || strcmp(s, "\r") == 0
			|| strcmp(s, " ") == 0) {
			continue;
		}

		//单行注释结束
		if (noteType == 1) {
			noteType = 0;
			ableToRead = true;
		}

		//初始化各种标识
		existsFalse = false;
		stringFalse0 = false;
		stringFalse1 = false;
		stringFalse2 = false;
		charFalse0 = false;
		charFalse1 = false;
		charFalse2 = false;
		charFalse3 = false;

		//初始化下标
		p = 0;
		
		//只输入一遍原字符串
		int temp_cnt = 0;

		while (p < strlen(s)) {	//循环条件 ,p还未指到字符串最后	

			memset(token, '\0', sizeof(token));
			scanner(syn, p, s);
			
			if (temp_cnt == 0)
				cout << "-------------第" << ++id << "行代码为：" << ' ' << s << endl, temp_cnt++;

			if (ableToRead == true) {
				//如果词法出错
				if (existsFalse) {
					if (charFalse0) {
						cout << "只读到一个单引号，属于不完整的字符" << endl;
					}
					if (charFalse1) {
						cout << "字符末尾缺少单引号" << endl;
					}
					if (charFalse2) {
						cout << "不允许使用该字符常量" << endl;
					}
					if (charFalse3) {
						cout << "字符格式错误，应输入单个字符" << endl;
					}
					if (stringFalse0) {
						cout << "只读到一个双引号，属于不完整的字符串" << endl;
					}
					if (stringFalse1) {
						cout << "字符串末尾缺少双引号" << endl;
					}
					if (stringFalse2) {
						cout << "字符串中存在不允许包含的字符" << endl;
					}
				}
				//输出词法识别结果
				else {
					if (syn == 22) {
						cout << '<' << synChangeToString() << ", " << token << ", "
							<< digit0 << ", " << digit1 << ", " << digit2
							<< '>' << endl;
					}
					else {
						if (strlen(token))
							cout << '<' << synChangeToString() << ", " << token << '>' << endl;
					}
				}
				if (existsFalse == true)
					break;
			}
		}
	}
}

/*int main()
{
	//freopen("input_01.in", "r", stdin);
	//freopen("output_01.out", "w", stdout);

	getToken();
	return 0;
}*/