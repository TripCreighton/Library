#include "User.h"

User::User() {
	// Intialize vector with default values:
	for (int i = 0; i < 50; i++)
		this->ratings.push_back(0);
}

void User::setUsername(string username) {
	this->username = username;
}

bool User::setRatingAt(int index, int rating) {
	// Avoid out of range exceptions:
	if (index >= 0 && index < 50 && rating >= 0 && rating <= 5) {
		this->ratings[index] = rating;
		return true;
	}

	return false;
}

string User::getUsername() {
	return this->username;
}

int User::getRatingAt(int index) {
	// Avoid out of range exceptions:
	if (index >= 0 && index < 50) {
		return this->ratings[index];
	}

	return -1;
}