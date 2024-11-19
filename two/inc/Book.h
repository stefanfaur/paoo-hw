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
    std::vector<Page> pages; // no need destruct manually, vector will do it when out of scope
    int bookmarkedPageIndex;

public:
    // constructor
    Book(const std::string& title, const std::string& author, int year, const std::string& code, const std::vector<std::string>& pageContents);

    // assignment operator override
    Book& operator=(const Book& other);

    // destructor
    // makes sure derived class destructor is called even if assigned to base class reference
    virtual ~Book();

    void openBook();
    void turnPage();
    void bookmarkPage();
    void goToBookmark();
    double computeReadingProgressPercentage() const;
    void displayCurrentPage() const;
    virtual void displayInfo() const; 
    int getCurrentPageIndex() const;
};

#endif
