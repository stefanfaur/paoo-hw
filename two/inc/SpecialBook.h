#ifndef SPECIALBOOK_H
#define SPECIALBOOK_H

#include "Book.h"
#include <string>

class SpecialBook : public Book {
private:
    std::string specialFeature;

public:
    SpecialBook(const std::string& title, const std::string& author, int year, const std::string& code, 
                const std::vector<std::string>& pageContents, const std::string& feature);

    // copy constructor
    SpecialBook(const SpecialBook& other);

    SpecialBook(SpecialBook&& other) noexcept;

    // assignment operators
    SpecialBook& operator=(const SpecialBook& other);
    SpecialBook& operator=(SpecialBook&& other) noexcept;

    // destructor
    ~SpecialBook();

    // display feature
    void displaySpecialFeature() const;
};

#endif
