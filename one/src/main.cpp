#include "Book.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> pageContents = {
        "Some content on the first page about data.",
        "Now some words about programming itself.",
        "The third page is about the importance of algorithms.",
        "And on the fourth page, we will discuss the mind of a programmer.",
    };

    Book book1("The Pragmatic Programmer", "Andrew Hunt, David Thomas", 2019, "9780201616224", pageContents);

    book1.displayInfo();

    book1.openBook();
    book1.displayCurrentPage();
    book1.turnPage();
    book1.displayCurrentPage();
    book1.bookmarkPage();
    book1.turnPage();
    book1.displayCurrentPage();


    std::cout << "Reading progress: " << book1.computeReadingProgressPercentage() << "%" << std::endl;

    book1.goToBookmark();
    book1.displayCurrentPage();

    std::cout << "Reading progress: " << book1.computeReadingProgressPercentage() << "%" << std::endl;

    Book book2 = book1;
    book1.turnPage();
    book1.displayCurrentPage();
    book2.displayCurrentPage();

    return 0;
}