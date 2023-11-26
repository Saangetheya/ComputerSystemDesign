%{
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<unordered_map>
#include<vector>
#include<stack>
#include<unistd.h>
#include"helper.h"

using namespace std; 
extern FILE* yyin;
extern int DEBUG;		//to print information about tokeninzing
extern int parseDebug;		//to print information about parsing
int symbolDebug = 1;	//print the symbol table.

int error;
extern int yylineno;
extern "C"
{
	int yyparse(void);
	int yylex(void);
	void yyerror(const char* s)
	{
		error = -1;
		printTable();	
		printf("%s at line: %d\n", s, yylineno);
		return;
	}
	int yywrap()
	{
		return 1; 
	} 
}
%}
%union
{
	char* str;		//used for returning the identifiers from the lexer.
	int intval;

	struct			//used by grammar symbols that evaluate to expressions.
	{
		char* type;
		char* addr;
	} var;
};

%token BREAK CHAR CONST CONTINUE ELSE ELIF FLOAT FOR IN IF INT STRUCT RETURN SIZEOF VOID BOOL STRING ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN POW_ASSIGN INC_OP DEC_OP OR_OP AND_OP LE_OP GE_OP EQ_OP NE_OP C_CONST S_CONST B_CONST I_CONST F_CONST IDENTIFIER LET PRINT PRINTS SCAN VAR NULL_ MALLOC LMFUNCTION ASM POINTER MAC LEFT_SHIFT RIGHT_SHIFT

%start begin

%% 
	primary_expression
			:	IDENTIFIER POINTER IDENTIFIER {	
					string str($<str>1);
					string attr($<str>3);
					if( !isVariable(str) ){
						cout << "COMPILETIME ERROR: " << string($<str>1) << " not declared" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.type>$ = getCharArray("UNKNOWN TYPE");
						$<var.addr>$ = getCharArray("UNKNOWN VARIABLE");
					}
					else{
						SymbolTableEntry ste = getVariable(str);
						
						string sName = ste.dataType;

						if(sName[0]!='*')
						{
							cout << "COMPILETIME ERROR: " << string($<str>3) << "invalid syntax" << endl;
							cout << "At line : " << yylineno << endl;
							error = -1;
							return 1;
							$<var.type>$ = getCharArray("UNKNOWN TYPE");
							$<var.addr>$ = getCharArray("UNKNOWN VARIABLE");
						}

						string structName;
						for(auto i : sName)
						{
							if(i!='*')
								structName+=i;
						}
						string dtType;
						if(!isValidAttribute(structName,attr,dtType))
						{
							cout << "COMPILETIME ERROR: " << string($<str>3) << " invalid attribute" << endl;
							cout << "At line : " << yylineno << endl;
							error = -1;
							return 1;
							$<var.type>$ = getCharArray("UNKNOWN TYPE");
							$<var.addr>$ = getCharArray("UNKNOWN VARIABLE");
						}

						$<var.type>$ = getCharArray(dtType);
						$<var.addr>$ = getCharArray("*"+ste.name +"."+attr+ "_" + to_string(ste.scope));
					}
					debug(1);
				}	
				| IDENTIFIER '.' IDENTIFIER {	
					string str($<str>1);
					string attr($<str>3);
					if( !isVariable(str) ){
						cout << "COMPILETIME ERROR: " << string($<str>1) << " not declared" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.type>$ = getCharArray("UNKNOWN TYPE");
						$<var.addr>$ = getCharArray("UNKNOWN VARIABLE");
					}
					else{
						SymbolTableEntry ste = getVariable(str);
						string sName = ste.dataType;
						string structName;
						for(auto i : sName)
						{
							if(i!='*')
								structName+=i;
						}
						
						string dtType;
						if(!isValidAttribute(structName,attr,dtType))
						{
							cout << "COMPILETIME ERROR: " << string($<str>3) << " invalid attribute" << endl;
							cout << "At line : " << yylineno << endl;
							error = -1;
							return 1;
							$<var.type>$ = getCharArray("UNKNOWN TYPE");
							$<var.addr>$ = getCharArray("UNKNOWN VARIABLE");
						}

						$<var.type>$ = getCharArray(dtType);
						$<var.addr>$ = getCharArray(ste.name +"."+attr+ "_" + to_string(ste.scope));
					}
					debug(1);
				}	
				| IDENTIFIER	{	
					string str($<str>1);
					if( !isVariable(str) ){
						cout << "COMPILETIME ERROR: " << string($<str>1) << " not declared" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.type>$ = getCharArray("UNKNOWN TYPE");
						$<var.addr>$ = getCharArray("UNKNOWN VARIABLE");
					}
					else{
						SymbolTableEntry ste = getVariable(str);
						$<var.type>$ = getCharArray(ste.dataType);
						$<var.addr>$ = getCharArray(ste.name + "_" + to_string(ste.scope));
					}
					debug(1);
				}	
			| constant	{
					$<var.addr>$ = $<var.addr>1;
					$<var.type>$ = $<var.type>1;
					debug(2);
				}
			| '(' expression ')'{
					$<var.addr>$ = $<var.addr>2;
					$<var.type>$ = $<var.type>2;
					debug(3);
				}
			| NULL_	{
					$<var.type>$ = getCharArray("all");
					$<var.addr>$ = getTemp("int");
					appendCode(string($<var.addr>$) + " = #0");
					debug(4);
				}
			| SIZEOF '(' sizeof_arg ')'
				{
					string str($<str>3);
					if(str == "int")
					{
						$<var.type>$ = getCharArray("int");
						$<var.addr>$ = getTemp("int");
						appendCode(string($<var.addr>$) + " = #"+to_string(getActualSize("int")));
					}
					else if(str == "char")
					{
						$<var.type>$ = getCharArray("int");
						$<var.addr>$ = getTemp("int");
						appendCode(string($<var.addr>$) + " = #"+to_string(getActualSize("char")));						
					}
					else if(str == "*")
					{
						$<var.type>$ = getCharArray("int");
						$<var.addr>$ = getTemp("int");
						appendCode(string($<var.addr>$) + " = #"+to_string(getActualSize("*")));						
					}
					else if(!isVariable(str))
					{
						cout << "COMPILETIME ERROR: " << str << " not declared" << endl;	
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.type>$ = getCharArray("UNKNOWN TYPE");
						$<var.addr>$ = getCharArray("UNKNOWN VARIABLE");
					}
					else
					{
						// Lazy Allocation
						SymbolTableEntry ste = getVariable(str);
						int cur_struct_size = ste.defaultValue;
						$<var.type>$ = getCharArray("int");
						$<var.addr>$ = getTemp("int");
						appendCode(string($<var.addr>$) + " = #"+to_string(cur_struct_size));	
						
					}
				}
			; 
	sizeof_arg 
		:
			INT
				{
					$<str>$  = getCharArray("int");
				} 
			| CHAR
				{
					$<str>$  = getCharArray("char");
				} 
			| '*'
				{
					$<str>$  = getCharArray("*");
				} 
			| IDENTIFIER
				{
					$<str>$  = $<str>1;
				}
			; 

	constant
		:	I_CONST	{
					$<var.type>$ = getCharArray("int");
					$<var.addr>$ = getTemp("int");
					appendCode(string($<var.addr>$) + " = #" + string($<str>1));
					debug(5);
				}
			| C_CONST	{
					$<var.type>$ = getCharArray("char");
					$<var.addr>$ = getTemp("char");
					appendCode(string($<var.addr>$) + " = #" + string($<str>1));
					debug(6);
				}
			| S_CONST	{
					$<var.type>$ = getCharArray("*char");
					$<var.addr>$ = getTemp("*char");
					appendCode("string " + string($<var.addr>$) + " " + string($<str>1));
				}
			;

	postfix_expression
		:	primary_expression	{
					$<var.type>$ = $<var.type>1;
					$<var.addr>$ = $<var.addr>1;
				}
			| postfix_expression '[' expression ']'	{
					string type($<var.type>1);
					string addr($<var.addr>1);
					if( type[0] != '*' ){
						cout << "COMPILETIME ERROR: Cannot index a non-array type" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else{
						string indexType($<var.type>3);
						if(indexType != "int" && indexType!="char"){
							cout << "COMPILETIME ERROR: Cannot use non int/char type " << indexType << " as array index" << endl;
							cout << "At line : " << yylineno << endl;
							error = -1;
							return 1;
						}
						else{
							string index($<var.addr>3);
							string arrayType = type.substr(1, type.length());

							string temp1 = string(getTemp("int"));
							if(arrayType[0] == '*')
							{
								appendCode( temp1 + " = " + index + " * #" + to_string(getActualSize("*")) );
							}
							else
							{
								appendCode( temp1 + " = " + index + " * #" + to_string(getActualSize(arrayType)) );
							}
							string temp = string(getTemp(type));
							appendCode( temp + " = " + addr + " + " + temp1 );


							$<var.type>$ = getCharArray(arrayType);
							$<var.addr>$ = getCharArray("*"+temp);
						}
					}
				}

			| postfix_expression INC_OP	{
					string type($<var.type>1);
					if( type!="int" && type!="char" && type[0]!='*'){
						cout << "COMPILETIME ERROR: cannot apply increment operator to non int/char/* types" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else{
						$<var.addr>$ = getTemp("int");
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1));
						appendCode(string($<var.addr>1) + " = " + string($<var.addr>1) + " + " + "#1");
						$<var.type>$ = $<var.type>1;
					}
				}	

			| postfix_expression DEC_OP		
				{
					string type($<var.type>$);
					if( type!="int" && type!="char" && type[0]!='*'){
						cout << "COMPILETIME ERROR: cannot apply decrement operator to non int/char/* types" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else{
						$<var.addr>$ = getTemp("int");
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1));
						appendCode(string($<var.addr>1) + " = " + string($<var.addr>1) + " - " + "#1");

						$<var.type>$ = $<var.type>1;
					}
				}
			| IDENTIFIER '('
				{
					string functionName($<str>1);
					string returnType = getFunctionReturnType(functionName);
					if( returnType == "" )
					{
						cout << "COMPILETIME ERROR: " << functionName << " is not declared" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else
					{
						appendCode("FunctionCall " + functionName);
						setCallStack(functionName);
					}
				}
			functionParameters
				{
					string functionName($<str>1);
					string returnType = getFunctionReturnType(functionName);

					if( !callStack.empty() )
					{
						cout << "COMPILETIME ERROR: Too few arguments for the function " << functionName << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else
					{
						appendCode("call " + getFunctionLabel(functionName));
						string afterLabel = getLabel();
						appendCode(afterLabel + ":");

						$<var.addr>$ = getTemp(returnType);
						$<var.type>$ = getCharArray(returnType);
						appendCode(string($<var.addr>$) + " = ReturnVal");

					}
				}

			;
	
	functionParameters
		: ')'
		| argument_list ')'
		;

	argument_list
		: expression
			{
				string param($<var.addr>1);
				string type($<var.type>1);

				if( callStack.empty() )
				{
					cout << "COMPILETIME ERROR : Too many arguments" << endl;
					cout << "At line : " << yylineno << endl;
					error = -1;
					return 1;
				}
				else if( callStack.top().dataType != type )
				{
					cout << "COMPILETIME ERROR : Incorrect function parameter types" << endl;
					cout << "Assigning " << type << " to " << callStack.top().dataType << endl;
					cout << "At line : " << yylineno << endl;
					error = -1;
					return 1;
				}
				else
				{
					appendCode("param " + param );
					callStack.pop();
				}
			}
		| argument_list ',' expression
			{
				string param($<var.addr>3);
				string type($<var.type>3);

				if( callStack.empty() )
				{
					cout << "COMPILETIME ERROR : Too many arguments" << endl;
					cout << "At line : " << yylineno << endl;
					error = -1;
					return 1;
				}
				else if( callStack.top().dataType != type )
				{
					cout << "COMPILETIME ERROR : Incorrect function parameter types" << endl;
					cout << "At line : " << yylineno << endl;
					error = -1;
					return 1;
				}
				else
				{
					appendCode("param " + param );
					callStack.pop();
				}
			}
		;

	unary_expression
		:	postfix_expression{	
					$<var.addr>$ = $<var.addr>1;
					$<var.type>$ = $<var.type>1;
				}
			| INC_OP unary_expression{
					string type($<var.type>1);
					if( type!="int" && type!="char" && type[0]!='*'){
						cout << "COMPILETIME ERROR: cannot apply increment operator to non int/char/* types, applying to " << string($<var.type>2) << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else{
						$<var.addr>$ = $<var.addr>2;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>$) + " + " + "#1");
						$<var.type>$ = $<var.type>2;
					}
				}
			| DEC_OP unary_expression	{
					string type($<var.type>1);
					if(type!="int" && type!="char" && type[0]!='*'){
						cout << "COMPILETIME ERROR: cannot apply increment operator to non int/char/* types, applying to " << string($<var.type>2)  << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else{
						$<var.addr>$ = $<var.addr>2;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>$) + " - " + "#1");
						$<var.type>$ = $<var.type>2;
					}
				}
			| unary_operator unary_expression{
					string op($<str>1);
					string type($<var.type>2); 
					$<var.type>$ = $<var.type>2;
					if( op == "+" or op == "-" ){
						if( type != "int" ){
							cout << "COMPILETIME ERROR: cannot apply " << op << " to non number types" << endl;
							cout << "At line : " << yylineno << endl;
							error = -1;
							return 1;
							$<var.addr>$ = $<var.addr>2;
						}
						else{
							if( op == "-" ){
								if( type == "int" ){
									$<var.addr>$ = getTemp("int");
									appendCode(string($<var.addr>$) + " = " + "minus " + string($<var.addr>2));
								}
							}
						}
					}
				}
			| MALLOC '(' expression ')' {
					string type($<var.type>3);
					if( type != "int" ){
						cout << "COMPILETIME ERROR: Argument to malloc must be integer" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.type>$ = getCharArray("UNKNOWN TYPE");
						$<var.addr>$ = getTemp("int");
					}
					else
					{
						$<var.type>$ = getCharArray("*int");
						$<var.addr>$ = getTemp("*int");
						appendCode("memory " + string($<var.addr>$) + " " + string($<var.addr>3) + " #1" );
					}
				}
		;

	type_name		
		:	INT	{dtype = "int"; starsCount = 0; }
			| CHAR {dtype = "char"; starsCount = 0; }
			| STRUCT IDENTIFIER {string str($<str>2); dtype = str;starsCount = 0; }						
			;

	stars
		: '*' stars { starsCount++; }
		|
		;

	unary_operator
		:	'+'	{	$<str>$ = $<str>1;	}
			| '-'	{	$<str>$ = $<str>1;	}
			| '!'	{	$<str>$ = $<str>1;	}
			| '*'	{	$<str>$ = $<str>1;	}
			| '&'	{	$<str>$ = $<str>1;	}
			;

	bitwise_expression :
				unary_expression	{
					$<var.addr>$ = $<var.addr>1;
					$<var.type>$ = $<var.type>1;
				} 
			|	bitwise_expression RIGHT_SHIFT unary_expression {
					string type1($<var.type>1);
					string type2($<var.type>3);

					if( (type1 != "int" && type1!= "char") or (type2 != "int" && type2 != "char") )
					{
						cout << "COMPILETIME ERROR: cannot apply >> to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.addr>$ = $<var.type>1;
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.addr>$ = getTemp("int");
						$<var.type>$ = $<var.type>1;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " >> " +  string($<var.addr>3));
					}
				}
			| bitwise_expression LEFT_SHIFT unary_expression {
					string type1($<var.type>1);
					string type2($<var.type>3);

					if( (type1 != "int" && type1!= "char") or (type2 != "int" && type2 != "char") )
					{
						cout << "COMPILETIME ERROR: cannot apply << to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.addr>$ = $<var.type>1;
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.addr>$ = getTemp("int");
						$<var.type>$ = $<var.type>1;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " << " +  string($<var.addr>3));
					}
				}	
			|	bitwise_expression '|' unary_expression {
					string type1($<var.type>1);
					string type2($<var.type>3);

					if( (type1 != "int" && type1!= "char") or (type2 != "int" && type2 != "char") )
					{
						cout << "COMPILETIME ERROR: cannot apply | to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.addr>$ = $<var.type>1;
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.addr>$ = getTemp("int");
						$<var.type>$ = $<var.type>1;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " | " +  string($<var.addr>3));
					}
				}
			| bitwise_expression '&' unary_expression {
					string type1($<var.type>1);
					string type2($<var.type>3);

					if( (type1 != "int" && type1!= "char") or (type2 != "int" && type2 != "char") )
					{
						cout << "COMPILETIME ERROR: cannot apply & to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.addr>$ = $<var.type>1;
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.addr>$ = getTemp("int");
						$<var.type>$ = $<var.type>1;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " & " +  string($<var.addr>3));
					}
				}
			| bitwise_expression '^' unary_expression {
					string type1($<var.type>1);
					string type2($<var.type>3);

					if( (type1 != "int" && type1!= "char") or (type2 != "int" && type2 != "char") )
					{
						cout << "COMPILETIME ERROR: cannot apply ^ to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.addr>$ = $<var.type>1;
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.addr>$ = getTemp("int");
						$<var.type>$ = $<var.type>1;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " ^ " +  string($<var.addr>3));
					}
				};

	multiplicative_expression
		:	bitwise_expression {
					$<var.addr>$ = $<var.addr>1;
					$<var.type>$ = $<var.type>1;
				}
			|  multiplicative_expression MAC unary_expression {
					string type1($<var.type>1);
					string type2($<var.type>3);

					if( (type1 != "int" && type1!= "char") or (type2 != "int" && type2 != "char") )
					{
						cout << "COMPILETIME ERROR: cannot apply MAC to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.addr>$ = $<var.type>1;
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.addr>$ = getTemp("int");
						$<var.type>$ = $<var.type>1;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " MAC " +  string($<var.addr>3));
					}
				}
			| multiplicative_expression '*' unary_expression {
					string type1($<var.type>1);
					string type2($<var.type>3);

					if( (type1 != "int" && type1!= "char") or (type2 != "int" && type2 != "char") )
					{
						cout << "COMPILETIME ERROR: cannot apply '*' to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.addr>$ = $<var.type>1;
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.addr>$ = getTemp("int");
						$<var.type>$ = $<var.type>1;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " * " +  string($<var.addr>3));
					}
				}

			| multiplicative_expression '/' unary_expression
				{
					string type1($<var.type>1);
					string type2($<var.type>3);

					if( (type1 != "int" && type1!= "char") or (type2 != "int" && type2 != "char") )
					{
						cout << "COMPILETIME ERROR: cannot apply '/' to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.addr>$ = $<var.type>1;
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.addr>$ = getTemp("int");
						$<var.type>$ = $<var.type>1;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " / " +  string($<var.addr>3));
					}
				}

			| multiplicative_expression '%' unary_expression
				{
					string type1($<var.type>1);
					string type2($<var.type>3);

					if( (type1 != "int" && type1!= "char") or (type2 != "int" && type2 != "char") )
					{
						cout << "COMPILETIME ERROR: cannot apply '%' to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.addr>$ = $<var.type>1;
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.addr>$ = getTemp("int");
						$<var.type>$ = $<var.type>1;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " % " +  string($<var.addr>3));
					}
				}
			;

	additive_expression
		:	multiplicative_expression		
				{
					$<var.addr>$ = $<var.addr>1;
					$<var.type>$ = $<var.type>1;
				}

			| additive_expression '+' multiplicative_expression
				{
					string type1($<var.type>1);
					string type2($<var.type>3);

					if( (type1 != "int" && type1!= "char" && type1[0]!= '*') or (type2 != "int" && type2 != "char" && type2[0]!= '*'))
					{
						cout << "COMPILETIME ERROR: cannot apply '+' to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.addr>$ = $<var.type>1;
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.addr>$ = getTemp("int");
						$<var.type>$ = $<var.type>1;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " + " +  string($<var.addr>3));
					}
				}

			| additive_expression '-' multiplicative_expression
				{
					string type1($<var.type>1);
					string type2($<var.type>3);

					if(  (type1 != "int" && type1!= "char" && type1[0]!= '*') or (type2 != "int" && type2 != "char" && type2[0]!= '*'))
					{
						cout << "COMPILETIME ERROR: cannot apply '+' to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						$<var.addr>$ = $<var.type>1;
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.addr>$ = getTemp("int");
						$<var.type>$ = $<var.type>1;
						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " - " +  string($<var.addr>3));
					}
				}
			;
	
	relational_expression
		:	additive_expression				
				{
					$<var.addr>$ = $<var.addr>1;
					$<var.type>$ = $<var.type>1;
				}

			| relational_expression '<' additive_expression
				{
					string type1($<var.type>1);
					string type2($<var.type>3);

					if((type1 != "int" && type1 != "char" ) or (type2 != "int" && type2 != "char" ))
					{
						cout << "COMPILETIME ERROR: cannot apply '<' to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else
					{
						$<var.type>$ = getCharArray("bool");
						$<var.addr>$ = getTemp("bool");

						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " < " + string($<var.addr>3));
					}
				}

			| relational_expression '>' additive_expression
				{
					string type1($<var.type>1);
					string type2($<var.type>3);

					if((type1 != "int" && type1 != "char" ) or (type2 != "int" && type2 != "char" ))
					{
						cout << "COMPILETIME ERROR: cannot apply '>' to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else
					{
						$<var.type>$ = getCharArray("bool");
						$<var.addr>$ = getTemp("bool");

						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " > " + string($<var.addr>3));
					}
				}

			| relational_expression LE_OP additive_expression
				{
					string type1($<var.type>1);
					string type2($<var.type>3);

					if( (type1 != "int" && type1 != "char" ) or (type2 != "int" && type2 != "char" ) )
					{
						cout << "COMPILETIME ERROR: cannot apply '<=' to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else
					{
						$<var.type>$ = getCharArray("bool");
						$<var.addr>$ = getTemp("bool");

						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " <= " + string($<var.addr>3));
					}
				}

			| relational_expression GE_OP additive_expression
				{
					string type1($<var.type>1);
					string type2($<var.type>3);

					if((type1 != "int" && type1 != "char" ) or (type2 != "int" && type2 != "char" ))
					{
						cout << "COMPILETIME ERROR: cannot apply '<=' to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else
					{
						$<var.type>$ = getCharArray("bool");
						$<var.addr>$ = getTemp("bool");

						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " >= " + string($<var.addr>3));
					}
				}
			;
	
	equality_expression
		:	relational_expression			
				{
					$<var.addr>$ = $<var.addr>1;
					$<var.type>$ = $<var.type>1;
				}

			| equality_expression EQ_OP relational_expression
				{
					string type1($<var.type>1);
					string type2($<var.type>3);

					// if(( type1 != "int" or type2 != "int" ) && type2!= "all" && type1!="all")
					if(false && (type1 != "int" or type2 != "int" ))
					{
						cout << "COMPILETIME ERROR: cannot apply '==' to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else
					{
						$<var.type>$ = getCharArray("bool");
						$<var.addr>$ = getTemp("bool");

						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " == " + string($<var.addr>3));
					}
				}

			| equality_expression NE_OP relational_expression
				{
					string type1($<var.type>1);
					string type2($<var.type>3);

					// if( (type1 != "int" or type2 != "int") && type2!= "all" && type1!="all")
					if(false && (type1 != "int" or type2 != "int" ))
					{
						cout << "COMPILETIME ERROR: cannot apply '!=' to arguements of types: " << type1 << ", " << type2 << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else
					{
						$<var.type>$ = getCharArray("bool");
						$<var.addr>$ = getTemp("bool");

						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " != " + string($<var.addr>3));
					}
				}
			;

	logical_and_expression
		:	equality_expression				
				{
					$<var.addr>$ = $<var.addr>1;
					$<var.type>$ = $<var.type>1;
				}

			| logical_and_expression AND_OP equality_expression
				{
					if( strcmp($<var.type>1, "bool") != 0 or strcmp($<var.type>3, "bool") != 0 )
					{
						cout << "COMPILETIME ERROR: cannot apply '&&' to non-boolean operands" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						
						$<var.addr>$ = getTemp("bool");
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.type>$ = getCharArray("bool");
						$<var.addr>$ = getTemp("bool");

						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " && " + string($<var.addr>3));
					}
				}
			;
	
	logical_or_expression
		:	logical_and_expression			
				{
					$<var.addr>$ = $<var.addr>1;
					$<var.type>$ = $<var.type>1;
				}

			| logical_or_expression OR_OP	logical_and_expression
				{
					if( strcmp($<var.type>1, "bool") != 0 or strcmp($<var.type>3, "bool") != 0 )
					{
						cout << "COMPILETIME ERROR: cannot apply '||' to non-boolean operands" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
						
						$<var.addr>$ = getTemp("bool");
						$<var.type>$ = $<var.type>1;
					}
					else
					{
						$<var.type>$ = getCharArray("bool");
						$<var.addr>$ = getTemp("bool");

						appendCode(string($<var.addr>$) + " = " + string($<var.addr>1) + " || " + string($<var.addr>3));
					}
				}
			;

	expression
		: 	logical_or_expression			
				{
					$<var.addr>$ = $<var.addr>1;
					$<var.type>$ = $<var.type>1;
				}
			| B_CONST
				{
					$<var.addr>$ = getCharArray($<str>1);
					$<var.type>$ = getCharArray("bool");
				}
			;

	assignment_operator
		:	'='						{	$<str>$ = $<str>1;	}
			/*| MUL_ASSIGN			{	$<str>$ = $<str>1;	}
			| DIV_ASSIGN			{	$<str>$ = $<str>1;	}
			| MOD_ASSIGN			{	$<str>$ = $<str>1;	}
			| ADD_ASSIGN			{	$<str>$ = $<str>1;	}
			| SUB_ASSIGN			{	$<str>$ = $<str>1;	}
			| POW_ASSIGN			{	$<str>$ = $<str>1;	}
			*/
			;

	assignment_expression
		: 	unary_expression assignment_operator expression
				{
					string op($<str>2);
					string var($<var.addr>1);
					string val($<var.addr>3);

					string type1($<var.type>1);
					string type2($<var.type>3);

					appendCode(var + " = " + val);
					if( type2!="all" && type1 != type2 )
					{
						cout << "COMPILETIME WARNING: assigning " << type2 << " to " << type1 << endl;
						cout << "At line : " << yylineno << endl;
					}
				}
			;


	declaration_expression
			:type_name declarationlist
			;
	
	declarationlist
			:	declaration ',' declarationlist		
			|	declaration
			;
	
	declaration
		:	stars IDENTIFIER 
				{
					declevels.clear();
				}
			brackets
				{
					string var = string($<str>2);
					string type = dtype;

					for( int i = 0 ; i < declevels.size() ;i++ )
					{
						type = "*" + type;
					}

					for( int i = 0 ; i < starsCount ; i++ )
					{
						type = "*" + type;
					}
					starsCount = 0;
					int resp = insertVariable(var, type, declevels);
					if( resp == -1 )
					{	
						cout << "COMPILETIME ERROR: Redeclaration of an already existing variable " << var << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					if( resp == -2 )
					{	
						cout << "COMPILETIME ERROR: Struct not declared " << dtype << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					if( declevels.size() != 0 ){
						SymbolTableEntry ste = getVariable(var);
						if(type[0] == '*')
						{
							appendCode("memory " + var+"_"+ to_string(ste.scope) + " " + declevels[0] + " #" + to_string(getActualSize("*")));
						}
						else
						{
							appendCode("memory " + var+"_"+ to_string(ste.scope) + " " + declevels[0] + " #" + to_string(getActualSize(dtype)));
						}
					}
				}
			;

	brackets
		: brackets '[' expression ']'
				{
					string expr($<var.addr>3);
					string type($<var.type>3);

					if( type != "int" )
					{
						cout << "COMPILETIME ERROR: cannot use not int type for array sizes" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else
					{
						declevels.push_back(expr);
					}
				}
		|
		;

	conditional_expression
		: IF '(' expression ')'
			{
				string expr($<var.addr>3);
				
				string elseLabel = getLabel();
				$<str>1 = getCharArray(elseLabel);

				string afterIf = getLabel();
				ifgoto.push(afterIf);

				appendCode("if ( " + expr + " == #0 ) goto " + elseLabel);
			}
		'{'
			{
				currentScope++;
				scopeStack.push(currentScope);
			}
		statement_list
			{
				appendCode("goto " + ifgoto.top());
				appendCode(string($<str>1) + ":");
			}
		'}'
			{
				currentScope--;
				scopeStack.pop();
				removeVariables();
			}

		else_statement
			{
			}
		;
	
	else_statement
		:	ELIF '(' expression ')'
			{
				string expr($<var.addr>3);
				string elseLabel = getLabel();
				$<str>1 = getCharArray(elseLabel);

				appendCode("if ( " + expr + " == #0 ) goto " + elseLabel);
			}
		'{'
			{
				currentScope++;
				scopeStack.push(currentScope);
			}
		statement_list
			{
				appendCode("goto " + ifgoto.top());
				appendCode(string($<str>1) + ":");
			}
		'}'
			{
				currentScope--;
				scopeStack.pop();
				removeVariables();
			}
		else_statement
			{
			}
		| ELSE '{'
			{
				currentScope++;
				scopeStack.push(currentScope);
			}

		statement_list
			{
				appendCode(ifgoto.top() + ":");
				ifgoto.pop();
			}
		'}'
			{
				currentScope--;
				scopeStack.pop();
				removeVariables();
			}
		| 
			{
				appendCode(ifgoto.top() + ":");
				ifgoto.pop();
			}
		;
	
	for_expression	
		:	FOR '(' 
				{
					currentScope++;
					scopeStack.push(currentScope);
				}

			loop_initialization_list ';'
				{
					string forStart = getLabel();
					$<str>1  = getCharArray(forStart);
					appendCode(forStart+":");
				}
			loop_condition ';'
				{
					string expr = forExpr;

					string statementstart = getLabel();

					string incrementstart = getLabel();
					forIncrement.push(incrementstart);

					string endfor = getLabel();
					forNext.push(endfor);

					$<str>4 = getCharArray(statementstart);
					$<var.addr>6 = getCharArray(incrementstart);
					$<var.type>6 = getCharArray(endfor);

					appendCode("if ( " + expr + " == #0 ) goto " + endfor);
					appendCode("goto " + statementstart);
					appendCode(incrementstart + ":");
				}

			loop_increment_list 			
				{
					appendCode("goto " + string($<str>1));
					appendCode(string($<str>4) + ":");
				}

			')' '{' for_statement_list 			
				{
					appendCode("goto " + string($<var.addr>6));
					appendCode(string($<var.type>6) + ":");
				}

			'}'								
				{
					currentScope--;
					scopeStack.pop();
					removeVariables();
					forIncrement.pop();
					forNext.pop();
				}
			;

	for_statement_list :
		statement_list | ;

	loop_initialization_list										
		:	assignment_expression ',' loop_initialization_list	{}
			| assignment_expression	{}
			| {}
			;
	
	loop_condition
		: 	expression						
				{
					if( strcmp($<var.type>1, "bool") != 0 )
					{
						cout << "COMPILETIME ERROR: non-boolean expression is being used as loop condition" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					forExpr = string($<var.addr>1);
				}

			|
				{
					forExpr = string(getTemp("bool"));
					appendCode(forExpr + " = #1");
				}
			;
	
	loop_increment_list
		:	expression ',' loop_increment_list	
				{
					if( parseDebug == 1 )
					{
						cout << "loop_incr -> expression , loop_incr" << endl;
					}
				}

			| expression					
				{
					if( parseDebug == 1 )
					{
						cout << "loop_incr -> expression" << endl;
					}
				}

			| 
				{
					if( parseDebug == 1 )
					{
						cout << "loop_incr -> expression" << endl;
					}
				}
			;


	lambda_expression
		:	 LMFUNCTION 
				{
					lambdaParamStack.clear();
				}
			'<'
			lamda_return_type 
			'('
			lambda_param_types
			')'
			'>'
			IDENTIFIER
				{
					if(currentFunction != "main")
					{
						cout << "COMPILETIME ERROR: Lambda functions need to be declared inside main" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}

					string functionName($<str>9);
					string type = lambdaReturnType;
					string returnType = type;
					int res = insertFunction(functionName,returnType);
					currentFunction = functionName;
					string functionStart = getLabel();
					appendCode(functionStart + ":");
					setLabel(currentFunction, functionStart);

				}
			'='
			'['
			'&'
			']'
			'('
				{
					currentScope++;
					scopeStack.push(currentScope);
					setLambdaLocal();
				}
			lambda_params
			')'
				{
					if(!verifyParams(lambdaParamStack))
					{
						cout << "COMPILETIME ERROR: Inconsistent Parameters" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}

				}
			'{'
			lambda_body
			'}'
				{
					currentScope--;
					scopeStack.pop();
					removeVariables();
					currentFunction = "main";
				}
			;

	
	lamda_return_type 
		: 
				type_name
				stars 
				{
					string newType;
					for(int i=0;i<starsCount;i++)
					{
						newType+='*';
					}
					starsCount = 0;
					dtype = newType + dtype;
					lambdaReturnType = dtype;
				};
	
	lambda_param_types :
			type_name stars
				{
					string newType;
					for(int i=0;i<starsCount;i++)
					{
						newType+='*';
					}
					starsCount = 0;
					dtype = newType + dtype;
					lambdaParamStack.push_back(dtype);
				} 
			',' lambda_param_types
			| type_name 	stars			
				{
					string newType;
					for(int i=0;i<starsCount;i++)
					{
						newType+='*';
					}
					starsCount = 0;
					dtype = newType + dtype;
					lambdaParamStack.push_back(dtype);
				} 
			|
			;

	lambda_params : functionArguments |
			;
	
	lambda_body :
			statement_list ;
	
	statement
		:  lambda_expression ';'
			| assignment_expression ';'
			| declaration_expression ';'
			| conditional_expression
			| for_expression
			| expression ';'
			| flow_control_statement ';'
			| ASM '(' S_CONST ',' S_CONST ',' IDENTIFIER ')' ';'
				{
					string code = "asm " + string($<str>3) + " " + string($<str>5) + " ";
					string str($<str>7);
					if( !isVariable(str) ){
						cout << "COMPILETIME ERROR: " << str << " not declared" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else{
						SymbolTableEntry ste = getVariable(str);
						code += ste.name+"_"+to_string(ste.scope) + " ";
					}
					//appendCode("asm " + ste.name+"_"+to_string(ste.scope) + " " + string($<str>5) + " " + string($<str>7) + " " + string($<str>9));
					appendCode(code);
				}
			| RETURN expression ';'
				{
					string returnVal($<var.addr>2);
					appendCode("Return " + returnVal);
					
					if( parseDebug == 1 )
					{
						cout << "statement -> return expression" << endl;
					}
				}

			| RETURN ';'
				{
					appendCode("return");
					
					if( parseDebug == 1 )
					{
						cout << "statement -> return" << endl;
					}
				}
			| error ';'
				{
					error = -1;
					return 1;
				}
			;
	
	flow_control_statement
		:	BREAK
				{
					if( forNext.empty() == true )
					{
						cout << "COMPILETIME ERROR: cannot use break outside for loop" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else
					{
						appendCode("goto " + forNext.top());
					}
				}
			| CONTINUE
				{
					if( forIncrement.empty() == true )
					{
						cout << "COMPILETIME ERROR: cannot use continue outside for loop" << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					else
					{
						appendCode("goto " + forIncrement.top());
					}
				}

	statement_list
		: 	statement statement_list
			| statement
			;

	begin:
		{
			currentStruct = "main";
			insertStruct(currentStruct);
		}
		blocks
		;

	blocks:
		attribute blocks
		| functionPrefix blocks
		| 
		;
	
	attribute
		:	 
			 type_name stars IDENTIFIER ';'
				{
					string addr($<str>3);
					string type = dtype;
					for( int i = 0 ; i < starsCount ; i++ )
					{
						type = "*" + type;
					}
					starsCount = 0;
					stdeclevels.clear();
					defaultStValues.clear();
					insertAttribute(addr, type,stdeclevels,defaultStValues);
				}
			 | type_name stars IDENTIFIER 
			 '=' 
			 attribute_constant
				{
					string addr($<str>3);
					string type = dtype;
					for( int i = 0 ; i < starsCount ; i++ )
					{
						type = "*" + type;
					}

					string rAddr($<str>5);
					string rType($<str>5);

					if(rType != "char" && rType != "*char")
						rType ="int";

					if(type != rType)
					{
						cout << "COMPILETIME ERROR: Types don't match" << addr << " and "<<rAddr<<endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					stdeclevels.clear();
					defaultStValues.clear();
					starsCount = 0;

					if(rType == "int")
						defaultStValues.push_back(stoi(rAddr)); 
					
					insertAttribute(addr, type,stdeclevels,defaultStValues);
					defaultStValues.clear();
				}
			 ';'
				| struct_declaration ';'
		;

	attribute_constant
		:	I_CONST	{
					$<var.addr>$ = getCharArray($<str>1);
				}
			| C_CONST	{
					$<var.type>$ = getCharArray("char");
				}
			| S_CONST	{
					$<var.type>$ = getCharArray("*char");
				}
			;

	struct_declaration
		:	STRUCT IDENTIFIER struct_body  			 
				{
					string var = string($<str>2);
					string type = "struct";
					for( int i = 0 ; i < starsCount ; i++ )
					{
						type = "*" + type;
					}
					starsCount = 0;
					defaultStValues.push_back(curStructSize);
					if( insertAttribute(var, type, stdeclevels,defaultStValues) == -1 )
					{	
						cout << "COMPILETIME ERROR: Redeclaration of an already existing variable " << var << endl;
						cout << "At line : " << yylineno << endl;
						error = -1;
						return 1;
					}
					actualSize[var] = curStructSize;
				};

	struct_body
		: '{' 
				{
					defaultStValues.clear();
					stdeclevels.clear();
					curStructSize = 0;
				}

			struct_attributes '}';
	
	struct_attributes
		: type_name stars 
				IDENTIFIER
				{
					tempStValues.clear();
				} 
				st_brackets';'
				{
					string var = string($<str>3);
					string type = dtype;

					for( int i = 0 ; i < starsCount ; i++ )
					{
						type = "*" + type;
					}
					starsCount = 0;
					int typeSize = getActualSize(type);
					if(type[0] == '*')
					{
						typeSize = 4;
					}
					int tot_size = 1*typeSize;
					for( int i = declevels.size()-1 ; i >=0 ; i-- )
					{
						addStructLevels(var+"_"+to_string(i),type);
						defaultStValues.push_back(tempStValues[i]);
						type = "*" + type;
						tot_size*=tempStValues[i];
					}

					addStructLevels(var,type);
					defaultStValues.push_back(tot_size);
					curStructSize+=tot_size;
					declevels.clear();
				} 
			struct_attributes
		| ;

	st_brackets : st_brackets '[' st_const ']'
				{
					string expr($<str>3);
					declevels.push_back(expr);
				}
		|
		;

	st_const : I_CONST 
							{
								string var($<str>1);
								$<str>$ = getCharArray(var);
								tempStValues.push_back(stoi(var));

							}
					 | IDENTIFIER
					 	{
							string var($<str>1);
 
							if(isVariable(var))
							{
								SymbolTableEntry ste = getVariable(var);
								if(ste.dataType != "int")
								{
									cout << "COMPILETIME ERROR: " << var << " does not have int type "<<endl;
									cout << "At line : " << yylineno << endl;
									error = -1;
									return 1;				
								}
	
								$<str>$ = getCharArray(var);
								tempStValues.push_back(ste.defaultValue);
							}
							else
							{
									cout << "COMPILETIME ERROR: " << var << " not declared "<<endl;
									cout << "At line : " << yylineno << endl;
									error = -1;
									return 1;
							}
						} 
					 ;

	functionPrefix:
		type_name stars IDENTIFIER '('
				{
					string functionName($<str>3);
					string type = dtype;
					for( int i = 0 ; i < starsCount ; i++ )
					{
						type = "*" + type;
					}
					string returnType = type;
					int res = insertFunction(functionName,returnType);
					currentFunction = functionName;
					currentScope++;
					scopeStack.push(currentScope);
				}
		functionSuffix
		;

	functionSuffix:
		')'
			{
				currentScope--;
				scopeStack.pop();

				string functionStart = getLabel();
				appendCode(functionStart + ":");
				setLabel(currentFunction, functionStart);
			}
		statement_block
		| functionArguments ')'
			{
				currentScope--;
				scopeStack.pop();

				string functionStart = getLabel();
				appendCode(functionStart + ":");
				setLabel(currentFunction, functionStart);
			}
		statement_block							
		;
	
	functionArguments:
		type_name stars IDENTIFIER
			{
				string name($<str>3);
				string type = dtype;
				for( int i = 0 ; i < starsCount ; i++ )
				{
					type = "*" + type;
				}
				insertParam(name, type);
			}
		| functionArguments ',' type_name stars IDENTIFIER
			{
				string name($<str>5);
				string type = dtype;
				for( int i = 0 ; i < starsCount ; i++ )
				{
					type = "*" + type;
				}
				starsCount = 0;
				insertParam(name, type);
			}
		;

	statement_block
		:	'{' 						
				{
					currentScope++;
					scopeStack.push(currentScope);
					$<intval>1 = scopeStack.top();
				}

			statement_list	'}'			
				{
					currentScope--;
					scopeStack.pop();
					removeVariables();
					
					if( parseDebug == 1 )
					{
						cout << "statement_block -> { statementlist }" << endl;
					}
				}
											
			| '{' '}'					{
												if( parseDebug == 1 )
												{
													cout << "statementblock -> {}" << endl;
												}
										}
			;
%%


int main( int argcount, char* arguements[] )
{
	error = 0;
	yyin = fopen(arguements[1], "r");
	init();
	int i = yyparse();

    std::ofstream outputFile("output.txt",std::ios::trunc);
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(outputFile.rdbuf());
		if( i != 0 or error != 0 )
		{
			cout << "Error = " << error << endl<<endl;
			printTable();
			std::cout.rdbuf(coutbuf);
			outputFile.close();

			std::ofstream outputFile1("code.tac",std::ios::trunc);
    
			std::streambuf *coutbuf1 = std::cout.rdbuf();
    	std::cout.rdbuf(outputFile1.rdbuf());

    	std::cout.rdbuf(coutbuf1);

    	outputFile1.close();
			return 0;
		}
		cout<<"Successfully Compiled"<<endl<<endl;

    printTable();

		std::cout.rdbuf(coutbuf);

    outputFile.close();

		std::ofstream outputFile1("code.tac",std::ios::trunc);
    std::streambuf *coutbuf1 = std::cout.rdbuf();
    std::cout.rdbuf(outputFile1.rdbuf());

    printCode();

    std::cout.rdbuf(coutbuf1);

    outputFile1.close();

		
	// translate();
}
