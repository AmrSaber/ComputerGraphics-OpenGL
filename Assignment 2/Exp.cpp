float Term::evalTrig(float x){
			// unity function
			if (function == "x") return x;
			
			// trig functions
			if (function == "sin") return sin(x);
			if (function == "cos") return cos(x);
			if (function == "tan") return tan(x);
			if (function == "asin") return asin(x);
			if (function == "acos") return acos(x);
			if (function == "atan") return atan(x);
			
			// hyper-trig functions
			if (function == "sinh") return sinh(x);
			if (function == "cosh") return cosh(x);
			if (function == "tanh") return tanh(x);
			if (function == "asinh") return asinh(x);
			if (function == "acosh") return acosh(x);
			if (function == "atanh") return atanh(x);
			
			return 1;
		}

float Term::eval(float x) {
	//printf("c: %d, exp: %d, f:%s, val: %f\n", coef, exp, function.c_str(), coef * pow(evalTrig(x), exp));
	if (exp == 0) return coef;
	return coef * pow(evalTrig(x), exp);
}

void Term::print() {
	printf("coef: %d, power: %d, function: %s\n", coef, exp, function.c_str());
}

// =================================[Exp functions]===========================

Exp::~Exp(){
	terms.clear();
}

float Exp::eval(float x) {
	float y = 0;
	for(Term term : terms) y += term.eval(x);
	return y;
}

int Exp::string2number(string str){
	int num = 0;
	int place = 1;
	reverse(str.begin(), str.end());
	for (char d : str) {
		num += (d - '0') * place;
		place *= 10;
	}
	return num;
}

void Exp::print() {
	for (Term term : terms) term.print();
}

// accExpted syntax: [+/-]_[digit(s)]_[function: just x or trig function]_^_[digit(s)], _ == any number of spaces (0 or more)
// syntax is split into 5 stages: from 0 to 4 searching for the above respectivly
void Exp::parse(string expression) {
	string errorMsg = "Expression syntax error";
	Term *term = new Term();
	terms.clear();
	
	int stage = 0;
	for (int i = 0 ; i < expression.size() ; ++i) {
		char c = expression[i];
		if (c == ' ') continue;
		
		string num = "";
		switch(stage) {
			case 0:
				if (c != '+' && c != '-'){
					--i;
				} else {
					if (c == '-') term->coef *= -1;
				}
				++stage;
				break;
			
			case 1:
				num = "";
				if (!isdigit(c)) {
					--i;
				} else {
					while(isdigit(expression[i])){
						num += expression[i];
						++i;
					}
					--i;
					term->coef *= string2number(num);
				}
				++stage;
				break;
			
			case 2:
				if (!isalpha(c)){
					if (c == '^') throw errorMsg;
					terms.push_back(*term);
					term = new Term();
					stage = 0;
				} else {
					if (c == 'x') {
						term->function = "x";
					} else {
						while(isalpha(expression[i])) {
							term->function += expression[i];
							++i;
						};
						while(expression[i] == ' ') ++i;
						if (expression[i] != '(') throw errorMsg;
						while(expression[i] != ')') ++i;						
					}
					++stage;
				}
				break;
				
			case 3:
				if (c != '^') {
					--i;
					terms.push_back(*term);
					term = new Term();
					stage = 0;
				} else {
					++stage;
				}
				break;
				
			case 4:
				if (!isdigit(c)) throw errorMsg;
				num = "";
				while(isdigit(expression[i])){
					num += expression[i];
					++i;
				}
				--i;
				term->exp = string2number(num);
				
				terms.push_back(*term);
				term = new Term();
				stage = 0;
				break;
		}
	}
	
	if (stage == 2) {
		term->function = "x";
		term->exp = 0;
		terms.push_back(*term);
	} else if (stage == 3) {
		term->exp = 1;
		terms.push_back(*term);
	} else {
		delete term;
	}
}