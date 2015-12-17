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
	void set_key(const string & _key); //设置密钥
	string encode(string message); // 对明文message进行加密，返回密文
	string decode(const string &code) const; //对密文code进行解密，返回明文

private:
	void process_message(string &message, string &processed_message);
	bool build_dict();
	string key;
	vector<string> dict;

};

	
