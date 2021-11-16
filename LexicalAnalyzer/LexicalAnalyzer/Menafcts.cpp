#include"Menafcts.h"

//��Źؼ���
char key[21][20] = { "if", "else", "while", "do", "main", "int", "float",
"double", "return", "const", "void", "continue", "break", "char", "unsigned",
"enum", "long", "switch", "case", "auto", "static" };

//����ַ������ʣ� 
char token[20];	

//��ֵ�������������ԣ����͡����ơ���׺
string digit0, digit1, digit2; 

//�����ַ���
char s[100];
//�ַ����±�
int p = 0;

//�к�
int id = 0;

//��������
int syn;

//�ܷ���루��ע��ʱʹ�ã�
int noteType = 0;// 1 Ϊ����ע�ͣ�2Ϊ����ע��
bool ableToRead = true;

//��ʶ�����Ƿ����
bool existsFalse = false;

//�ַ����������ʶ
bool charFalse0 = false;//ֻ����һ�������ţ����ڲ��������ַ�
bool charFalse1 = false;//�ַ�ĩβȱ�ٵ�����
bool charFalse2 = false;//������ʹ�ø��ַ�����
bool charFalse3 = false;//�ַ���ʽ����Ӧ���뵥���ַ�

//�ַ������������ʶ
bool stringFalse0 = false;//ֻ����һ��˫���ţ����ڲ��������ַ���
bool stringFalse1 = false;//�ַ���ĩβȱ��˫����
bool stringFalse2 = false;//�ַ����д��ڲ�����������ַ�

//�жϹؼ�������
int isKey(char s[]) {
	for (int i = 0; i < 21; i++) {
		if (strcmp(s, key[i]) == 0)	{
			return i + 1;	//�ؼ��ֵ��ֱ���
		}
	}
	return -1;
}

//�ж��ǲ����»���
bool isUnderline(char ch) {
	if (ch == '_')
		return true;
	return false;
}

//�ж��ǲ�����ĸ 
bool isChar(char ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else return false;
}

//�ж��ǲ������� 
bool isNum(char ch) {
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

//�ж��ǲ���С����
bool isPoint(char ch) {
	if (ch == '.')
		return true;
	return false;
}

//�����ӳ���
void scanner(int& syn, int& p, char s[]) {

	//token���ݴ�ĵ���λ��
	int count = 0;
	//С�������������1���򱨴�
	int cnt_point = 0;
	digit0 = "0:����";//��ֵ����Ĭ��Ϊ����
	digit1 = "2:ʮ����";//��������Ĭ��Ϊʮ����
	digit2 = "0:��ͨ��׺";//��׺Ĭ��Ϊ��ͨ����

	while (p < strlen(s) && (s[p] == ' ' || s[p] == '\r' || s[p] == '\t')) p++;

	//������ɻ��������ע����������
	//if (p >= strlen(s) || s[p] == '/' && s[p + 1] == '/') {
	//	syn = 404;
	//	return;
	//}

	//��������ע��
	if (s[p] == '/' && s[p + 1] == '/') {
		noteType = 1;
		ableToRead = false;
	}

	//��������ע��
	if (s[p] == '/' && s[p + 1] == '*') {
		p += 2;
		noteType = 2;
		ableToRead = false;
	}
	//�ָ�����
	if (s[p] == '*' && s[p + 1] == '/') {
		p += 2;
		noteType = 0;
		ableToRead = true;
	}

	if (p >= strlen(s))
		return;

	//��ͷ����ĸ
	if (isChar(s[p]) || isUnderline(s[p]))
	{
		while (isNum(s[p]) || isChar(s[p]) || isUnderline(s[p])) {
			if (ableToRead == true)
				token[count++] = s[p++];
			else
				p++;
		}
		if (ableToRead == true) {
			token[count] = '\0';	//'\0'��Ϊ������ ,�����ʷָ��� 
			syn = isKey(token);
			if (syn == -1)
			{
				syn = 0;	//��ʶ��letter(letter|digit) * ����Ϊ 0
			}
		}
	}

	//��ͷ������ ���� 22
	//�������ԣ����͡����ơ���׺
	//���� = 0
	//������ = 1
	//������ = 0(0b|0B...)
	//�˽��� = 1(0...)
	//ʮ���� = 2(0d|0D...)
	//ʮ������ = 3(0x|0X...)
	//��ͨ���� = 0
	//������ = 1(...S)
	//������ = 2(...L)
	//��ѧ���� = 3(...E)
	else if (isNum(s[p]))
	{
		if (s[p] == '0') {
			if (ableToRead == true)
				token[count++] = s[p++];
			else
				p++;
			
			if (ableToRead == true) {
				if (s[p] == 'b' || s[p] == 'B')
					digit1 = "0:������", token[count++] = s[p++];
				else if (s[p] == 'd' || s[p] == 'D')
					digit1 = "2:ʮ����", token[count++] = s[p++];
				else if (s[p] == 'x' || s[p] == 'X')
					digit1 = "3:ʮ������", token[count++] = s[p++];
				else if (isNum(s[p])) {
					digit1 = "1:�˽���", token[count++] = s[p++];
				}
			}
			else
				p++;
		}

		//�ж�����
		while (isNum(s[p]) || isPoint(s[p]))
		{
			if (ableToRead == true) {
				if (s[p] == '.')
					digit0 = "1:������", cnt_point++;
				if (cnt_point > 1)
					digit0 = "��������ʽ����";
				token[count++] = s[p++];
			}
			else
				p++;
		}

		//�жϺ�׺
		if (s[p] == 'S') {
			if (ableToRead == true)
				digit2 = "1:������", token[count++] = s[p++];
			else
				p++;
		}
		else if (s[p] == 'L') {
			if (ableToRead == true)
				digit2 = "2:������", token[count++] = s[p++];
			else
				p++;
		}
		else if (s[p] == 'E') {
			if (ableToRead == true)
				digit2 = "3:��ѧ����", token[count++] = s[p++];
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
				digit2 = "δ֪�ĺ�׺����";
				token[count++] = s[p++];
			}
			else
				p++;
		}*/
		if (ableToRead == true) {
			token[count] = '\0';//������ʶ 
			syn = 22;	//����digit(digit) * ����Ϊ 22
		}
	}

	//������š��ַ��������ַ�������
	else {
		//������������ַ�
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
		//������������ַ�
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

		//�ַ�����
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
			//�ַ�����Ϊ���� ' \ \r 'a' ֮����ַ�
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
			//�ַ�ĩβҪ�� '
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

		//�ַ�������
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
			//�ַ������������� " \ \r "a" ���ַ�
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

		//���� 
		p++;	//�ж�������ͽ�����ⲿ������ָ�� p û�����ָ��������Ҫ��ָ�� p �����һλ 
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
	if (syn == 0) res += "��ʶ��";
	else if (1 <= syn && syn <= 21) res += "�ؼ��ֻ�����";
	else if (syn == 22) res += "����";
	else if (23 <= syn && syn <= 42) res += "�����ַ�";
	else if (syn == 46) res += "�ַ�����";
	else if (syn == 47) res += "�ַ�������";
	return res;
}

void getToken() {

	while (true) {
		cout << "������C���Դ��룺" << endl;
		cin.getline(s, 100);
		//cnt++;
		//if (cnt == 10) break;
		//�հ׷������ַ����飬�ո񣬻س������Ʊ����
		if ( strlen(s) == 0
			|| strcmp(s, "\t") == 0 || strcmp(s, "\r") == 0
			|| strcmp(s, " ") == 0) {
			continue;
		}

		//����ע�ͽ���
		if (noteType == 1) {
			noteType = 0;
			ableToRead = true;
		}

		//��ʼ�����ֱ�ʶ
		existsFalse = false;
		stringFalse0 = false;
		stringFalse1 = false;
		stringFalse2 = false;
		charFalse0 = false;
		charFalse1 = false;
		charFalse2 = false;
		charFalse3 = false;

		//��ʼ���±�
		p = 0;
		
		//ֻ����һ��ԭ�ַ���
		int temp_cnt = 0;

		while (p < strlen(s)) {	//ѭ������ ,p��δָ���ַ������	

			memset(token, '\0', sizeof(token));
			scanner(syn, p, s);
			
			if (temp_cnt == 0)
				cout << "-------------��" << ++id << "�д���Ϊ��" << ' ' << s << endl, temp_cnt++;

			if (ableToRead == true) {
				//����ʷ�����
				if (existsFalse) {
					if (charFalse0) {
						cout << "ֻ����һ�������ţ����ڲ��������ַ�" << endl;
					}
					if (charFalse1) {
						cout << "�ַ�ĩβȱ�ٵ�����" << endl;
					}
					if (charFalse2) {
						cout << "������ʹ�ø��ַ�����" << endl;
					}
					if (charFalse3) {
						cout << "�ַ���ʽ����Ӧ���뵥���ַ�" << endl;
					}
					if (stringFalse0) {
						cout << "ֻ����һ��˫���ţ����ڲ��������ַ���" << endl;
					}
					if (stringFalse1) {
						cout << "�ַ���ĩβȱ��˫����" << endl;
					}
					if (stringFalse2) {
						cout << "�ַ����д��ڲ�����������ַ�" << endl;
					}
				}
				//����ʷ�ʶ����
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