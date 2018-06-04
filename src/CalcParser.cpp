#include <assert.h>
#include <string>
#include <algorithm>
#include "CalcParser.hpp"

using namespace std;

CalcInstruction CalcParser::parse(std::string insstr)
{
	CalcInstruction ret;
	
	string opChar = "ADDSUBSET";
	// PUT YOUR CODE HERE
	while (insstr[0] == ' ') {
		insstr.erase(0, 1);
	}

	int alphaCnt = 0;
	int idx = 0;
	for (unsigned int i = 0; i < insstr.length() && alphaCnt < 3; i++, idx++) {
		if (opChar.find(insstr[i]) != string::npos) alphaCnt++;
	}

	// string delimiter = " ";
	// string s1 = insstr.substr(0, insstr.find(delimiter));
	// string s2 = insstr.substr(insstr.find(delimiter) + 1, string::npos);

	if (alphaCnt < 3) {
		return ret;
	}

	string s1 = insstr.substr(0, idx);
	string s2 = insstr.substr(idx + 1, string::npos);


	size_t i = 0;
	size_t len = s1.length();
	while (i < len) {
		if (opChar.find(s1[i]) == string::npos) {
			s1.erase(i, 1);
			len--;
		} else {
			i++;
		}
	}

	i = 0;
	len = s2.length();
	while (i < len) {
		if (!isdigit(s2[i])) {
			s2.erase(i, 1);
			len--;
		} else {
			i++;
		}
	}

	// s1.erase(remove(s1.begin(), s1.end(), isspace), s1.end());
	// s2.erase(remove(s2.begin(), s2.end(), isspace), s2.end());

	ret.opcode = s1;
	ret.operand = atoi(s2.c_str());

	return ret;
}
