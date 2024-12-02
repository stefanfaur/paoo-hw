#include "ThreadSafeLibrary.h"

ThreadSafeLibrary::ThreadSafeLibrary() {
    available_books["9780201616224"] = true;
    available_books["9780137081073"] = true;
}

bool ThreadSafeLibrary::checkoutBook(const std::string& isbn) {
    std::lock_guard<std::mutex> lock(mtx);
    if (available_books.find(isbn) != available_books.end() && available_books[isbn]) {
        available_books[isbn] = false;
        return true;
    }
    return false;
}

void ThreadSafeLibrary::returnBook(const std::string& isbn) {
    std::lock_guard<std::mutex> lock(mtx);
    if (available_books.find(isbn) != available_books.end()) {
        available_books[isbn] = true;
    }
}

ThreadSafeLibrary::BookCheckout::BookCheckout(ThreadSafeLibrary& lib, const std::string& book_isbn)
    : library(lib), isbn(book_isbn), checked_out(false) {
    checked_out = library.checkoutBook(isbn);
}

ThreadSafeLibrary::BookCheckout::~BookCheckout() {
    if (checked_out) {
        library.returnBook(isbn);
    }
}

bool ThreadSafeLibrary::BookCheckout::isCheckedOut() const {
    return checked_out;
}