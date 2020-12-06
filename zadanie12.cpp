#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<vector>
#include <algorithm>
#include<sstream>

using namespace std;

void MaxString(map<pair<int, char>, int>state, int k, string input)
{
	int start = 1; //начальное состояние
	string res = "false";
	int cur = start;
	int m = 0, str = 0;
	int fstate[2] = { 3}; //конечные переходы

	for (int i = k; i < input.length(); i++)
	{
		int p = 0;
		map<pair<int, char>, int>::iterator it = state.begin();
		for (int j = 0; it != state.end(); it++) {
			if (it->first.second == input[i] && it->first.first == cur) { //происходит ли переход
				cur = it->second; //переходим
				str++; //считаем длину подстроки
				p = 1;
				break;
			}
		}
		if (p == 0) {
			str = 0; //обнуляем длину и возвращаемся в начало
			cur = start;
		}
		else
			for (int d = 0; d < 2; d++)
				if (cur == fstate[d]) //если состояние конечное то запоминаем длину подстроки и говорим что нашли
					if (m < str) {
						m = str;
						res = "true";
					}
	}
	cout << m <<endl;
	cout << res<<endl;
}

int main()
{
	map<pair<int, char>, int>state;
	ifstream in("in.txt");
	int start = 1;
	string line;
	string input = "cccaaaaab";
	int k = 2;
	while (!in.eof())
	{
		getline(in, line);
		string n;
		vector<string>c;
		stringstream ss(line);
		while (getline(ss, n, ' '))
			c.push_back(n);
		if (c.size() == 3)
			state.insert(make_pair(make_pair(stoi(c[0]), c[1][0]), stoi(c[2])));
	}

	MaxString(state, k, input);

	system("pause");
	return 0;
}
