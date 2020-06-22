#pragma once
#include <string>
#include <vector>

using namespace std;

class Utilities {
public:
	static vector<string> split(string input, char delimiter);
	static vector<int> splitIntegers(string input, char delimiter);
	static vector<float> splitFloats(string input, char delimiter);
	static string toLower(string input);
};