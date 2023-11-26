#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cassert>
#include <cstring>
#include <utility>
#include "helper.h"
using namespace std;

string currentStruct;
string currentFunction;

int currentScope;

int tempInt;
int labelInt;

unordered_map<string, int> actualSize;
unordered_map<string, int> Size;

stack<int> scopeStack;
stack<string> ifgoto;
stack<string> forNext;
stack<string> forIncrement;
stack<SymbolTableEntry> callStack;
vector<string> declevels;
vector<pair<string, string>> stdeclevels;
vector<int> defaultStValues;
vector<int> tempStValues;
string dtype;
string lambdaReturnType;
vector<string> lambdaParamStack;
int starsCount;
int dlevels;
int parseDebug;
string forExpr;
int constInt;
int curStructSize;
vector<StructTable> globalTable;

SymbolTableEntry::SymbolTableEntry(string name, string type, int scope, vector<SymbolTableEntry> v)
{
	this->name = name;
	this->dataType = type;
	this->scope = scope;
	this->isActive = 1;
	this->levels = v;
}

SymbolTableEntry::SymbolTableEntry(string name, string type, int scope, vector<SymbolTableEntry> v, int defaultValue)
{
	this->name = name;
	this->dataType = type;
	this->scope = scope;
	this->isActive = 1;
	this->levels = v;
	this->defaultValue = defaultValue;
}

SymbolTableEntry::SymbolTableEntry()
{
}

FunctionTable::FunctionTable(string name, string rType)
{
	this->functionName = name;
	this->returnType = rType;
}

FunctionTable::FunctionTable()
{
}

void FunctionTable ::appendCode(string code)
{
	this->code.push_back(code);
}

int FunctionTable ::insertVariable(string name, string type, vector<SymbolTableEntry> table)
{
	for (int i = 0; i < localVariables.size(); i++)
	{
		if (localVariables[i].name == name and localVariables[i].isActive == 1)
		{
			return -1;
		}
	}

	SymbolTableEntry ste(name, type, scopeStack.top(), table);
	localVariables.push_back(ste);
	return 0;
}

int FunctionTable ::insertTempVariable(string name, string type)
{
	for (int i = 0; i < tempVariables.size(); i++)
	{
		if (tempVariables[i].name == name and tempVariables[i].dataType == type)
		{
			cout << "FATAL ERROR: inserting duplicate temp variable" << endl;
			return -1;
		}
	}
	vector<SymbolTableEntry> table;
	SymbolTableEntry ste(name, type, scopeStack.top(), table);
	tempVariables.push_back(ste);
	return 0;
}

int FunctionTable ::insertParam(string name, string type, vector<SymbolTableEntry> table)
{
	for (int i = 0; i < parameters.size(); i++)
	{
		if (parameters[i].name == name and parameters[i].dataType == type)
		{
			return -1;
		}
	}
	SymbolTableEntry ste(name, type, scopeStack.top(), table);
	parameters.push_back(ste);
	return 0;
}

StructTable::StructTable(string name)
{
	structName = name;
}

int StructTable::insertAttribute(string name, string type, vector<SymbolTableEntry> table, int defaultVal)
{
	for (auto i : attributes)
	{
		if (i.name == name)
		{
			return -1;
		}
	}
	SymbolTableEntry ste(name, type, scopeStack.top(), table, defaultVal);
	attributes.push_back(ste);
	return 0;
}

int StructTable::insertFunction(string functionName, string returnType)
{
	for (auto i : functionTables)
	{
		if (i.functionName == functionName)
		{
			return -1;
		}
	}

	FunctionTable func(functionName, returnType);
	functionTables.push_back(func);
	return 0;
}

int StructTable::insertConstant(string name, string value)
{
	vector<SymbolTableEntry> table;
	SymbolTableEntry ste(name, value, 1, table);
	constants.push_back(ste);
	return 0;
}

void init()
{
	actualSize = {{"int", 4},
								{"char", 1},
								{"string", 4},
								{"bool", 1},
								{"float", 4},
								{"*", 4}};

	Size = {{"int", 4},
					{"char", 4},
					{"string", 4},
					{"bool", 4},
					{"float", 4},
					{"void", 4},
					{"*", 4}};

	tempInt = 1;
	labelInt = 1;
	currentScope = 1;
	scopeStack.push(0);
	parseDebug = 0;
}

int insertStruct(string structName)
{
	for (auto i : globalTable)
	{
		if (i.structName == structName)
		{
			return -1;
		}
	}
	StructTable table(structName);
	globalTable.push_back(table);
	return 0;
}

void printSymbolTable(vector<SymbolTableEntry> v)
{
	cout << "\t\tName\t"
			 << "DataType\t"
			 << "Scope\t"
			 << "Active\t"
			 << "Default\t"
			 << "pointer\t" << endl;
	for (auto i : v)
	{
		cout << "\t\t\t\t" << i.name << "\t\t" << i.dataType << "\t\t\t" << i.scope << "\t\t" << i.isActive << "\t\t" << i.defaultValue << "\t\t\t";
		for (auto j : i.levels)
		{
			cout << j.name << "*";
		}
		cout << endl;
	}
}

void printFunctions(vector<FunctionTable> v)
{
	for (auto f : v)
	{
		cout << endl;
		cout << "\t\tfunction Name = " << f.functionName << endl;
		cout << "\t\t\tlabel = " << f.label << endl;
		cout << "\t\t\treturn value : " << f.returnType << endl;
		cout << "\t\t\tparameters : " << endl
				 << "\t\t";
		printSymbolTable(f.parameters);
		cout << "\t\t\tlocalVariables : " << endl
				 << "\t\t";
		printSymbolTable(f.localVariables);
		cout << "\t\t\ttempVariables = " << endl
				 << "\t\t";
		printSymbolTable(f.tempVariables);
		cout << "\t\t\tCode = " << endl;
		for (auto c : f.code)
		{
			cout << "\t\t\t\t" << c << endl;
		}
	}
}

void printTable()
{
	for (auto st : globalTable)
	{
		cout << "Struct Name = " << st.structName << endl;
		cout << "\tAttributes = " << endl
				 << "\t\t";
		printSymbolTable(st.attributes);
		cout << "\tConstants = " << endl
				 << "\t\t";
		printSymbolTable(st.constants);
		cout << "\tFunctions = " << endl;
		printFunctions(st.functionTables);
	}
}

void printCode()
{
	for (auto st : globalTable)
	{
		for (auto f : st.functionTables)
		{
			if (f.functionName != "main")
				continue;
			for (auto c : f.code)
			{
				cout << c << endl;
			}
			cout << endl;
		}
	}

	for (auto st : globalTable)
	{
		for (auto f : st.functionTables)
		{
			if (f.functionName == "main")
				continue;
			for (auto c : f.code)
			{
				cout << c << endl;
			}
			cout << endl;
		}
	}
}

int getStructIndex(string name)
{
	for (int i = 0; i < globalTable.size(); i++)
	{
		if (globalTable[i].structName == name)
		{
			return i;
		}
	}
	return -1;
}

int getFunctionIndex(int globalIndex, string name)
{
	for (int i = 0; i < globalTable[globalIndex].functionTables.size(); i++)
	{
		if (globalTable[globalIndex].functionTables[i].functionName == name)
		{
			return i;
		}
	}
	return -1;
}

int insertAttribute(string attributeName, string attributeType, vector<pair<string, string>> levels, vector<int> defaultVal)
{
	int index = getStructIndex(currentStruct);
	vector<SymbolTableEntry> table;

	if (levels.size() == 0)
	{
		int to_insert = 0;
		if (defaultVal.size() > 0)
			to_insert = defaultVal[0];
		vector<SymbolTableEntry> v;
		return globalTable[index].insertAttribute(attributeName, attributeType, v, to_insert);
	}

	for (int i = 0; i < levels.size(); i++)
	{
		string name = attributeName + "." + levels[i].first;
		vector<SymbolTableEntry> v;
		if (globalTable[index].insertAttribute(name, levels[i].second, v, defaultVal[i]) != 0)
		{
			return -1;
		}

		table.push_back(getVariable(name));
		table.back().name = levels[i].first;
	}
	return globalTable[index].insertAttribute(attributeName, attributeType, table, defaultVal.back());
}

int insertFunction(string functionName, string returnType)
{
	int index = getStructIndex(currentStruct);
	return globalTable[index].insertFunction(functionName, returnType);
}

int insertVariable(string variableName, string dataType, vector<string> levels)
{
	int gindex = getStructIndex(currentStruct);
	int findex = getFunctionIndex(gindex, currentFunction);

	vector<SymbolTableEntry> table;

	vector<SymbolTableEntry> attributes = globalTable[gindex].attributes;
	string newDataType;
	for (auto i : dataType)
	{
		if (i != '*')
			newDataType += i;
	}

	bool st = 1;
	if (attributes.size() == 0)
		st = 0;
	for (int i = 0; i < attributes.size(); i++)
	{
		if (newDataType == "char" || newDataType == "int" || attributes[i].name == newDataType)
		{
			st = 0;
		}
	}
	if (st)
	{
		return -2;
	}

	if (levels.size() == 0)
	{
		vector<SymbolTableEntry> v;
		return globalTable[gindex].functionTables[findex].insertVariable(variableName, dataType, v);
	}

	for (int i = levels.size() - 1; i >= 0; i--)
	{
		string name = variableName + "_" + to_string(i);
		vector<SymbolTableEntry> v;
		// if (globalTable[gindex].functionTables[findex].insertVariable(name, "int", v) != 0)
		if (globalTable[gindex].functionTables[findex].insertVariable(name, newDataType, v) != 0)
		{
			return -1;
		}
		globalTable[gindex].functionTables[findex].appendCode(name + "_" + to_string(scopeStack.top()) + " = " + levels[i]);
		table.push_back(getVariable(name));
		newDataType = "*" + newDataType;
	}
	return globalTable[gindex].functionTables[findex].insertVariable(variableName, dataType, table);
}

int insertTempVariable(string name, string type)
{
	int gindex = getStructIndex(currentStruct);
	int findex = getFunctionIndex(gindex, currentFunction);

	return globalTable[gindex].functionTables[findex].insertTempVariable(name, type);
}

int insertParam(string name, string type)
{
	int gindex = getStructIndex(currentStruct);
	int findex = getFunctionIndex(gindex, currentFunction);

	vector<SymbolTableEntry> table;
	return globalTable[gindex].functionTables[findex].insertParam(name, type, table);
}

void removeVariables()
{
	int gIndex = getStructIndex(currentStruct);
	int fIndex = getFunctionIndex(gIndex, currentFunction);
	vector<SymbolTableEntry> local = globalTable[gIndex].functionTables[fIndex].localVariables;

	for (int i = 0; i < local.size(); i++)
	{
		if (local[i].scope > currentScope)
		{
			local[i].isActive = 0;
		}
	}

	// while (!local.empty() && local.back().scope > currentScope)
	// {
	// 	local.pop_back();
	// }
	globalTable[gIndex].functionTables[fIndex].localVariables = local;
}

void setLambdaLocal()
{
	int gindex = getStructIndex(currentStruct);
	int findex = getFunctionIndex(gindex, currentFunction);
	int mindex = getFunctionIndex(gindex, "main");

	vector<SymbolTableEntry> local = globalTable[gindex].functionTables[mindex].localVariables;

	for (auto entry : local)
	{
		globalTable[gindex].functionTables[findex].localVariables.push_back(entry);
	}
}

bool verifyParams(vector<string> types)
{
	int gindex = getStructIndex(currentStruct);
	int findex = getFunctionIndex(gindex, currentFunction);

	vector<SymbolTableEntry> params = globalTable[gindex].functionTables[findex].parameters;

	if (types.size() != params.size())
	{
		return false;
	}

	for (int i = 0; i < params.size(); i++)
	{
		if (params[i].dataType != types[i])
			return false;
	}
	return true;
}

int insertConstant(string name, string value)
{
	int gindex = getStructIndex(currentStruct);

	return globalTable[gindex].insertConstant(name, value);
}

void setLabel(string fn, string label)
{
	int gIndex = getStructIndex(currentStruct);
	int fIndex = getFunctionIndex(gIndex, fn);
	globalTable[gIndex].functionTables[fIndex].label = label;
}

bool isVariable(string str)
{
	int gIndex = getStructIndex(currentStruct);
	int fIndex = getFunctionIndex(gIndex, currentFunction);

	if (fIndex != -1)
	{
		vector<SymbolTableEntry> local = globalTable[gIndex].functionTables[fIndex].localVariables;

		for (int i = 0; i < local.size(); i++)
		{
			if (local[i].name == str && local[i].isActive == 1)
			{
				return true;
			}
		}

		vector<SymbolTableEntry> parameters = globalTable[gIndex].functionTables[fIndex].parameters;
		for (int i = 0; i < parameters.size(); i++)
		{
			if (parameters[i].name == str && parameters[i].isActive == 1)
			{
				return true;
			}
		}
	}

	vector<SymbolTableEntry> global = globalTable[gIndex].attributes;
	for (int i = 0; i < global.size(); i++)
	{
		if (global[i].name == str && global[i].isActive == 1)
		{
			return true;
		}
	}
	return false;
}

SymbolTableEntry getVariable(string str)
{
	int gIndex = getStructIndex(currentStruct);
	int fIndex = getFunctionIndex(gIndex, currentFunction);
	if (fIndex != -1)
	{
		vector<SymbolTableEntry> local = globalTable[gIndex].functionTables[fIndex].localVariables;

		for (int i = 0; i < local.size(); i++)
		{
			if (local[i].name == str)
			{
				return local[i];
			}
		}

		vector<SymbolTableEntry> parameters = globalTable[gIndex].functionTables[fIndex].parameters;
		for (int i = 0; i < parameters.size(); i++)
		{
			if (parameters[i].name == str)
			{
				return parameters[i];
			}
		}
	}

	vector<SymbolTableEntry> global = globalTable[gIndex].attributes;
	for (int i = 0; i < global.size(); i++)
	{
		if (global[i].name == str)
		{
			return global[i];
		}
	}
	cout << "Should't have come here" << endl;
	assert(false);
	SymbolTableEntry ste;
	return ste;
}

string getFunctionReturnType(string functionName)
{
	int gIndex = getStructIndex(currentStruct);
	for (int i = 0; i < globalTable[gIndex].functionTables.size(); i++)
	{
		if (globalTable[gIndex].functionTables[i].functionName == functionName)
		{
			return globalTable[gIndex].functionTables[i].returnType;
		}
	}
	return "";
}

string getFunctionLabel(string functionName)
{
	int gIndex = getStructIndex(currentStruct);
	for (int i = 0; i < globalTable[gIndex].functionTables.size(); i++)
	{
		if (globalTable[gIndex].functionTables[i].functionName == functionName)
		{
			return globalTable[gIndex].functionTables[i].label;
		}
	}
	return "";
}

void setCallStack(string functionName)
{
	while (!callStack.empty())
	{
		callStack.pop();
	}

	int gindex = getStructIndex(currentStruct);
	int findex = getFunctionIndex(gindex, functionName);
	vector<SymbolTableEntry> param = globalTable[gindex].functionTables[findex].parameters;

	int s = param.size();
	for (int i = s - 1; i >= 0; i--)
	{
		callStack.push(param[i]);
	}
}

int getSize(string dataType)
{
	if (Size.find(dataType) == Size.end())
	{
		return -1;
	}
	return Size[dataType];
}

char *getCharArray(string str)
{
	char *t = (char *)calloc(str.length(), sizeof(char));
	strcpy(t, str.c_str());
	return t;
}

char *getTemp(string type)
{
	string temp = "_t" + to_string(tempInt);
	vector<string> levels;
	insertTempVariable(temp, type);
	temp += "_" + to_string(scopeStack.top());
	char *t = (char *)malloc((temp.length() - 1) * sizeof(char));
	strcpy(t, temp.c_str());
	tempInt++;
	return t;
}

char *getConst(string value)
{
	string constant = "_C" + to_string(constInt);
	insertConstant(constant, value);
	insertTempVariable(constant, "char*");
	constInt++;
	char *t = (char *)malloc((constant.length() - 1) * sizeof(char));
	strcpy(t, constant.c_str());
	return t;
}

void debug(int d)
{
	if (parseDebug == 1)
	{
		cout << "debug called" << endl;
	}
}

void appendCode(string str)
{
	int gIndex = getStructIndex(currentStruct);
	int fIndex = getFunctionIndex(gIndex, currentFunction);
	globalTable[gIndex].functionTables[fIndex].appendCode(str);
}
int getActualSize(string type)
{
	return actualSize[type];
}
string getLabel()
{
	return "label_" + to_string(labelInt++);
}

void addStructLevels(string var, string type)
{
	stdeclevels.push_back(make_pair(var, type));
}

bool isValidAttribute(string structName, string attr, string &type)
{
	int index = getStructIndex(currentStruct);
	vector<SymbolTableEntry> attributes = globalTable[index].attributes;
	for (auto attribute : attributes)
	{
		if (attribute.name == structName && attribute.dataType == "struct")
		{
			for (auto level : attribute.levels)
			{
				if (level.name == attr)
				{
					type = level.dataType;
					return true;
				}
			}
		}
	}
	return false;
}