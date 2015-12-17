#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>

using namespace std;
const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
class PlayFair
{
public:
	PlayFair():key(){}
	PlayFair(const string & _key);
	void set_key(const string & _key);
	string encode(string message);
	string decode(const string &code) const;

private:
	void process_message(string &message, string &processed_message);
	bool build_dict();
	string key;
	vector<string> dict;

};

	