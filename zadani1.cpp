#include<iostream>
#include<string>
#include<map>

using namespace std;


int main()
{
	map<pair<int, char>, int> state = //������� ���������
	{ {{ 1, 'a' },2},
	 {{ 2, 'b' },3 },
	{ { 1, 'b' },2 } };
	int fstate[2] = { 2, 3 }; //�������� ��������
	string input = "cccaaaaab"; 
	int k=2; 
	int start=1; //��������� ���������
	string res = "false";
	int cur = start;
	int m = 0, str = 0;
	for (int i = k; i < input.length(); i++)
	{
		int p = 0;
		map<pair<int, char>, int>::iterator it = state.begin(); 
		for (int j = 0; it != state.end(); it++) { 
			if (it->first.second == input[i] && it->first.first == cur) { //���������� �� �������
				cur = it->second; //���������
				str++; //������� ����� ���������
				p = 1;
				break;
			}
		}
		if (p == 0) {
			str = 0; //�������� ����� � ������������ � ������
			cur = start;
		}
		else
			for (int d = 0; d < 2; d++)
				if (cur == fstate[d]) //���� ��������� �������� �� ���������� ����� ��������� � ������� ��� �����
					if (m < str) {
						m = str;
						res = "true";
					}
	}

	cout << m << endl << res << endl;
	system("pause");
	return 0;
}
