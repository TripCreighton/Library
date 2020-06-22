#include "Library.h"
#include <iostream>

using namespace std;

// Initialize the library:
Library library(0, 0);

int main() {

	// Print out menu options:
	printf("Select a numerical option:\n======Main Menu=====\n");
	printf("1. Read books\n");
	printf("2. Read ratings\n");
	printf("3. View ratings\n");
	printf("4. Print all books\n");
	printf("5. Update a rating\n");
	printf("6. Add a user\n");
	printf("7. Get recommendations\n");
	printf("8. Quit\n");

	int menuSelection = 0;

	cin >> menuSelection;

	if (cin.fail()) {
		printf("Invalid option.\n");
		main();
	} else {
		switch (menuSelection) {
		case 1: {
			printf("Enter a book file name:\n");
			string fileName;

			cin >> fileName;
			int output = library.readBooks(fileName);
			if (output == -1) {
				printf("No books saved to the library.\n");
			}
			else printf("Total books in the library: %i\n", output);
			main();
			break;
		}
		case 2: {
			printf("Enter a user file name:\n");
			string fileName;

			cin >> fileName;
			int output = library.readRatings(fileName);
			if (output == -1) {
				printf("No users saved to the library.\n");
			}
			else printf("Total users in the library: %i\n", output);
			main();
			break;
		}
		case 3: {
			printf("Enter a user name:\n");
			string username;
			cin >> username;

			printf("Enter a minimum rating:\n");
			int rating = 0;
			cin >> rating;

			if (cin.fail()) {
				main();
				break;
			}

			library.viewRatings(username, rating);
			main();
			break;
		}
		case 4: {
			library.printAllBooks();
			main();
			break;
		}
		case 5: {
			string username;
			string title;
			int rating = 0;

			printf("Enter a user name:\n");
			cin >> username;

			printf("Enter a book title:\n");
			cin.ignore();
			getline(cin, title);

			printf("Enter a new rating:\n");
			cin >> rating;

			if (cin.fail()) {
				main();
				break;
			}
			else {
				library.updateRating(username, title, rating);

				main();
				break;
			}
		}
		case 6: {
			string username;

			printf("Enter a user name:\n");
			cin >> username;

			library.addUser(username);

			main();
			break;
		}
		case 7: {
			string username;

			printf("Enter a user name:\n");
			cin >> username;

			library.getRecommendations(username);

			main();
			break;
		}
		case 8:
			printf("Good bye!\n");
			break;
		default:
			printf("Invalid option.\n");
			main();
			break;
		}
	}
}