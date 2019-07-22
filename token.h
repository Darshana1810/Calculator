#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//class token to genrate token from istream or store token 
class token {
public:
	char type;
	double value;
	token():type(0),value(0){}
	token(char c) : type(c), value(0) {}
	token(char c, double v) :type(c), value(v) {}
};


class variable {
public:
	string name;
	double value;
	int code;
	variable(string n, double v) :name(n), value(v), code(0) {}
	variable(int c) :code(c), name(""), value(0) {}
};

class command {
public:
	int check(string name);
	vector<variable> variables, pre_defined;
	variable define_variable();
	void pre();
	string buffer;
	command() { pre(); }
	token var_value(string name);
};

//token stream to generate or store token
class token_stream {
public:
	token buffer;
	bool full;	//indicates state of buffer
	token get_token(token_stream& ts,command &c);	//returns token from buffer or genrates a new token from istream
	void put_token(token t);	//stores 1 token in buffer
	token_stream() :buffer(0), full(false) {}
	void reset();
};













