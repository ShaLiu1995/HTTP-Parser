#include <assert.h>
#include <string>
#include "CalcFramer.hpp"

using namespace std;

static const string delim = "\r\n";

void CalcFramer::append(string chars)
{
	// PUT YOUR CODE HERE
	buffer.append(chars);
}

bool CalcFramer::hasMessage() const
{
	// PUT YOUR CODE HERE
	return !buffer.empty();
}

string CalcFramer::topMessage() const
{
	// PUT YOUR CODE HERE
	size_t idx = buffer.find_first_of(delim);

	if (idx == string::npos) {
        return "break";
	}
	return buffer.substr(0, idx);
}

void CalcFramer::popMessage()
{
	// PUT YOUR CODE HERE
	size_t idx = buffer.find_first_of(delim);

	if (idx == string::npos) {
        	return;
	}

	buffer.erase(0, idx + 1);
	if (delim.find(buffer[0]) != string::npos) {
        	buffer.erase(buffer.begin());
	}
}

void CalcFramer::printToStream(ostream& stream) const
{
	// (OPTIONAL) PUT YOUR CODE HERE--useful for debugging
	stream << buffer << endl;
}


