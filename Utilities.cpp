#include "Utilities.h"

vector<string> Utilities::split(string input, char delimiter) {
	vector<string> result;

	string tempLine;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == delimiter) {
			result.push_back(tempLine);
			tempLine = "";

			continue;
		}

		tempLine += input[i];
	}

	result.push_back(tempLine);

	return result;
}

vector<int> Utilities::splitIntegers(string input, char delimiter) {
	auto splitData = split(input, delimiter);
	vector<int> result;

	for (auto i : splitData) {
		int convertedInt = stoi(i);

		result.push_back(convertedInt);
	}

	return result;
}

vector<float> Utilities::splitFloats(string input, char delimiter) {
	auto splitData = split(input, delimiter);
	vector<float> result;

	for (auto i : splitData) {
		int convertedFloat = stof(i);

		result.push_back(convertedFloat);
	}

	return result;
}

string Utilities::toLower(string input) {
	string result;

	for (int i = 0; i < input.size(); i++) 
		result += tolower(input[i]);

	return result;
}
