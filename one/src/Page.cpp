#include "Page.h"
#include <iostream>

// constructor
Page::Page(const std::string &content) {
    this->content = content;
}

// getter
std::string Page::getContent() const { return content; }

// destructor
Page::~Page() {
    std::cout << "Page object destroyed" << std::endl;
}
