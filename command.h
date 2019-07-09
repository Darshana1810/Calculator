#pragma once

#include<iostream>
#include <string>
#include <vector>
//#include "token.h"

using namespace std;

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
	double var_value(string name);
};