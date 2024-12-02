#ifndef THREAD_SAFE_LIBRARY_H
#define THREAD_SAFE_LIBRARY_H

#include <mutex>
#include <string>
#include <unordered_map>

class ThreadSafeLibrary {
private:
    std::mutex mtx;
    std::unordered_map<std::string, bool> available_books; // map<ISBN -> availability>

public:
    class BookCheckout;
    ThreadSafeLibrary();
    bool checkoutBook(const std::string& isbn);
    void returnBook(const std::string& isbn);
};

class ThreadSafeLibrary::BookCheckout {
private:
    ThreadSafeLibrary& library;
    std::string isbn;
    bool checked_out;

public:
    BookCheckout(ThreadSafeLibrary& lib, const std::string& book_isbn);
    ~BookCheckout();
    bool isCheckedOut() const;
};

#endif