#pragma once
#include "Lexer.hpp"
#include <complex>
#include <map>
#include "Programm.hpp"

class MathParser
{
  public:
	MathParser();
	~MathParser();
	void Parse(string Expression);
	Programm Calc();

  private:
	enum ETokens
	{
		Error,
		End,
		Whitespace,
		Comma,
		Number,
		Plus,
		Minus,
		Mul,
		Div,
		BracketOpen,
		BracketClose,
		Abs,
		Sin,
		ASin,
		Cos,
		ACos,
		Tan,
		ATan,
		Sqrt,
		Pow,
		Log,
		Imag,
		Real,
		PLog,
		IPow,
		KomplexNumber,
		Pi,
		Eulernumber,
		Unknown,
		CNumber,
	};
	Lexer m_Clexer;
	int m_iCurrentPosition;
	list<Token> m_lTokens;
	list<Token>::iterator m_lTokensIterator;
	Token m_CToken;

	void Accept(ETokens token);
	void GetNextToken();

	Result Level0();
	Result Level1();
	Result Level2();

	vector<Result> GetArguments(int Number);
	vector<Item> m_Programm;
};
