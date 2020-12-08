#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<vector>
#include <algorithm>
#include<sstream>

using namespace std;


int main()
{
	vector<map<pair<int, char>, int>>avto;
	ifstream in("in.txt");
	int k;
	in >> k;
	string line;
	vector<string>name;
	vector<int>prior;
	for (int i = 0; i < k + 1; i++) {
		getline(in, line);
		if (line != "") {
			prior.push_back(line[0] - '0');
			name.push_back(line);
		}
	}

	while (!in.eof())
	{
		getline(in, line);
		vector<string>::iterator it;
		it = find(name.begin(), name.end(), line);
		if (it != name.end()) {
			line = "";
			map<pair<int, char>, int>avtocur;
			while (find(name.begin(), name.end(), line) == name.end()) {
				string n;
				vector<string>c;
				stringstream ss(line);
				while (getline(ss, n, ' '))
					c.push_back(n);
				if (c.size() == 3)
					avtocur.insert(make_pair(make_pair(stoi(c[0]), c[1][0]), stoi(c[2])));
				getline(in, line);
			}
			avto.push_back(avtocur);

		}
	}

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
		pair<int, char>pa(cur, s);
		map<pair<int, char>, int>::iterator it;

		if (s != ' ' && s != ';' && s != '{' && s != '}' && s != ')' && s != '(' && !(isalpha(s) && cur == 5)) {
			for (int i = 0; i < avto.size(); i++) {
				it = avto[i].find(pa);
				if (it != avto[i].end()) //происходит ли переход
				{
					cur = avto[i].find(pa)->second;
					str += s;
					p = cur;
				}
			}
		}
		else {
			for (int i = 0; i < 8; i++)
				if (tex[i] == str)
					p = 6;
			switch (p)
			{
			case 2:
				fout << "Identifikator:  " << str << endl;
				break;
			case 3:
				fout << "Number:  " << str << endl;
				break;
			case 5:
				fout << "Operator:  " << str << endl;
				break;
			case 6:
				fout << "Klu4evoe slovo:   " << str << endl;
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
