#ifndef __EQUATION_PARSER
#define __EQUATION_PARSER

#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

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
		unordered_map<float, float> cache;
		int _isEven = -1;
		float string2number(string str);
	
	public:
		void parse(string);
		float eval(float);
		bool isEven();
		void print();
		~Exp();
};

#include "Exp.cpp"
#endif
