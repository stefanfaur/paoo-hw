#include <iostream>
#include <vector>

#include "Book.h"
#include "SpecialBook.h"

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

  // tried to cleanup prints with this but getting double free error
  // book1.~Book();
  // book2.~Book();

  std::cout << " part two: " << std::endl;
  std::cout << " ----------------- " << std::endl;

  std::vector<std::string> pages = {"Page 1 content", "Page 2 content",
                                    "Page 3 content"};

  SpecialBook specialBook("Effective C++", "Scott Meyers", 2005, "1234567890",
                          pages, "Additional Exercises");
  specialBook.displayInfo();
  specialBook.displayInfo();
  specialBook.displaySpecialFeature();

  // using copy constructor
  SpecialBook specialBook2 = specialBook;

  // using move constructor - DISABLED
  // compile error if uncommented, as expected
  // SpecialBook specialBook3 = std::move(specialBook2);

  // move constructor being used to move temp object into vector
  std::vector<Book> books;
  books.push_back(Book("Moved Book", " Moved Author", 2020, "12345", {}));


  SpecialBook specialBook3("Unmoved Book", "Some other Author", 2021, "1234567890",
                            {}, "Joke every 5 pages");

  // using copy assignment
  SpecialBook specialBook4("Another", "Some Author", 2021, "1234567890",
                           {}, "Some feature");
  specialBook4 = specialBook;

  // using move assignment
  specialBook4 = std::move(specialBook3);

  return 0;
}