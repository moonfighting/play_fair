#play_fair
=========
该代码为play_fair加密算法的C++实现版本
play_fair.h 中的PlayFair为算法类
每个PlayFair的对象都可以实现设置密钥，对明文加密和对密文解密的功能

实例化加密类，设置初始密钥：
string key;
PlayFair playfair(key);
或
PlayFair playfair();
playfair.set_key(key);

后续若需要修改密钥，则可以用set_key方法：
playfair.set_key(key2);

设置好密钥后即可对明文进行加密: 
string message;
string code = playfair.encode(message);

也可以对密文进行解密,使用相同的密钥:
string code;
string message = playfair.decode(message);

注意解密后的明文是经过处理的，需要解密者自己判断明文的意义。
