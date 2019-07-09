#include "command.h"

void command::check(string name) {
	for (variable& i : variables) {
		if (i.name == name) {
			cerr << "Variable already present with value : " << i.value;
			cerr << "Try using a different name";
		}
	}
}

void command::commands(string cc) {
	if (cc == "let") {
		char c;
		string name = "";
		int val;
		cin >> c;
		do {
			name += c;
			cin >> c;
		} while (c != '=');
		cin >> val;
		check(name);
		variables.push_back(variable(name, val));
	}
}
