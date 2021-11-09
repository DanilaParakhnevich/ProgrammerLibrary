#include <string>
#include <vector>
#include "header.h"
#include <algorithm>
#include <locale>

using namespace std;

string getMainWord(string line) {
	int pos = line.find_first_of(" ");
	return line.substr(0, pos + 1);
}

void toLowerCase(string& line) {
	for (size_t index = 0; index < line.size(); ++index) {
		line[index] = tolower(line[index]);
	}
}

bool isSuitable(string line, string request) {
	locale loc;
	toLowerCase(line);
	toLowerCase(request);
	return line.find(request) != std::string::npos;
}

