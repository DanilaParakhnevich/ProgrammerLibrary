#include <string>
#include <vector>
#include <Windows.h>
#pragma once
using namespace std;
vector<string> read(string nameOfFile); 
string getResult(HWND hWnd);
string getMainWord(string line);
bool isSuitable(string line, string request);