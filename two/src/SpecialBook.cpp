#include "SpecialBook.h"
#include <iostream>

// constructor
SpecialBook::SpecialBook(const std::string& title, const std::string& author, int year, const std::string& code, 
                         const std::vector<std::string>& pageContents, const std::string& feature)
    : Book(title, author, year, code, pageContents), specialFeature(feature) {
    std::cout << "SpecialBook created with feature: " << specialFeature << std::endl;
}

// copy constructor
SpecialBook::SpecialBook(const SpecialBook& other) 
    : Book(other), specialFeature(other.specialFeature) {
    std::cout << "SpecialBook copy constructor called" << std::endl;
}

// move constructor - i will disable this
// SpecialBook::SpecialBook(SpecialBook&& other) noexcept
//     : Book(std::move(other)), specialFeature(std::move(other.specialFeature)) {
//     std::cout << "SpecialBook move constructor called" << std::endl;
// }

// copy assignment operator
SpecialBook& SpecialBook::operator=(const SpecialBook& other) {
    if (this != &other) {
        Book::operator=(other); // Assign base class part
        specialFeature = other.specialFeature;
        std::cout << "SpecialBook copy assignment operator called" << std::endl;
    }
    return *this;
}

// move assignment operator
SpecialBook& SpecialBook::operator=(SpecialBook&& other) noexcept {
    if (this != &other) {
        Book::operator=(std::move(other)); // assign base class part
        specialFeature = std::move(other.specialFeature);
        std::cout << "SpecialBook move assignment operator called" << std::endl;
    }
    return *this;
}

// destructor
SpecialBook::~SpecialBook() {
    std::cout << "Destroying SpecialBook with feature: " << specialFeature << std::endl;
}

// display special feature
void SpecialBook::displaySpecialFeature() const {
    std::cout << "Special feature of this book: " << specialFeature << std::endl;
}
