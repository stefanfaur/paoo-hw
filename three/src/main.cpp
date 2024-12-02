#include <iostream>
#include <thread>
#include <vector>

#include "Book.h"
#include "SpecialBook.h"
#include "ThreadSafeLibrary.h"

// ----------------------------------------------------------
// mutex stuff

void demonstrateMutex() {
    std::cout << "\nThread Safety Demonstration:\n";
    std::cout << "-------------------------\n";

    ThreadSafeLibrary library;
    const std::string pragmatic_prog = "9780201616224";
    const std::string clean_coder = "9780137081073";

    auto tryCheckout = [&](const std::string &isbn, const std::string &thread_name) {
        ThreadSafeLibrary::BookCheckout checkout(library, isbn);
        if (checkout.isCheckedOut()) {
            std::cout << thread_name << " checked out book " << isbn << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate reading
            std::cout << thread_name << " returning book " << isbn << std::endl;
        } else {
            std::cout << thread_name << " couldn't check out book " << isbn << std::endl;
        }
    };

    // Create multiple threads trying to access the same books
    std::thread reader1(tryCheckout, pragmatic_prog, "Reader 1");
    std::thread reader2(tryCheckout, pragmatic_prog, "Reader 2");
    std::thread reader3(tryCheckout, clean_coder, "Reader 3");
    std::thread reader4(tryCheckout, clean_coder, "Reader 4");

    reader1.join();
    reader2.join();
    reader3.join();
    reader4.join();
}

// ----------------------------------------------------------
// main

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

  SpecialBook specialBook3("Unmoved Book", "Some other Author", 2021,
                           "1234567890", {}, "Joke every 5 pages");

  // using copy assignment
  SpecialBook specialBook4("Another", "Some Author", 2021, "1234567890", {},
                           "Some feature");
  specialBook4 = specialBook;

  // using move assignment
  // from this point on specialBook3 is in undefined state
  SpecialBook someSpecialBook = std::move(SpecialBook("UnmovedConstructor Book", "Some other Author", 2021,
                           "1234567890", {}, "Joke every 5 pages"));

  std::cout << " polymorphism stuff: " << std::endl;
  std::cout << " ----------------- " << std::endl;

  pageContents = {
      "Page 1 content",
      "Page 2 words.",
      "Page 3 stuff.",
  };

  Book baseBook("Base Book", "Author A", 2000, "123456", pageContents);

  SpecialBook derivedBook("Special Book", "Author B", 2022, "654321",
                          pageContents, "Extra Insights");

  Book* bookPtr = &baseBook;
  bookPtr->displayInfo();  // Calls Book::displayInfo

  bookPtr = &derivedBook;
  bookPtr->displayInfo();  // calls SpecialBook::displayInfo (dynamic link)

  Book& bookRef = derivedBook;
  bookRef = SpecialBook("Special Book", "Author B", 2022, "654321",
                        pageContents, "Extra Insights");
  bookRef.displayInfo(); // calls SpecialBook::displayInfo (dynamic link)


  // Smart pointers stuff

  // although all are books, displayInfo will be linked dinamically like above
 std::vector<std::shared_ptr<Book>> library;

    library.push_back(std::make_shared<Book>("Base Book", "Author A", 2000,
                                             "123456", pageContents));
    library.push_back(std::make_shared<SpecialBook>("Special Book", "Author B",
                                                    2022, "654321", pageContents,
                                                    "Extra Insights"));

    std::cout << "\nLibrary Contents:\n";
    for (const auto& book : library) {
        book->displayInfo();  // polymorphic call to displayInfo()
    }

    // another library showing shared ownership
    std::vector<std::shared_ptr<Book>> anotherLibrary;

    // share books between two libraries
    for (const auto& book : library) {
        anotherLibrary.push_back(book);  // share ownership
    }

    std::cout << "\nAnother Library Contents (Shared):\n";
    for (const auto& book : anotherLibrary) {
        book->displayInfo();  // polymorphic call to displayInfo()
    }

    // mark all pages in the first book to show unique ownership
    library[0]->markAllPages();
    library[0]->displayCurrentPage();
    library[1]->displayCurrentPage();
    anotherLibrary[0]->displayCurrentPage();
    anotherLibrary[1]->displayCurrentPage();

    // Demonstrating shared ownership
    std::cout << "\nOwnership Demonstration:\n";
    std::cout << "Book 1 use count (library): " << library[0].use_count() << std::endl;
    std::cout << "Book 1 use count (anotherLibrary): " << anotherLibrary[0].use_count() << std::endl;

    // Mutex stuff
    // RAII; resource acquisition is initialization

    demonstrateMutex();

    std::cout << " end, destructors: " << std::endl;
    std::cout << " ----------------- " << std::endl;

    return 0;
}

