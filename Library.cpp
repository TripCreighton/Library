#include "Library.h"

Library::Library()
{
}

Library::Library(int numBooks, int numUsers) {
	this->numBooks = numBooks;
	this->numUsers = numUsers;
}

int Library::getNumBooks() {
	return this->books.size();
}

int Library::getNumUsers() {
	return this->users.size();
}

int Library::readBooks(string filename) {
	ifstream fileStream;

	fileStream.open(filename);

	// Verify the file exists:
	if (fileStream.fail()) return -1;
	
	string tempLine;
	while (getline(fileStream, tempLine)) {
		// Filter empty lines:
		if (tempLine == "") continue;

		auto splitData = Utilities::split(tempLine, ',');

		// Verify that the split data is valid:
		if (splitData.size() < 2) continue;

		// Verify the vector has not surpassed 50 books (although this can easily be surpassed):
		if (this->books.size() >= 50) break;

		Book book;
		book.setAuthor(splitData[0]);
		book.setTitle(splitData[1]);

		this->books.push_back(book);
		this->numBooks++;
	}

	// Close the file stream:
	fileStream.close();

	return this->books.size();
}

int Library::readRatings(string filename) {
	ifstream fileStream;

	fileStream.open(filename);

	// Verify the file exists:
	if (fileStream.fail()) return -1;

	int linePos = 0;
	string tempLine;
	User currentUser;

	while (getline(fileStream, tempLine)) {
		// Filter empty lines:
		if (tempLine == "") continue;

		if (this->users.size() >= 100) break;

		// If the line is even, we're looking at numbers otherwise its likely a name:
		if (linePos % 2 != 0) {
			auto splitRatings = Utilities::splitIntegers(tempLine, ',');

			// Sort the ratings:
			for (int i = 0; i < splitRatings.size(); i++)
				currentUser.setRatingAt(i, splitRatings[i]);

			this->users.push_back(currentUser);
			currentUser = User();
		} else {
			currentUser.setUsername(Utilities::toLower(tempLine));
		}

		this->numUsers++;
		linePos++;
	}

	// Close the file stream:
	fileStream.close();

	return this->users.size();
}

void Library::viewRatings(string username, int minRating) {
	if (this->users.size() == 0 || this->books.size() == 0) {
		printf("The library has not been fully initialized.\n");

		return;
	}

	// Determine if the user exists:
	User requestedUser;
	bool wasUserFound = false;
	for (User user : this->users) {
		if (user.getUsername() == Utilities::toLower(username)) {
			requestedUser = user;

			wasUserFound = true;
		}
	}

	if (!wasUserFound) {
		printf("%s does not exist.\n", username.data());

		return;
	}

	// Find all valid ratings:
	int validRatingsFound = 0;
	for (int i = 0; i < this->books.size(); i++) {
		if (requestedUser.getRatingAt(i) >= minRating) {
			validRatingsFound++;
		}
	}

	if (validRatingsFound == 0) {
		printf("%s has not rated any books with %i or higher.\n", username.data(), minRating);
	
		return;
	}
	
	// Print all rated books above minRating:
	printf("Here are the books that %s rated", username.data());
	for (int i = 0; i < this->books.size(); i++) {
		int rating = requestedUser.getRatingAt(i);

		if (rating >= minRating) {
			printf("\nTitle : %s \nRating : %i\n-----", this->books[i].getTitle().data(), rating);
		}
	}

	printf("\n");
}

void Library::printAllBooks() {
	if (this->users.size() == 0 || this->books.size() == 0) {
		printf("The library has not been fully initialized.\n");

		return;
	}

	for (int i = 0; i < this->books.size(); i++) {
		Book book = this->books[i];

		// Calculate average rating for this book:
		float total = 0.0;
		int usersRated = 0;
		for (User user : this->users) {
			float rating = (float)user.getRatingAt(i);

			if (rating != 0) {
				usersRated++;
				total += rating;
			}
		}

		printf("(%.2f) %s by %s\n", total / (float)usersRated, book.getTitle().data(), book.getAuthor().data());
	}
}

void Library::addUser(string username) {
	if (this->users.size() >= 100) {
		printf("The library is already full. %s was not added.\n", username.data());

		return;
	}

	// Check if the user already exists:
	for (auto user : this->users) {
		if (user.getUsername() == Utilities::toLower(username)) {
			printf("%s already exists in the library.\n", username.data());

			return;
		}
	}

	// User doesn't exist and list isn't full, add them:
	printf("Welcome to the library %s\n", username.data());

	User user;
	user.setUsername(Utilities::toLower(username));

	this->users.push_back(user);
}

void Library::updateRating(string username, string title, int newRating) {
	if (this->users.size() == 0 || this->books.size() == 0) {
		printf("The library has not been fully initialized.\n");

		return;
	}

	// Find the requested user:
	int userIndex = -1;
	for (int i = 0; i < this->users.size(); i++) {
		if (Utilities::toLower(this->users[i].getUsername()) == Utilities::toLower(username)) {
			userIndex = i;
			break;
		}
	}

	if (userIndex == -1) {
		printf("%s does not exist.\n", username.data());

		return;
	}

	// Verify the rating value is valid:
	if (newRating < 0 || newRating > 5) {
		printf("%i is not valid.\n", newRating);
		
		return;
	}

	// Find the requested book:
	int bookIndex = -1;
	for (int i = 0; i < this->books.size(); i++) {
		if (Utilities::toLower(this->books[i].getTitle()) == Utilities::toLower(title)) {
			bookIndex = i;
			break;
		}
	}

	if (bookIndex == -1) {
		printf("%s does not exist.\n", title.data());

		return;
	}

	this->users[userIndex].setRatingAt(bookIndex, newRating);
	printf("The rating has been updated.\n");
}

void Library::getRecommendations(string username) {
	if (this->users.size() == 0 || this->books.size() == 0) {
		printf("The library has not been fully initialized.\n");

		return;
	}

	// Find the requested user:
	int userIndex = -1;
	for (int i = 0; i < this->users.size(); i++) {
		if (this->users[i].getUsername() == Utilities::toLower(username)) {
			userIndex = i;
			break;
		}
	}

	if (userIndex == -1) {
		printf("%s does not exist.\n", username.data());

		return;
	}

	// Determine this users most similar user:
	if (this->users.size() > 1) {
		User requestedUser = this->users[userIndex];
		vector<int> recommendationScores;

		for (int i = 0; i < this->users.size(); i++) {
			User user = this->users[i];

			int totalScore = 0;
			 
			// Loop through each book to determine the individual score:
			for (int l = 0; l < this->books.size(); l++) {
				totalScore += (int)pow(requestedUser.getRatingAt(l) - user.getRatingAt(l), 2);
			}

			recommendationScores.push_back(totalScore);
		}

		// Determine the lowest recommendation score:
		int lowestScore = recommendationScores[userIndex == 0 ? 1 : 0];
		int lowestIndex = userIndex == 0 ? 1 : 0;

		for (int i = 0; i < recommendationScores.size(); i++) {
			if (recommendationScores[i] < lowestScore && recommendationScores[i] != 0) {
				// Check if this user has atleast 1 recommended book with 3 stars:
				bool foundThreeStars = false;
				for (int l = 0; l < this->books.size(); l++) {
					if (this->users[i].getRatingAt(l) >= 3) {
						foundThreeStars = true;
						break;
					}
				}

				if (foundThreeStars) {
					lowestScore = recommendationScores[i];
					lowestIndex = i;
				}
			}
		}

		// Determine the books which are rated 3+:
		User similarUser = this->users[lowestIndex];
		bool didFindRecommendation = false;
		bool didPrint = false;
		int recommendationCount = 0;

		for (int i = 0; i < this->books.size(); i++) {
			if (similarUser.getRatingAt(i) >= 3 && requestedUser.getRatingAt(i) == 0) {
				Book book = this->books[i];
				
				if (!didPrint) {
					didPrint = true;
					printf("Here is the list of recommendations\n");
				}


				printf("%s by %s\n", book.getTitle().data(), book.getAuthor().data());
				didFindRecommendation = true;
				recommendationCount++;
			}

			// Stop after 5 recommendations:
			if (recommendationCount == 5) break;
		}

		if (!didFindRecommendation)
			printf("There are no recommendations for %s at present.\n", username.data());
	} else {
		printf("There are no recommendations for %s at present.\n", username.data());
	}
}
