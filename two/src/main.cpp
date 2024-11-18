#include <iostream>
#include <vector>

#include "Book.h"

int main() {
  std::vector<std::string> pageContents = {
      "Some content on the first page about data.",
      "Now some words about programming itself.",
      "The third page is about the importance of algorithms.",
      "And on the fourth page, we will discuss the mind of a programmer.",
  };

  Book book1("The Pragmatic Programmer", "Andrew Hunt, David Thomas", 2019,
             "9780201616224", pageContents);

  book1.displayInfo();

  book1.openBook();
  book1.displayCurrentPage();
  book1.turnPage();
  book1.displayCurrentPage();
  book1.bookmarkPage();
  book1.turnPage();
  book1.displayCurrentPage();

  std::cout << "Reading progress: " << book1.computeReadingProgressPercentage()
            << "%" << std::endl;

  book1.goToBookmark();
  book1.displayCurrentPage();

  std::cout << "Reading progress: " << book1.computeReadingProgressPercentage()
            << "%" << std::endl;

  Book book2("The Clean Coder", "Robert C. Martin", 2011, "9780137081073", {});
  book2 = book1;  // assignment op wasn't getting called before as we were not
                  // assigning, but using generated copy constructor

  book1.displayCurrentPage();
  book2.displayCurrentPage();

  book1.turnPage();
  book1.displayCurrentPage();
  book2.displayCurrentPage();

  std::cout << " part two: " << std::endl;
  std::cout << " ----------------- " << std::endl;

  std::vector<std::string> pages = {
        "Page 1 content",
        "Page 2 content",
        "Page 3 content"
    };

SpecialBook book("Effective C++", "Scott Meyers", 2005, "1234567890", pages, "Additional Exercises");
book.displayInfo();

  return 0;
}