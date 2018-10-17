#ifndef __EQUATION_PARSER
#define __EQUATION_PARSER

#include <math.h>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Term{	
	public:
		float exponent = 1;
		float coef = 1;
		string function = "";
		
		float evalTrig(float x);
		float eval(float x);
		void print();
};

class Exp{

	private:		
		vector<Term> terms;		
		float string2number(string str);
	
	public:
		void parse(string);
		float eval(float);
		void print();
		~Exp();
};

#include "Exp.cpp"
#endif
