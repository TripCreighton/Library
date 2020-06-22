#pragma once
#include "Book.h"
#include "User.h"
#include "Utilities.h"
#include <fstream>
#include <cmath>

class Library {
private:
	vector<Book> books;
	vector<User> users;
	int numBooks;
	int numUsers;
public:
	Library();
	Library(int numBooks, int numUsers);

	int getNumBooks();
	int getNumUsers();
	int readBooks(string filename);
	int readRatings(string filename);
	void viewRatings(string username, int minRating);
	void printAllBooks();
	void addUser(string username);
	void updateRating(string username, string title, int newRating);
	void getRecommendations(string username);
};

