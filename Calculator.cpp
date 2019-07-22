// Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "token.h"

namespace {
	const char quit = 'q', print = ';', let = 'L', del = 'D';
}
//deals with bracket and returns numerical value
double brac_n_num(token_stream& ts,command &c);

double plus_n_minus(token_stream& ts,command& c);

//deals with factorial
double facto(token_stream& ts,command &c) {
	double left = brac_n_num(ts,c);
	token t = ts.get_token(ts,c);
	while (true) {
		switch (t.type) {
		case '!': {
			double fact = 1;
			if (left == 0)	return fact;

			for (int i = left; i > 0; i--)	fact *= i;
			left = fact;
			t = ts.get_token(ts,c);
			break;
		}
		default:
			ts.put_token(t);
			return left;
		}
	}
}

//deals with powers and roots
double power_n_root(token_stream& ts,command& c) {
	double left = facto(ts,c);
	token t = ts.get_token(ts,c);
	while (true) {
		switch (t.type) {
		case '^': {
			token x = ts.get_token(ts,c);
			if (x.type == 'i')
				left = pow(left, x.value);
			else {
				ts.put_token(x);
				x.value = brac_n_num(ts,c);
				left = pow(left, x.value);
			}
			t = ts.get_token(ts,c);
			break;
		}
		default:
			ts.put_token(t);
			return left;
		}
	}
}

//deals with multiplication and division
double mul_n_div(token_stream& ts,command& c) {
	double left = power_n_root(ts,c);
	token t = ts.get_token(ts,c);
	while (true) {
		switch (t.type) {
		case '*':
			left *= power_n_root(ts,c);
			t = ts.get_token(ts,c);
			break;
		case '/':
			left /= power_n_root(ts,c);
			t = ts.get_token(ts,c);
			break;
		default:
			ts.put_token(t);
			return left;
		}
	}
}

//deals with addition and subtraction
double plus_n_minus(token_stream& ts,command& c) {
	double left = mul_n_div(ts,c);
	token t = ts.get_token(ts,c);
	while (true) {
		switch (t.type) {
		case '+':
			left += mul_n_div(ts,c);
			t = ts.get_token(ts,c);
			break;
		case '-':
			left -= mul_n_div(ts,c);
			t = ts.get_token(ts,c);
			break;
		default:
			ts.put_token(t);
			return left;
		}
	}
}

double commands(token_stream& ts,command& c) {
	token t = ts.get_token(ts,c);
	switch (t.type) {
	case let: {
		variable v = c.define_variable();
		switch (v.code) {
		case 321:	case 322:	case 323:	case 324:
			throw v.code;
			break;
		default:
			cout << "Variable defined succesfully" << endl;
		}
		return v.value;
	}
	default:
		ts.put_token(t);
		return plus_n_minus(ts, c);
	}
}

//deals with brackets and sign
double brac_n_num(token_stream& ts,command& c) {
	double left;
	token t = ts.get_token(ts,c);
	switch (t.type) {
	case '(': {
		left = plus_n_minus(ts,c);
		token x = ts.get_token(ts,c);
		if (x.type != ')') {
			cout <<"')' not found";
			exit(0);
		}
		return left;	}
	case 'i':
	case 'v':
		return t.value;
	case '+': {
		token a = ts.get_token(ts,c);
		return a.value;	}
	case '-': {
		token a = ts.get_token(ts,c);
		return -a.value;	}
	//default case enot needed as ts.get() wont return an unsupported character
	}
}

void clean_up(token_stream& ts) {
	char x;
	do {
		x = getchar();
	} while (!(x == ' ' || x == 10 || x == ';' || x == 'q'));
	ts.reset();
	cin.putback(x);
}

void calculate(token_stream& ts, command& c) {
	try {
		do {
			token temp{ 0 };
			cout << ">";
			temp = ts.get_token(ts, c);
			while (temp.type == ';')
				temp = ts.get_token(ts, c);//removes any remaining ';' from input stream
			if (temp.type == 'q')
				exit(0);
			if (temp.type == 'e')
				throw temp.value;

			ts.put_token(temp);
			cout << "\b=" << commands(ts, c) << endl;// '\b' is used to erase '>' character from console is present

		} while (cin);
	}
	catch (int c) {
		//Source code file : Calculator
		if (c == 101) {
			cerr << "Invalid token" << endl;
		}


		//Source code file : token
//function number -> 1
		if (c == 211) {//error 1
			cerr << "Caluculator doesnot support special symbols" << endl;
		}


		//Source code file : command
//function number -> 2
		if (c == 321) {
			cerr << "Variable name cannot start with number or Special Symbol" << endl;
		}
		if (c == 322) {
			cerr << "Variable cannot contain Special symbol" << endl;
		}
		if (c == 323) {
			cerr << "Error in reading number" << endl;
		}
		if (c == 324) {
			cerr << "Variable alread Defined/Pre-Defined" << endl;
		}

		//function number -> 3 (error first identified)
		//error code thrown in source code file Calculator in function calculate
		if (c == 331) {
			cerr << "\b1.Unknown Command" << endl;//'b' is used to remove '=' charcter from console is present
			cerr << "2.Undefined variable" << endl << endl;
		}

		clean_up(ts);
	}
}

int main() {
	token_stream ts;
	command c;
	while (cin) {
		calculate(ts,c);
	}
}