#include "Interpreter_Interface.h"
#include<map>
#include<string>
using namespace std;

class interpreter : interpreter_inteface
{
public:
	map<string, int>symbols;
	int memory[256];
	int accumilator;
	int additional_register;
	int program_counter;
	int zero_result;
	int overflow;
	int size = 0;

	interpreter(string input) {
		program_counter = 0;
		accumilator = -1;
		zero_result = 0;
		overflow = 0;
		additional_register = -1;
		string program = input;
		int pos = 0;
		string token;
		while ((pos = program.find(" ")) != std::string::npos) {
			token = program.substr(0, pos);
			if (token == "DEC")
			{
				pair<string, int>entry;
				memory[size++] = 0;
				entry.second = size;
				memory[size++] = -1;
				program.erase(0, pos + 1);
				pos = program.find(" ");
				token = program.substr(0, pos);
				entry.first = token;
				symbols.insert(entry);
			}
			else if (token == "LDA")
			{
				memory[size++] = 1;
				program.erase(0, pos + 1);
				pos = program.find(" ");
				token = program.substr(0, pos);
				memory[size++] = symbols.at(token);
			}
			else if (token == "LDB")
			{
				memory[size++] = 2;
				program.erase(0, pos + 1);
				pos = program.find(" ");
				token = program.substr(0, pos);
				memory[size++] = symbols.at(token);
			}
			else if (token == "LDI")
			{
				memory[size++] = 3;
				program.erase(0, pos + 1);
				pos = program.find(" ");
				token = program.substr(0, pos);
				memory[size++] = stoi(token);
			}
			else if (token == "ST")
			{
				memory[size++] = 4;
				program.erase(0, pos + 1);
				pos = program.find(" ");
				token = program.substr(0, pos);
				memory[size++] = symbols.at(token);
			}
			else if (token == "XCH")
			{
				memory[size++] = 5;
			}
			else if (token == "JMP")
			{
				memory[size++] = 6;
				program.erase(0, pos + 1);
				pos = program.find(" ");
				token = program.substr(0, pos);
				memory[size++] = stoi(token);
			}
			else if (token == "JZS")
			{
				memory[size++] = 7;
				program.erase(0, pos + 1);
				pos = program.find(" ");
				token = program.substr(0, pos);
				memory[size++] = stoi(token);
			}
			else if (token == "JVS")
			{
				memory[size++] = 8;
				program.erase(0, pos + 1);
				pos = program.find(" ");
				token = program.substr(0, pos);
				memory[size++] = stoi(token);
			}
			else if (token == "ADD")
			{
				memory[size++] = 9;
			}
			else if (token == "HLT")
			{
				memory[size++] = 10;
			}
			program.erase(0, pos + 1);
		}
	};
	void lda_command(int address);
	void ldb_command(int address);
	void ldi_command(int value);
	void st_command(int address);
	void xch_command();
	void jmp_command(int number);
	void jzs_command(int number);
	void jvs_command(int number);
	void add_command();
	void hlt_command();
};

