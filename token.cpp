//Source code file number -> 2
#include "token.h"
#include "command.h"
#include "error.h"
#include <cstdlib>
namespace {
	const char quit = 'q', print = ';', let = 'L', del = 'D';
}

//Function number -> 1
//error_codes -> 211
token token_stream::get_token(token_stream& ts,command& c) {

	//check if buffer is full
	if (ts.full) {
		ts.full = false;
		return ts.buffer;
	}

	//take input from user and prepare token
	char input;
	cin >> input;
	

	//make token or check for commands
	switch (input) {
	case '+':	case '-':
	case '*':	case '/':
	case '^':
	case '!':
	case '(':	case ')':
	case print:
	case quit:
		return token(input);

	case '.':
	case '0':	case '1':	case '2':	case '3':	case '4':
	case '5':	case '6':	case '7':	case '8':	case '9': {
		cin.putback(input);	//placing character back if its a number
		double val;
		cin >> val;
		return token('i', val);
	}

	default:
		if (isalpha(input)) {
			//read word/command/variable name
			string temp = "";
			do {
				temp += input;
				input = getchar();
			} while (isalnum(input));
			cin.putback(input);
			if (temp == "let")
				return token(let);
			if (temp == "del")
				return token(del);
			else{
				//check for defined variable 
				double k = c.var_value(temp);
				return token('v', k);
			}
		}
		//if input is special symbol
		cerr << "Bad Token"<<endl;
		throw 211;
	}
}

//Function number -> 2
void token_stream::put_token(token t) {
		buffer = t;
		full = true;
}
