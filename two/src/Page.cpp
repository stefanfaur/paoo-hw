#include "Page.h"

#include <iostream>

// constructor
Page::Page(const std::string& content) : content(content) {}

// destructor
// commenting the log out to reduce output pollution
Page::~Page() { 
    // std::cout << "Page object destroyed" << std::endl; 
    }

// getter
std::string Page::getContent() const { return content; }