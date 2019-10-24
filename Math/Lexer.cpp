#include "Lexer.hpp"
Lexer::Lexer() : endOfLineRegex("\r\n|\r|\n"), tokenDefinitions()
{
}

Lexer::~Lexer()
{
}

void Lexer::AddDefinition(TokenDefinition tokenDefinition)
{
	tokenDefinitions.push_front(tokenDefinition);
}

void Lexer::AddDefinition(int numbrt, string reg,bool ignore)
{
	tokenDefinitions.push_front(TokenDefinition(numbrt, reg,ignore));
}

list<Token> Lexer::Tokenize(string source)
{
	list<Token> Res;

	int currentIndex = 0;
	int currentLine = 1;
	int currentColumn = 0;

	int sourcelength = source.length();

	while (currentIndex < sourcelength)
	{
		TokenDefinition matchedDefinition(0, "");
		int matchLength = 0;
		string matchedStr = "NULL";
		for (auto var = tokenDefinitions.begin(); var != tokenDefinitions.end(); ++var)
		{
			std::smatch sm;
			bool sucess = regex_search(source, sm, var->GetRegex());
			if (sucess && source.substr(0, sm.str().length()) == sm.str())
			{
				matchedDefinition = *var;
				matchLength = sm.str().length();
				matchedStr = sm.str();
				break;
			}
			else
			{
				matchedStr = "NULL";
			}
		}
		if (matchedStr == "NULL")
		{
			currentIndex += 1;
			Res.push_back(Token(0, "", TokenPosition(currentIndex, currentLine, currentColumn)));
		}
		else
		{
			if (!matchedDefinition.GetIsIgnored())
			{
				Res.push_back(Token(matchedDefinition.GetType(), matchedStr, TokenPosition(currentIndex, currentLine, currentColumn)));
			}
			std::smatch sm;
			if (regex_search(matchedStr, sm, endOfLineRegex))
			{
				currentLine += 1;
				currentColumn = 0;
			}
			else
			{
				currentColumn += matchLength;
			}
			currentIndex += matchLength;
			source.erase(0, matchLength);
		}
	}
	Res.push_back(Token(1, "", TokenPosition(currentIndex, currentLine, currentColumn)));
	return Res;
}
