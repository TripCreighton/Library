#include "Book.h"

Book::Book() {}

Book::Book(string title, string author) {
	this->title = title;
	this->author = author;
}

string Book::getTitle() {
	return this->title;
}

string Book::getAuthor() {
	return this->author;
}

void Book::setTitle(string title) {
	this->title = title;
}

void Book::setAuthor(string author) {
	this->author = author;
}