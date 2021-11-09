#include <fstream>
#include <string>
#include "header.h"
#include <iostream>
#include <vector>


using namespace std;


vector<string> read(string nameOfFile) {
	ifstream fin(nameOfFile);
	vector<string> lines;
	while (fin) {
		string line;
		getline(fin, line);
		lines.push_back(line);
	}
	fin.close();
	return lines;
}