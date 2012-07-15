/******************************************************************************************************************
*** Name:       Jonathan Canfield               																***
*** Clase:      CPSC 323																						***
*** Professor:  Choi																							***
*** Assignment: #2																								***
*** Due:        11/4/2011																						***
*******************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
/******************************************************************************************************************
header file used for declarations, struct and class. 
*******************************************************************************************************************/
enum allowed_token {Identifier, Keyword, Integer,Real, Operator, Separator, Unknown};
const char * tokens [] = {"Identifier", "Keyword", "Integer", "Real",
								"Operator", "Separator", "Unknown"};
const char * Keywords [] = {"function", "int", "Real", "boolean", "if","endif", "else", "while", 
								"return", "print", "scan", "true", "false","write"};
bool found_Keyword=false;
void Syntax_ana();
void Opt_Function_Definitions();
void Function_Definitions();
void Function();
void Opt_Parameter_List();
void Parameter_List();
void Parameter();
void Qualifier();
void Body();
void Opt_Declaration_List();
void Declaration_List();
void Declaration();
void IDs();
void FSM_STATment_List();
void FSM_STATment();
void Compound();
void Assign();
void If();
void Return();
void Write();
void Read();
void While();
void Condition();
void Relop();
void Expression();
void Expression_Prime();
void Term();
void Term_Prime();
void Factor();
void Primary();
void Empty();
void Term_Epsilon();
void Expression_Epsilon();
void output_new_token(const char * str);
void output_new_token(allowed_token token);
void output_production_rules(const char * str);
void check_end_file ();

struct Token {
	char lexeme[50];
	allowed_token token;
	int line_int;
	bool Lexeme_comp(const char * str)
	{ 
		return (strcmp(str,lexeme) == 0); 
	}
};

class Lexical {
private:
	ifstream input;
public:
	int b;
	Lexical(const char * filename) { 
		input.open(filename);
		b = 1;
	}
	~Lexical() { input.close(); }
	

	bool check_Keyword( const char * id ){
		found_Keyword=false;
		for (int counter=0;counter<14;counter++)
			if (strcmp(Keywords[counter],id) == 0)
				found_Keyword = true;
		return found_Keyword;
	}
	Token nextToken();
};
Lexical *get_lexical;
Token token;
ofstream output_file;
