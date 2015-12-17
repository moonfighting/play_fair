#include "play_fair.h"
#include <set>
using namespace std;
bool isnotalpha(char ch)
{
	return !isalpha(ch);
}
PlayFair::PlayFair(const string & _key)
{
	set_key(_key);
}

void PlayFair::set_key(const string & _key)
{
	key = _key;
	bool flag = build_dict();
	if(!flag)
	{
		cout << "set key fail, please check the key" << endl;
		exit(-1);
	}
	cout << "set key success!" << endl;
}

bool PlayFair::build_dict()
{
	if(key.empty())
		return false;
	string::iterator p_end = remove_if(key.begin(), key.end(), isnotalpha);
	
	//dict.assign(5, string(""));
	set<char> hashtable;
	string tmp_line("");
	for(string::iterator iter = key.begin(); iter != key.end(); iter++)
	{
		char ch = tolower(*iter);
		if(hashtable.find(ch) != hashtable.end())
			continue;
		if(ch == 'j')
			continue;
		tmp_line.push_back(ch);
		hashtable.insert(ch);
		if(tmp_line.size() == 5)
		{
			dict.push_back(tmp_line);
			tmp_line.clear();
		}
	}

	if(dict.size() != 5)
	{
		char st = 'a';
		while(st <= 'z')
		{
			if(st == 'j' || hashtable.find(st) != hashtable.end())
			{
				st++;
				continue;
			}

			tmp_line.push_back(st);
			st++;
			if(tmp_line.size() == 5)
			{
				dict.push_back(tmp_line);
				tmp_line.clear();
			}
			if(dict.size() == 5)
				break;
		}
	}
	return true;
}

//����ʱ��������������ͬ��ĸ�м����x,������ĸΪx�������p
//�����ʣ��һ����ĸ�����ڽ�β���x��������ĸΪx,�����p
void PlayFair::process_message(string &message, string &processed_message)
{
	string::iterator p_end = remove_if(message.begin(), message.end(), isnotalpha); //ȥ������ĸ�ַ�
	string::iterator p_iter = message.begin();
	int len = message.size();
	while(p_iter != p_end)
	{
		char ch = tolower(*p_iter);            

		if(processed_message.size() % 2 == 0)  //���������message����Ϊż������ֱ����Ӹ���ĸ
		{
			processed_message.push_back(ch);
			p_iter++;
		}
		else if(processed_message.size() % 2 != 0)   // ������ż���������ж�������������ĸ�Ƿ���ͬ������ͬ�����x��p������ͬ��ֱ�Ӳ���
		{
			if(processed_message.back() == ch)
			{
				processed_message.push_back(ch == 'x' ? 'p' : 'x');
			}
			else
			{
				processed_message.push_back(ch);
				p_iter++;
			}
		}
		
	}
	if(processed_message.size() % 2 != 0)
	{
		processed_message.push_back(processed_message.back() == 'x' ? 'p' : 'x');
	}
	
}

string PlayFair::encode(string message)														 
{
	string code;
	string processed_message;
	process_message(message, processed_message);
	
	int first_row = 0;
	int first_col = 0;
	int second_row = 0;
	int second_col = 0;

	for(size_t i = 0; i < processed_message.size(); i += 2)
	{
		for(int j = 0; j < 5; j++)
		{
			for(int k = 0; k < 5; k++)
			{
				if(processed_message[i] == dict[j][k])
				{
					first_row = j;
					first_col = k;
				}
				if(processed_message[i + 1] == dict[j][k])
				{
					second_row = j;
					second_col = k;
				}
			}
		}

		if(first_row == second_row)
		{
			first_col = first_col == 4 ? 0 : first_col + 1;
			second_col = second_col == 4 ? 0 : second_col + 1;
		}
		else if(first_col == second_col)
		{
			first_row = first_row == 4 ? 0 : first_row + 1;
			second_row = second_row == 4 ? 0 : second_row + 1;
		}
		else
		{
			swap(first_col, second_col);
		}

		code.push_back(dict[first_row][first_col]);
		code.push_back(dict[second_row][second_col]);

	}

	return code;
}


string PlayFair::decode(const string &code) const
{
	string message;

	int first_row = 0;
	int first_col = 0;
	int second_row = 0;
	int second_col = 0;

	for(size_t i = 0; i < code.size(); i += 2)
	{
		for(int j = 0; j < 5; j++)
		{
			for(int k = 0; k < 5; k++)
			{
				if(code[i] == dict[j][k])
				{
					first_row = j;
					first_col = k;
				}
				if(code[i + 1] == dict[j][k])
				{
					second_row = j;
					second_col = k;
				}
			}
		}

		if(first_row == second_row)
		{
			first_col = first_col == 0 ? 4 : first_col - 1;
			second_col = second_col == 0 ? 4 : second_col - 1;
		}
		else if(first_col == second_col)
		{
			first_row = first_row == 0 ? 4 : first_row - 1;
			second_row = second_row == 0 ? 4 : second_row - 1;
		}
		else
		{
			swap(first_col, second_col);
		}

		message.push_back(dict[first_row][first_col]);
		message.push_back(dict[second_row][second_col]);

	}

	return message;
}



