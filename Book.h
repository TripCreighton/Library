#include <string>
#include <iostream>

using namespace std;

class Book {
private:
	string title = "";
	string author = "";
public:
	Book();
	Book(string title, string author);

	string getTitle();
	string getAuthor();

	void setTitle(string title);
	void setAuthor(string author);
};