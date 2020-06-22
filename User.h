#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class User {
private:
	string username = "";
	vector<int> ratings;
public:
	User();

	void setUsername(string username);
	bool setRatingAt(int index, int rating);
	string getUsername();
	int getRatingAt(int index);
};