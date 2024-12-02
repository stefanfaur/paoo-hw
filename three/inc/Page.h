#ifndef PAGE_H
#define PAGE_H

#include <string>

class Page {
 private:
  std::string content;

 public:
  // constructor
  Page(const std::string& content);

  // destructor
  ~Page();

  // gtter
  std::string getContent() const;

  // setter
  void setContent(const std::string& newContent);
};
#endif