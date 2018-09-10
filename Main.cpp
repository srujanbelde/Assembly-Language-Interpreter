#include<fstream>
#include<iostream>
#include"Command.h"
#include"Interpreter.h"

void interpreter::lda_command(int address) {
	accumilator = memory[address];
};
void interpreter::ldb_command(int address) {
	additional_register = memory[address];
};
void interpreter::ldi_command(int value) {
	accumilator = value;
};
void interpreter::st_command(int address) {
	memory[address] = accumilator;
};
void interpreter::xch_command() {
	int temp = accumilator;
	accumilator = additional_register;
	additional_register = temp;
};
void interpreter::jmp_command(int number) {
	program_counter = number;
};
void interpreter::jzs_command(int number) {
	if (zero_result == 1)
		program_counter = number;
	else
		program_counter++;
};
void interpreter::jvs_command(int number) {
	if (overflow == 1)
		program_counter = number;
	else
		program_counter++;
};
void interpreter::add_command() {
	if ((accumilator + additional_register) == 0)
	{
		zero_result = 1;
	}
	else
	{
		zero_result = 0;
	}
	if (((accumilator + additional_register) > INT_MAX) || ((accumilator + additional_register) < INT_MIN))
	{
		overflow = 1;
		if ((accumilator + additional_register) > INT_MAX)
			accumilator = ((accumilator + additional_register) - INT_MAX);
		if ((accumilator + additional_register) < INT_MIN)
			accumilator = ((accumilator + additional_register) + INT_MIN);
	}
	else
	{
		overflow = 0;
		accumilator = accumilator + additional_register;
	}
};
void interpreter::hlt_command()
{
	program_counter = 257;
}




class LDA : command
{
	interpreter *in;
	int address;
public:
	LDA(interpreter *i, int ad)
	{
		in = i;
		address = ad;
	}
	void execute();
};
void LDA::execute()
{
	in->lda_command(address);
}

class LDB : command
{
	interpreter *in;
	int address;
public:
	LDB(interpreter *i, int ad)
	{
		in = i;
		address = ad;
	}
	void execute();
};
void LDB::execute()
{
	in->ldb_command(address);
}

class LDI : command
{
	interpreter *in;
	int value;
public:
	LDI(interpreter *i, int v)
	{
		in = i;
		value = v;
	}
	void execute();
};
void LDI::execute()
{
	in->ldi_command(value);
}

class ST : command
{
	interpreter *in;
	int address;
public:
	ST(interpreter *i, int ad)
	{
		in = i;
		address = ad;
	}
	void execute();
};
void ST::execute()
{
	in->st_command(address);
}

class XCH : command
{
	interpreter *in;
public:
	XCH(interpreter *i)
	{
		in = i;
	}
	void execute();
};
void XCH::execute()
{
	in->xch_command();
}

class JMP : command
{
	interpreter *in;
	int address;
public:
	JMP(interpreter *i, int ad)
	{
		in = i;
		address = ad;
	}
	void execute();
};
void JMP::execute()
{
	in->jmp_command(address);
}

class JZS : command
{
	interpreter *in;
	int address;
public:
	JZS(interpreter *i, int ad)
	{
		in = i;
		address = ad;
	}
	void execute();
};
void JZS::execute()
{
	in->jzs_command(address);
}

class JVS : command
{
	interpreter *in;
	int address;
public:
	JVS(interpreter *i, int ad)
	{
		in = i;
		address = ad;
	}
	void execute();
};
void JVS::execute()
{
	in->jvs_command(address);
}

class ADD : command
{
	interpreter *in;
public:
	ADD(interpreter *i)
	{
		in = i;
	}
	void execute();
};
void ADD::execute()
{
	in->add_command();
}

class HLT : command
{
	interpreter *in;
public:
	HLT(interpreter *i)
	{
		in = i;
	}
	void execute();
};
void HLT::execute()
{
	in->hlt_command();
}





int main()
{
	string user_input;
	interpreter *main_interpreter;
	main_interpreter = NULL;
	while (true)
	{
		cout << "Enter your Command:\t";
		cin >> user_input;
		if (user_input == "i")
		{
			string line;
			string input = "";
			ifstream myfile("input.txt");
			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					input = input + line + " ";
				}
				myfile.close();
			}
//			input = input.substr(0, input.length() - 1);
//			cout << input;
			interpreter myint(input);
			main_interpreter = &myint;
		}
		else if (user_input == "q")
		{
			break;
		}
		else if (user_input == "d")
		{
			if (main_interpreter->size < main_interpreter->program_counter)
			{
				cout << "oops!reached end of the memory" << endl;
				continue;
			}
			int code_value = main_interpreter->memory[main_interpreter->program_counter];
			main_interpreter->program_counter = main_interpreter->program_counter + 1;
			if (code_value == 0)
			{
				main_interpreter->program_counter = main_interpreter->program_counter + 1;
			}
			else if (code_value == 1)
			{
				LDA cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
				cm.execute();
				main_interpreter->program_counter = main_interpreter->program_counter + 1;
			}
			else if (code_value == 2)
			{
				LDB cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
				cm.execute();
				main_interpreter->program_counter = main_interpreter->program_counter + 1;
			}
			else if (code_value == 3)
			{
				LDI cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
				cm.execute();
				main_interpreter->program_counter = main_interpreter->program_counter + 1;
			}
			else if (code_value == 4)
			{
				ST cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
				cm.execute();
				main_interpreter->program_counter = main_interpreter->program_counter + 1;
			}
			else if (code_value == 5)
			{
				XCH cm(main_interpreter);
				cm.execute();
			}
			else if (code_value == 6)
			{
				JMP cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
				cm.execute();
			}
			else if (code_value == 7)
			{
				JZS cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
				cm.execute();
			}
			else if (code_value == 8)
			{
				JVS cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
				cm.execute();
			}
			else if (code_value == 9)
			{
				ADD cm(main_interpreter);
				cm.execute();
			}
			else if (code_value == 10)
			{
				HLT cm(main_interpreter);
				cm.execute();
			}
			cout << "Accumilator:" << main_interpreter->accumilator << endl;
			cout << "Additional Register:" << main_interpreter->additional_register << endl;
			cout << "Program Counter:" << main_interpreter->program_counter << endl;
			cout << "Zero-Result:" << main_interpreter->zero_result << endl;
			cout << "Overflow:" << main_interpreter->overflow << endl;
		}
		else if (user_input == "r")
		{
			while (main_interpreter->size > main_interpreter->program_counter)
			{
				int code_value = main_interpreter->memory[main_interpreter->program_counter];
				main_interpreter->program_counter = main_interpreter->program_counter + 1;
				if (code_value == 0)
				{
					main_interpreter->program_counter = main_interpreter->program_counter + 1;
				}
				else if (code_value == 1)
				{
					LDA cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
					cm.execute();
					main_interpreter->program_counter = main_interpreter->program_counter + 1;
				}
				else if (code_value == 2)
				{
					LDB cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
					cm.execute();
					main_interpreter->program_counter = main_interpreter->program_counter + 1;
				}
				else if (code_value == 3)
				{
					LDI cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
					cm.execute();
					main_interpreter->program_counter = main_interpreter->program_counter + 1;
				}
				else if (code_value == 4)
				{
					ST cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
					cm.execute();
					main_interpreter->program_counter = main_interpreter->program_counter + 1;
				}
				else if (code_value == 5)
				{
					XCH cm(main_interpreter);
					cm.execute();
				}
				else if (code_value == 6)
				{
					JMP cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
					cm.execute();
				}
				else if (code_value == 7)
				{
					JZS cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
					cm.execute();
				}
				else if (code_value == 8)
				{
					JVS cm(main_interpreter, main_interpreter->memory[main_interpreter->program_counter]);
					cm.execute();
				}
				else if (code_value == 9)
				{
					ADD cm(main_interpreter);
					cm.execute();
				}
				else if (code_value == 10)
				{
					HLT cm(main_interpreter);
					cm.execute();
				}
			}
			cout << "Accumilator:" << main_interpreter->accumilator << endl;
			cout << "Additional Register:" << main_interpreter->additional_register << endl;
			cout << "Program Counter:" << main_interpreter->program_counter << endl;
			cout << "Zero-Result:" << main_interpreter->zero_result << endl;
			cout << "Overflow:" << main_interpreter->overflow << endl;
		}
		else if (user_input == "s")
		{
			ofstream myfile;
			myfile.open("output.txt");
			myfile << "Memory:" << endl;
			for (int i = 0; i < main_interpreter->size; i++)
				myfile << (to_string(main_interpreter->memory[i]));
			myfile << "Accumilator:" << main_interpreter->accumilator << endl;
			myfile << "Additional Register:" << main_interpreter->additional_register << endl;
			myfile << "Program Counter:" << main_interpreter->program_counter << endl;
			myfile << "Zero-Result:" << main_interpreter->zero_result << endl;
			myfile << "Overflow:" << main_interpreter->overflow << endl;
			cout << "Saved!" << endl;
		}
	}
	return 0;
}