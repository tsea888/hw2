#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

Movie::~Movie()
{
}

std::set<std::string> Movie::keywords() const{
  set<string> words = parseStringToWords(name_);
  set<string> result = words;
  result.insert(convToLower(genre_));
  return result;
}

std::string Movie::displayString() const{
  std::stringstream out;
  out << fixed << setprecision(2);
  out << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left."; 
  return out.str();
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}