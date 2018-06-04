#ifndef CALCPARSER_HPP
#define CALCPARSER_HPP

#include <string>
#include <stdint.h>

// using namespace std;

typedef struct CalcInstruction_t {
	// DEFINE YOUR DATA STRUCTURE HERE
	uint64_t operand;
	std::string opcode;
} CalcInstruction;

/*
 * Alternatively:
 * class CalcInstruction {
 *   // DEFINE YOUR CLASS HERE
 * };
 *
 */


class CalcParser {
public:
	static CalcInstruction parse(std::string insstr);
};

#endif // CALCPARSER_HPP
