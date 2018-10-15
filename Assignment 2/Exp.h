#ifndef __EQUATION_PARSER
#define __EQUATION_PARSER

#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Term{	
	public:
		int exp = 1;
		int coef = 1;
		string function = "";
		
		float evalTrig(float x);
		float eval(float x);
		void print();
};

class Exp{

	private:		
		vector<Term> terms;		
		int string2number(string str);
	
	public:
		void parse(string);
		float eval(float);
		void print();
		~Exp();
};

#include "Exp.cpp"
#endif
