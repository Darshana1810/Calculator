#pragma once

#include "command.h"
#include <iostream>
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

//token stream to generate or store token
class token_stream {
public:
	token buffer;
	bool full;	//indicates state of buffer
	token get_token(token_stream& ts,command &c);	//returns token from buffer or genrates a new token from istream
	void put_token(token t);	//stores 1 token in buffer
	token_stream() :buffer(0), full(false) {}
};