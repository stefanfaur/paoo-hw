#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include "Page.h"

class Book {
private:
    std::string title;
    std::string author;
    int year;
    std::string code;
    int currentPageIndex;
    std::vector<std::unique_ptr<Page>> pages; // use unique_ptr as pages are not shared
    int bookmarkedPageIndex;

public:
    // constructor
    Book(const std::string& title, const std::string& author, int year, const std::string& code, const std::vector<std::string>& pageContents);

    // copy constructor and assignment operator
    Book(const Book& other);            // deep copy
    Book& operator=(const Book& other); // deep copy

    // move constructor and assignment operator
    Book(Book&& other) noexcept;            // move resources
    Book& operator=(Book&& other) noexcept; // move resources

    // destructor
    // makes sure derived class destructor is called even if assigned to base class reference
    virtual ~Book();

    void openBook();
    void turnPage();
    void bookmarkPage();
    void goToBookmark();
    void markAllPages();
    double computeReadingProgressPercentage() const;
    void displayCurrentPage() const;
    virtual void displayInfo() const; 
    int getCurrentPageIndex() const;
};

#endif
