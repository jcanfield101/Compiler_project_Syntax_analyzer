/******************************************************************************************************************
*** Name:       Jonathan Canfield										                 						***
*** Clase:      CPSC 323																						***
*** Professor:  Choi																							***
*** Assignment: #2																								***
*** Due:        11/4/2011																						***
*******************************************************************************************************************/
#include "header.h";

/******************************************************************************************************************
For this homework assignment I soon Realized our lexical analyzer would not meet the requirements for grabbing one 
token at a time when need.  I guess I could have ran the lexical analyzer stored everything into a text file then 
from that text file the Syntax analyzer would read the tokens from there.  I knew this would work but it’s a very
amateur way of going about it. So much to my dismay I completely revamped the first assignment to use a proper 
table for the tokens and FSM FSM_STAT. I think I got a few grey hairs from this but I wanted to do the assignment 
as correct as I possibly could. 
The main is very simple. We are now using pointers to get tokens from the lexical ana. It’s check to see if the 
file is empty or not and calls the Syntax analyzer. If I didn't modify the first assignment The lex. would read 
the entire source code from the user and output the results Then the syntax analyzer would use that text file for
its process. Now the syntax analyzer calls the lex when it needs a new token. I feel this is a much more professional
approach. Sadly I didn't ran out of time so I was unable to add error checking, if the code is not 100% correct 
the program crashes. 
*******************************************************************************************************************/
int main(){		
	   system("Color F");
	get_lexical = new Lexical("rat11f.txt");
	output_file.open("out.txt");	
	token = get_lexical->nextToken();	
	check_end_file ();
	Syntax_ana();	
	output_file.close();

	return 0;
}

/******************************************************************************************************************
This is the main part of the syntax analyzer. It first checks to see if the users program will have functions. If
it does the process for functions will be called. If it does not have any functions this part is ignored. 
*******************************************************************************************************************/

/*<Rat11F>::=  # <Opt Function Definition> # <Opt Declaration List> <FSM_STATment List> # */
void Syntax_ana(){
		
	if (token.Lexeme_comp("#")){
		output_new_token("");
		output_production_rules("<Syntax_ana>::=  # <Opt Function Definition> # <Opt Declaration List> <FSM_STATment List> #");		
		token = get_lexical->nextToken();
		Opt_Function_Definitions();
		token = get_lexical->nextToken();		
		Opt_Declaration_List();		
	}
		output_new_token("");
		FSM_STATment_List();
		cout<<"hi";
		system("pause");
	
	
}
/******************************************************************************************************************
Now there are a lot of functions for this program. instead is commenting on everyone; this would be some what
reduendent since most just output results. I did however comment above each function the syntax rule which is 
outputted. 
*******************************************************************************************************************/
//<Opt Function Definition>::=  <Function Definition> | <Empty>
void Opt_Function_Definitions() {
	output_production_rules("<Opt Function Definition>::=  <Function Definition> | <Empty>");
	
	if (token.Lexeme_comp("function")){		
	   Function_Definitions();}	
}

/*<Function Definition>::=  <Function> | <Function> <Function Definition>*/
void Function_Definitions(){
	output_production_rules("<Function Definition>::=  <Function> | <Function> <Function Definition>");
	Function();
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	if (token.Lexeme_comp("function"))
		Function_Definitions();
}

/*<Function>::=  function <Identifier> (<Opt Parameter List>) <Opt Declaration List> <Body>*/
void Function() {
	output_production_rules("<Function>::=  function <Identifier> (<Opt Parameter List>) <Opt Declaration List> <Body>");
	output_new_token("function");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(Identifier);
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	Opt_Parameter_List();	
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	Opt_Declaration_List();
	Body();
}

/*<Opt Parameter List>::=  <Parameter List> | <Empty>*/
void Opt_Parameter_List() {
	output_production_rules("<Opt Parameter List>::=  <Parameter List> | <Empty>");
	if (token.token == Identifier)
		Parameter_List();
	else
		Empty();
}

/*<Parameter List>::=  <Parameter> | <Parameter> , <Parameter List>*/
void Parameter_List() {
	output_production_rules("<Parameter List>::=  <Parameter> | <Parameter> , <Parameter List> ");
	Parameter();
	token = get_lexical->nextToken();
	check_end_file ();
	if (token.Lexeme_comp(",")) {
		output_new_token("");
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token(" ");
		Parameter_List();
	}
}
/*<Parameter>::=  <IDs> : <Qualifier>*/
void Parameter() {
	output_production_rules("<Parameter>::=  <IDs> : <Qualifier>");
	IDs();	
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	Qualifier();
	
}
/*<Qualifier>::=  int | boolean | Real*/
void Qualifier() {	
	if (token.Lexeme_comp("int")) {
		output_production_rules("<Qualifier>::=  int");		
		
	}
	else if (token.Lexeme_comp("boolean")) {
		output_production_rules("<Qualifier>::=  boolean");
		
	}
	else if (token.Lexeme_comp("Real")) {
		output_production_rules("<Qualifier>::=  Real");
				
	}
	
}

/*<Body>::=  { <FSM_STATment List> }*/
void Body() {
	output_production_rules("<Body>::=  { <FSM_STATment List> }");	
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	FSM_STATment_List();	
}

/*<Opt Declaration List>::=  <Declaration List> | <Empty>*/
void Opt_Declaration_List() {
	output_production_rules("<Opt Declaration List>::=  <Declaration List> | <Empty>");
	if (token.Lexeme_comp("int") || token.Lexeme_comp("boolean") || token.Lexeme_comp("Real"))
		Declaration_List();
	else
		Empty();
}

/*<Declarations List> ::=  <Declaration>; | <Declaration>; < Declaration List>*/
void Declaration_List() {
	output_production_rules("<Declarations List> ::=  <Declaration>; | <Declaration>; < Declaration List>");
	Declaration();	
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	if (token.Lexeme_comp("int") || token.Lexeme_comp("boolean") || token.Lexeme_comp("Real") ) 
		Declaration_List();
}
/*"<Declaration>::=  <Qualifier> <IDs>"*/
void Declaration() {
	output_production_rules("<Declaration>::=  <Qualifier> <IDs>");
	Qualifier();
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	IDs();	
}

/*<IDs>::=  <Identifier> | <Identifier>, <IDs>*/
void IDs() {
	output_production_rules("<IDs>::=  <Identifier> | <Identifier>, <IDs>");
	token = get_lexical->nextToken();
	check_end_file ();
	
	if (token.Lexeme_comp(",")){
		output_new_token(" ");
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token(" ");
		IDs();

	}

	if (token.Lexeme_comp("]")){
		output_new_token(" ");
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token(" ");
		IDs();

	}

}

/*<FSM_STATment List>::=  <FSM_STATment> | <FSM_STATment> <FSM_STATment List>*/
void FSM_STATment_List() {
	FSM_STATment();	
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	if (token.Lexeme_comp("{") || token.token == Identifier || token.Lexeme_comp("if")|| token.Lexeme_comp("write")
		|| token.Lexeme_comp("while")  || token.Lexeme_comp("return")
		|| token.Lexeme_comp("print") || token.Lexeme_comp("scan"))
	{
		FSM_STATment_List();
	}
}
/*I added print I noticed print is used in <Write> ::= print<Expression>);*/
/*<FSM_STATment List> ::= <FSM_STATment> | <Assign> | <If> | <Return> | <Write> | <Read> | <While>*/
void FSM_STATment() {
	if (token.Lexeme_comp("{")) {
		output_production_rules("<FSM_STATment>::=  <Compound>");
		Compound();
	}
	else if (token.token == Identifier) {

		output_production_rules("<FSM_STATment>::=  <Assign>");
		Assign();
	}
	else if (token.Lexeme_comp("if")) {
		output_production_rules("<FSM_STATment>::=  <If>");
		If();
	}
	else if (token.Lexeme_comp("while")) { 
		output_production_rules("<FSM_STATment>::=  <While>");
		While();
	}
	else if (token.Lexeme_comp("return")) {
		output_production_rules("<FSM_STATment>::=  <Return>");
		Return();
	}
	else if (token.Lexeme_comp("write")) {
		output_production_rules("<FSM_STATment>::=  <write>");
		Write();
	}
	else if (token.Lexeme_comp("print")) {
		output_production_rules("<FSM_STATment>::=  <Write>");
		Write();
	}
	else if (token.Lexeme_comp("scan")) {
		output_production_rules("<FSM_STATment>::=  <Read>");
		Read();
	}
	
}


/*<Compound>::=  { <FSM_STATment List> }*/
void Compound() {
	output_production_rules("<Compound>::=  { <FSM_STATment List> }");

	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(" ");
	FSM_STATment_List();
	output_new_token("");
}

/*<Assign>::=  <Identifier> := <Expression>;*/
void Assign() {
	
	output_production_rules("<Assign>::=  <Identifier> := <Expression>;");
	
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token(":=");
	token = get_lexical->nextToken();
	check_end_file ();
	Expression();	
}

/*<If>::=  if ( <Condition> ) <FSM_STATment> endif | if ( <Condition> ) <FSM_STATment> else <FSM_STATment> endif*/
void If() {
	output_production_rules("<If>::=  if ( <Condition> ) <FSM_STATment> endif | if ( <Condition> ) <FSM_STATment> else <FSM_STATment> endif");
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	Condition();

	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	FSM_STATment();
	token = get_lexical->nextToken();
	check_end_file ();
	if (token.Lexeme_comp("endif")) {
		
		output_new_token("");
	}
	else if (token.Lexeme_comp("else")) {
		output_new_token("");
		token = get_lexical->nextToken();
		check_end_file ();
		FSM_STATment();
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
	}
	
	

}

/*<While>::=  while ( <Condition> ) <FSM_STATment>*/
void While() {
	output_production_rules("<While>::=  while ( <Condition> ) <FSM_STATment>");
	//output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	Condition();

	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	FSM_STATment();
}

/*<Return>::=  return ; | return <Expression>;*/
void Return() {
	
	output_production_rules("<Return>::=  return ; | return <Expression>;");
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	if (token.Lexeme_comp(""))
		output_new_token("");
	else {
		Expression();
		output_new_token("");
	}
}

/*<Write>::=  print ( <Expression> );*/
void Write() {
	
	output_production_rules("<Write>::=  print ( <Expression> );");	
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	Expression();

	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
}

/*<Read>::=  read ( <IDs> );*/
void Read() {
	output_production_rules("<Read>::=  scan ( <IDs> );");		
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
	token = get_lexical->nextToken();
	output_new_token("");	
	IDs();	
	output_new_token("");
	token = get_lexical->nextToken();
	check_end_file ();
	output_new_token("");
}

/*<Condition>::=  <Expression> <Relop> <Expression>*/
void Condition() {
	output_production_rules("<Condition>::=  <Expression> <Relop> <Expression>");
	Expression();
	Relop();
	Expression();
}

/*<Relop>::=  = | /= | > | < | <= | =>*/
void Relop() {
	output_production_rules("<Relop>::=  = | /= | > | < | <= | =>");
	if (token.Lexeme_comp("=")) {
		output_production_rules("<Relop>::=  =");
		output_new_token("=");
	}
	else if (token.Lexeme_comp("/=")){
		output_production_rules("<Relop>::=  /=");
		output_new_token("");
	}
	else if (token.Lexeme_comp(">")) {
		output_production_rules("<Relop>::=  >");
		output_new_token("");
	}
	else if (token.Lexeme_comp("<")) {
		output_production_rules("<Relop>::=  <");
		output_new_token("");
	}
	else if (token.Lexeme_comp("<=")) { 
		output_production_rules("<Relop>::=  <=");
		output_new_token("");
	}
	else if (token.Lexeme_comp("=>")) {
		output_production_rules("<Relop>::=  =>");
		output_new_token("");
	}
	
	token = get_lexical->nextToken();	
	
}

/*<Expression>::=  <Term><Expression_Prime>*/
void Expression() {
	output_new_token("");
	output_production_rules("<Expression>::=  <Term> <Expression_Prime>");
	Term();
	Expression_Prime();
}

/*<Expression_Prime>::=  +<Term><Expression_Prime> | -<Term><Exression_Prime>*/
void Expression_Prime() {
	if (token.Lexeme_comp("+")) {
		output_production_rules("<Expression_Prime>::=  +<Term><Expression_Prime>");				
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
		Term();
		Expression_Prime();
	}
	if (token.Lexeme_comp("-")) {
		output_production_rules("<Expression_Prime>::=  -<Term><Expression_Prime>");
	
		
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
		Term();
		Expression_Prime();
	}
	else
		Expression_Epsilon();
}

/*<Term>::=  <Factor> <Term_Prime>*/
void Term() {
	output_production_rules("<Term>::=  <Factor> <Term_Prime>");
	Factor();
	Term_Prime();
}

//<Term_Prime>::=  *<Factor><Term_Prime> | /<Factor><Term_Prime>
void Term_Prime() {
	if (token.Lexeme_comp("*")) {
		output_production_rules("<Term_Prime>::=  *<Factor><Term_Prime>");
		
		
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
		Factor();
		Term_Prime();
	}
	if (token.Lexeme_comp("/")) {
		output_production_rules("<Term_Prime>::=  /<Factor><Term_Prime>");
		
		
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
		Factor();
		Term_Prime();
	}
	else
		Term_Epsilon();
}

/*<Factor>::=  -<Primary> | <Primary>*/
void Factor() {
	if (token.Lexeme_comp("-")) {
		output_production_rules("<Factor>::=  -<Primary>");
		
		
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
		Primary();
	}
	else {		
		output_production_rules("<Factor>::=  <Identifier>");
		Primary();
	}
}

/*<Primary>::=  <Integer> | <Real> | <Expression> | true | false | <Identifier> | <Identifier> [<IDs>]*/
void Primary() {

	if (token.token == Integer) {
		output_production_rules("<Primary>::=  <Integer>");
			
		token = get_lexical->nextToken();
		check_end_file ();
		
	}
	if (token.token == Real) {
		output_production_rules("<Primary>::=  <Real>");	

		token = get_lexical->nextToken();
		check_end_file ();
		
	}
	if (token.Lexeme_comp("(")) {
		output_production_rules("<Primary>::=  ( <Expression> )");
				
		token = get_lexical->nextToken();
		check_end_file ();		
		Expression();
		output_new_token("");
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
	}
	if (token.Lexeme_comp("true")) {
		output_production_rules("<Primary>::=  true");
		
		
		token = get_lexical->nextToken();
		check_end_file ();
		output_new_token("");
	}
	if (token.Lexeme_comp("false")) {
		output_production_rules("<Primary>::=  false");		
		
		token = get_lexical->nextToken();
		check_end_file ();
		
	}
	if (token.token == Identifier) {
		output_production_rules("<Primary>::=  <Identifier>");	
		
		token = get_lexical->nextToken();	
		output_new_token(" ");

		if (token.Lexeme_comp("[")) {
			output_production_rules("<Primary>::=  <Identifier> [<IDs>]");	
			token = get_lexical->nextToken();
			check_end_file ();
			output_new_token(" ");
			IDs();
				
			token = get_lexical->nextToken();
			check_end_file ();
			output_new_token("");
		}
	}
	
}

/* <Empty>::=  epsilon*/
void Empty() {
		output_production_rules("<Empty>::=  epsilon");
}

/*<Term Prime>::=  epsilon*/
void Term_Epsilon() {	
	output_production_rules("<Term Prime>::=  epsilon");
	
}

/*<Expression Prime>::=  epsilon*/
void Expression_Epsilon() {
	output_production_rules("<Expression Prime>::=  epsilon");
	
}

void check_end_file (){	
	if (token.Lexeme_comp("")){
		cout<<"its over ";
		system ("pause");
	     exit(1);}
}

void output_new_token(const char * str) {
	
	cout << "TOKEN: " << tokens[token.token] << setw (10)<< ", Lexeme: " << token.lexeme << "\n";
	output_file << "Token: " << tokens[token.token] << ", Lexeme: " << token.lexeme << "\n";
}

void output_new_token(allowed_token allowed_token) {
	
	cout << "Token: " << tokens[token.token] << setw (10)<< ", Lexeme: " << token.lexeme << "\n";
	output_file << "Token: " << tokens[token.token] << ", Lexeme: " << token.lexeme << "\n";
}

void output_production_rules(const char * str) {
	cout << "	" << str << "\n";
	output_file << "	" << str << "\n";
}
	

/* This is my new Lexical anaylzer; not fun doing another one */
Token Lexical::nextToken()
{
	bool check_stab = false;
	int running = 0, cols = 0, FSM_STAT = 0;
	char c;

	Token ptr;
	ptr.lexeme[0] = '\0';
	ptr.token = Unknown;


	const unsigned int table_stat[18][22] = 

	{1,  2,  7,  11, 11, 11, 8,  12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 13, 0,
	1,  1,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,
	5,  2,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  14, 5,
	1,  1,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	6,  6,  6,  6,  6,  9,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
	9,  9,  9,  9,  9,  10, 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 
	9,  9,  9,  9,  9,  9,  0,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
	6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6, 
	6,  6,  6,  6,  6,  6,  6,  11, 6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  11, 6,  6,  6,
	7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
	15, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
	
	while ( !input.eof() && !check_stab && running < 1000) {
		c = input.get();
		
		if (isalpha(c))
			cols = 0;
		else if (isdigit(c))
			cols = 1;
		else if (c == '_')
			cols = 2;
		else if (c == '+')
			cols = 3;
		else if (c == '-')
			cols = 4;
		else if (c == '*')
			cols = 5;
		else if (c == '/')
			cols = 6;
		else if (c == '=')
			cols = 7;
		else if (c == '>')
			cols = 8;
		else if (c == '<')
			cols = 9;
		else if (c == '(')
			cols = 10;
		else if (c == ')')
			cols = 11;
		else if (c == '{')
			cols = 12;
		else if (c == '}')
			cols = 13;
		else if (c == '[')
			cols = 14;
		else if (c == ']')
			cols = 15;
		else if (c == ';')
			cols = 16;
		else if (c == ',')
			cols = 17;
		else if (c == '#')
			cols = 18;
		else if (c == ':')
			cols = 19;
		else if (c == '.')
			cols = 20;
		else 
			cols = 21;


		FSM_STAT = table_stat[FSM_STAT][cols];		
		
		switch (FSM_STAT) {
			case 0:
				running = 0;
				break;
			case 4:
				ptr.lexeme[running] = '\0';
				ptr.token = Identifier;
				if (check_Keyword(ptr.lexeme))
					ptr.token = Keyword;

				if (c != '\n')
					input.unget();
				check_stab = true;
				break;
			case 5:
				ptr.token = Integer;

				if (c != '\n')
					input.unget();
				check_stab = true;
				break;
			case 6:
				ptr.token = Operator;

				if (c != '\n')
					input.unget();
				check_stab = true;
				break;
			case 7:
				ptr.token = Separator;

				if (c != '\n')
					input.unget();
				check_stab = true;
				break;
			case 15:
				ptr.token = Real;

				if (c != '\n')
					input.unget();
				check_stab = true;
				break;
			default:
				ptr.lexeme[running++] = c;
		}
	}

	ptr.line_int = b;
	if (c == '\n')
		b++;
	
	ptr.lexeme[running] = '\0';

	return ptr;

}