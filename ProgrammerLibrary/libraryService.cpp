#include <Windows.h>
#include <string>
#include <vector>
#include "header.h"
#include <algorithm>
#include <locale>
#include <iostream>


using namespace std;

string getMainWord(string line) {
	int pos = line.find_first_of(" ");
	return line.substr(0, pos + 1);
}

string toLowerCase(string msg) {
	for_each(msg.begin(), msg.end(), [](char& c) { if ((c >= 'А' && c <= 'Я') || (c >= 'A' && c <= 'Z'))c += 32; });
	return msg;
}

bool isSuitable(string line, string request) {
	locale loc;
	return toLowerCase(line).find(toLowerCase(request)) != std::string::npos;
}

string getResult(HWND hWnd) {
	char request[20];
	GetWindowTextA(hWnd, request, 20);
	vector<string> allText = read("library.txt");
	string responce = "";
	int number = 1;
	for (size_t i = 0; i < allText.size(); ++i) {
		if (isSuitable(allText.at(i), request)) {
			responce += to_string(number) + ". " + allText.at(i) + "\r\n";
			++number;
		}
	}
	if (responce == "") {
		return "Ничего не найдено";
	}
	return responce;
}

