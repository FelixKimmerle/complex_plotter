#include "TokenDefinition.hpp"

TokenDefinition::TokenDefinition(int type, string Regex, bool IsIgnored)
{
	this->Type = type;
	this->Regex = regex(Regex);
	this->IsIgnored = IsIgnored;
}

TokenDefinition::~TokenDefinition()
{
}

bool TokenDefinition::GetIsIgnored()
{
	return IsIgnored;
}

regex TokenDefinition::GetRegex()
{
	return Regex;
}

int TokenDefinition::GetType()
{
	return Type;
}
