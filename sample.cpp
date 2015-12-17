#include <iostream>
#include "play_fair.h"

using namespace std;


int main(int argc,char **argv)
{
    //string key="moonf,ighting";
   // string sentence="I will be back on january first";
	string key = "playfair example";
	string sentence("Hide the gold in the tree stump");
	PlayFair playfair(key);
	string code = playfair.encode(sentence);
	
	cout << code << endl;
	cout << playfair.decode(code) << endl;
	system("pause");
    return 0;
}

