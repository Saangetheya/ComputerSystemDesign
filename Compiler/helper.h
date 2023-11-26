#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <utility>
using namespace std;

class SymbolTableEntry
{
public:
	string name;
	string dataType;
	int scope;
	int defaultValue;
	int isActive;
	vector<SymbolTableEntry> levels;

	SymbolTableEntry(string, string, int, vector<SymbolTableEntry>);
	SymbolTableEntry(string, string, int, vector<SymbolTableEntry>, int);
	SymbolTableEntry();
};

class FunctionTable
{
public:
	string functionName;
	string label;
	string returnType;
	vector<SymbolTableEntry> parameters;
	vector<SymbolTableEntry> localVariables;
	vector<SymbolTableEntry> tempVariables;
	vector<string> code;

	FunctionTable(string name, string returnType);
	FunctionTable();
	void appendCode(string code);
	int insertVariable(string name, string type, vector<SymbolTableEntry> table);
	int insertTempVariable(string name, string type);
	int insertParam(string name, string type, vector<SymbolTableEntry> table);

	string getFunctionReturnType();
};

class StructTable
{
public:
	string structName;
	vector<SymbolTableEntry> attributes;
	vector<FunctionTable> functionTables;
	vector<SymbolTableEntry> constants;

	StructTable(string name);

	int insertAttribute(string name, string type, vector<SymbolTableEntry> table, int defaultVal);
	int insertFunction(string functionName, string returnType);
	int insertConstant(string name, string value);
};

extern string currentStruct;
extern string currentFunction;
extern int currentScope;

extern int tempInt;
extern int labelInt;

extern unordered_map<string, int> actualSize;
extern unordered_map<string, int> Size;

extern stack<int> scopeStack;
extern stack<string> ifgoto;
extern stack<string> forNext;
extern stack<string> forIncrement;
extern stack<SymbolTableEntry> callStack;
extern vector<string> declevels;
extern vector<pair<string, string>> stdeclevels;
extern vector<int> defaultStValues;
extern vector<int> tempStValues;
extern string dtype;
extern string lambdaReturnType;
extern vector<string> lambdaParamStack;
extern int starsCount;
extern int dlevels;
extern int parseDebug;
extern string forExpr;
extern int constInt;
extern int curStructSize;
extern vector<StructTable> globalTable;

SymbolTableEntry getVariable(string structName);

void init();
int insertStruct(string name);
void printTable();
int insertAttribute(string name, string type, vector<pair<string, string>> stdeclevels, vector<int> defaultVal);
int insertFunction(string name, string returnType);
int insertVariable(string variableName, string dataType, vector<string> declevels);
int insertParam(string, string);
int insertConstant(string name, string value);

int getSize(string dataType);
char *getCharArray(string str);
char *getTemp(string type);
char *getConst(string value);
bool isVariable(string str);
void debug(int d);
void appendCode(string str);
int getActualSize(string type);
string getLabel();
string getLabel();
void setLabel(string fn, string label);
string getFunctionLabel(string functionName);
string getFunctionReturnType(string functionName);
void setCallStack(string functionName);
bool verifyParams(vector<string> types);
void removeVariables();
void setLambdaLocal();
void addStructLevels(string var, string type);
bool isValidAttribute(string structName, string attr, string &type);
void printCode();
// void translate();
