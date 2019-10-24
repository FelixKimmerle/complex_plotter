#pragma once
#include <regex>
using namespace std;
class TokenDefinition
{
public:
	TokenDefinition(int type,string Regex,bool IsIgnored = false);
	~TokenDefinition();
	bool GetIsIgnored();
	regex GetRegex();
	int GetType();
private:
	bool IsIgnored;
	regex Regex;
	int Type;
};

