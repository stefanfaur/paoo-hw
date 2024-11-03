#ifndef PAGE_H
#define PAGE_H

#include <string>

class Page
{
private:
    std::string content;

public:
    // constructor
    Page(const std::string &content);

    // destructor
    ~Page();

    // getter
    std::string getContent() const;
};


#endif