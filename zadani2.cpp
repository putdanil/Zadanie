#include<iostream>
#include<string>
#include<map>
#include<fstream>

using namespace std;


int main()
{
	map<pair<int, char>, int> identif;
	for (char c = 'a'; c <= 'z'; c++) {
		identif.insert(make_pair(make_pair(1, c), 2));
	}
	for (char c = 'a'; c <= 'z'; c++) {
		identif.insert(make_pair(make_pair(2, c), 2));
	}
	for (char c = '0'; c <= '9'; c++) {
		identif.insert(make_pair(make_pair(2, c), 2));
	}
	identif.insert(make_pair(make_pair(1, '_'), 2));
	identif.insert(make_pair(make_pair(2, '_'), 2));

	map<pair<int, char>, int> numbers;
	for (char c = '0'; c <= '9'; c++) {
		numbers.insert(make_pair(make_pair(1, c), 3));
	}
	for (char c = '0'; c <= '9'; c++) {
		numbers.insert(make_pair(make_pair(3, c), 3));
	}
	numbers.insert(make_pair(make_pair(3, 'e'), 3));
	numbers.insert(make_pair(make_pair(3, '.'), 3));

	map<pair<int, char>, int> operators;
	operators.insert(make_pair(make_pair(1, '+'), 5));
	operators.insert(make_pair(make_pair(1, '-'), 5));
	operators.insert(make_pair(make_pair(1, '/'), 5));
	operators.insert(make_pair(make_pair(1, '|'), 5));
	operators.insert(make_pair(make_pair(1, '*'), 5));
	operators.insert(make_pair(make_pair(1, '<'), 5));
	operators.insert(make_pair(make_pair(1, '>'), 5));
	operators.insert(make_pair(make_pair(1, '&'), 5));
	operators.insert(make_pair(make_pair(1, '='), 5));
	operators.insert(make_pair(make_pair(1, '!'), 5));
	operators.insert(make_pair(make_pair(5, '!'), 5));
	operators.insert(make_pair(make_pair(5, '='), 5));
	operators.insert(make_pair(make_pair(5, '&'), 5));
	operators.insert(make_pair(make_pair(5, '>'), 5));
	operators.insert(make_pair(make_pair(5, '*'), 5));
	operators.insert(make_pair(make_pair(5, '/'), 5));
	operators.insert(make_pair(make_pair(5, '|'), 5));

	map<pair<int, char>, int> sint;
	sint.insert(make_pair(make_pair(1, ';'), 4));
	sint.insert(make_pair(make_pair(1, '}'), 4));
	sint.insert(make_pair(make_pair(1, '{'), 4));
	sint.insert(make_pair(make_pair(1, '('), 4));
	sint.insert(make_pair(make_pair(1, ')'), 4));

	string tex[10] = { "int", "double", "boolean", "while", "if", "break","true","false" };

	int start = 1; //начальное состояние
	int cur = start;

	ifstream file("fio.txt");
	char s;
	string str = "";
	int p = 0;

	ofstream fout;
	fout.open("file.txt");

	while (file.get(s)) {
		if (s != ' ' && s != ';' && s != '{' && s != '}' && s != ')' && s != '(' &&!(isalpha(s)&&cur==5)) {
			if (identif[make_pair(cur, s)]) //происходит ли переход
			{
				cur = identif[make_pair(cur, s)];
				str += s;
				p = 1;
			}
			if (numbers[make_pair(cur, s)]) //происходит ли переход
			{
				cur = numbers[make_pair(cur, s)];
				str += s;
				p = 2;
			}
			if (operators[make_pair(cur, s)]) //происходит ли переход
			{
				cur = operators[make_pair(cur, s)];
				str += s;
				p = 3;
			}
		}
		else {
			for (int i = 0; i < 8; i++)
				if (tex[i] == str)
					p = 5;
			switch (p)
			{
			case 1:
				fout << "Identifikator:  " << str << endl;
				break;
			case 2:
				fout << "Number:  " << str << endl;
				break;
			case 3:
				fout << "Operator:  " << str << endl;
				break;
			case 5:
				fout << "Klu4evoe slovo:   " << str << endl;
				break;
			case 0:
				break;
			}
			if (sint[make_pair(start, s)]) //происходит ли переход
			{
				cur = sint[make_pair(start, s)];
				str = s;
				p = 4;
				fout << "Sintaksis:  " << str << endl;
			}
			if (isalpha(s) && cur == 5)
				str = s;
			else
				str = "";
			p = 0;
			cur = start;
		}
	}
	fout.close();
	system("pause");
	return 0;
}
