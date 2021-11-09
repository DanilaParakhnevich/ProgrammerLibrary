#include <string>
#include <vector>
#pragma once
using namespace std;
vector<string> read(string nameOfFile); 
string getMainWord(string line);
bool isSuitable(string line, string request);