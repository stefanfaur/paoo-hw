#include "Book.h"

#include <iostream>

// constructor
Book::Book(const std::string& title, const std::string& author, int year,
           const std::string& code,
           const std::vector<std::string>& pageContents)
    : title(title),
      author(author),
      year(year),
      code(code),
      currentPageIndex(0),
      bookmarkedPageIndex(0) {
  for (int i = 0; i < pageContents.size(); ++i) {
    std::string content = pageContents[i];
    pages.emplace_back(content);
  }
  std::cout << "Book created: " << title << " with " << pages.size()
            << " pages." << std::endl;
}

// assignment operator override
Book& Book::operator=(const Book& other) {
  if (this != &other) {  // Self-assignment check
    title = other.title;
    author = other.author;
    year = other.year;
    code = other.code;
    currentPageIndex = other.currentPageIndex;
    bookmarkedPageIndex = other.bookmarkedPageIndex;
    pages = other.pages;  // Use the vector's assignment
  }
  std::cout << "Book assigned: " << title << std::endl;
  return *this;
}

// destructor
Book::~Book() { std::cout << "Book destroyed: " << title << std::endl; }

void Book::openBook() {
  std::cout << "Opening " << title << " at page " << currentPageIndex + 1 << "."
            << std::endl;
}

void Book::turnPage() {
  if (currentPageIndex < pages.size() - 1) {
    currentPageIndex++;
    std::cout << "Turning to page " << currentPageIndex + 1 << " in " << title
              << "." << std::endl;
  } else {
    std::cout << "You have reached the end of " << title << "." << std::endl;
  }
}

void Book::bookmarkPage() {
  bookmarkedPageIndex = currentPageIndex;
  std::cout << "Bookmarked page " << bookmarkedPageIndex + 1 << " in " << title
            << "." << std::endl;
}

void Book::goToBookmark() {
  if (bookmarkedPageIndex >= 0 && bookmarkedPageIndex < pages.size()) {
    currentPageIndex = bookmarkedPageIndex;
    std::cout << "Returning to bookmarked page " << currentPageIndex + 1
              << " in " << title << "." << std::endl;
  } else {
    std::cout << "No valid bookmark set in " << title << "." << std::endl;
  }
}

double Book::computeReadingProgressPercentage() const {
  return (static_cast<double>(currentPageIndex + 1) / pages.size()) * 100;
}

void Book::displayCurrentPage() const {
  std::cout << "Page " << currentPageIndex + 1 << ": "
            << pages[currentPageIndex].getContent() << std::endl;
}

void Book::displayInfo() const {
  std::cout << "Book Info: " << title << " by " << author << ", " << year
            << ", Code: " << code << std::endl;
}

int Book::getCurrentPageIndex() const { return currentPageIndex; }
