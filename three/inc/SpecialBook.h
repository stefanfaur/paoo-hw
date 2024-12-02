#ifndef SPECIALBOOK_H
#define SPECIALBOOK_H

#include "Book.h"
#include <string>

class SpecialBook : public Book {
private:
    std::shared_ptr<std::string> specialFeature; // shared_ptr as feature can be shared between books

public:
    SpecialBook(const std::string& title, const std::string& author, int year, const std::string& code, 
                const std::vector<std::string>& pageContents, const std::string& feature);

    // copy constructor
    SpecialBook(const SpecialBook& other);

    // move constructor - disabled
    SpecialBook(SpecialBook&& other) noexcept;

    // assignment operators
    SpecialBook& operator=(const SpecialBook& other);
    // SpecialBook& operator=(SpecialBook&& other) noexcept = 0;

    // destructor
    ~SpecialBook();

    // override displayInfo
    void displayInfo() const override;

    // display feature
    void displaySpecialFeature() const;
};

#endif
