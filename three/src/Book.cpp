#include "Book.h"

#include <iostream>
#include <memory>

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
  for (const auto& content : pageContents) {
    pages.emplace_back(std::make_unique<Page>(content)); // create unique_ptr for each page
  }
  std::cout << "Book created: " << title << " with " << pages.size()
            << " pages." << std::endl;
}

// copy constructor
Book::Book(const Book& other)
    : title(other.title),
      author(other.author),
      year(other.year),
      code(other.code),
      currentPageIndex(other.currentPageIndex),
      bookmarkedPageIndex(other.bookmarkedPageIndex) {
    for (const auto& page : other.pages) {
        pages.emplace_back(std::make_unique<Page>(page->getContent())); // Deep copy
    }
    std::cout << "Book copied: " << title << std::endl;
}


// copy assignment operator override
Book& Book::operator=(const Book& other) {
  if (this != &other) {  // Self-assignment check
    title = other.title;
    author = other.author;
    year = other.year;
    code = other.code;
    currentPageIndex = other.currentPageIndex;
    bookmarkedPageIndex = other.bookmarkedPageIndex;
    // deep copy of pages
    pages.clear();
    for (const auto& page : other.pages) {
      pages.emplace_back(std::make_unique<Page>(page->getContent()));
    }
  }
  std::cout << "Book assigned: " << title << std::endl;
  return *this;
}

// move constructor
Book::Book(Book&& other) noexcept
    : title(std::move(other.title)),
      author(std::move(other.author)),
      year(other.year),
      code(std::move(other.code)),
      currentPageIndex(other.currentPageIndex),
      bookmarkedPageIndex(other.bookmarkedPageIndex),
      pages(std::move(other.pages)) { // Move pages
    std::cout << "Book moved: " << title << std::endl;
}

Book& Book::operator=(Book&& other) noexcept {
    if (this != &other) {
        title = std::move(other.title);
        author = std::move(other.author);
        year = other.year;
        code = std::move(other.code);
        currentPageIndex = other.currentPageIndex;
        bookmarkedPageIndex = other.bookmarkedPageIndex;
        pages = std::move(other.pages); // Move pages
    }
    std::cout << "Book move-assigned: " << title << std::endl;
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
            << pages[currentPageIndex]->getContent() << std::endl;
}

void Book::displayInfo() const {
  std::cout << "Book Info: " << title << " by " << author << ", " << year
            << ", Code: " << code << std::endl;
}

int Book::getCurrentPageIndex() const { return currentPageIndex; }

void Book::markAllPages() {
  for (auto& page : pages) {  // Iterate over unique_ptr<Page>
    page->setContent("MARKED TOUCHED");  // Dereference unique_ptr to access Page
  }
  std::cout << "All pages in the book '" << title
            << "' have been marked as 'MARKED TOUCHED'." << std::endl;
}