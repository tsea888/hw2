#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) :
    Product(category, name, price, qty),
    isbn_(isbn),
    author_(author)
{
}

Book::~Book()
{
}

std::set<std::string> Book::keywords() const{
  set<string> words = parseStringToWords(name_);
  set<string> author = parseStringToWords(author_);
  set<string> result = setUnion(words, author);
  result.insert(convToLower(isbn_));
  return result;
}

std::string Book::displayString() const{
  std::stringstream out;
  out << fixed << setprecision(2);
  out << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left."; 
  return out.str();
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_  << "\n" << author_ << endl;
}