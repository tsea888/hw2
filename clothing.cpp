#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const string size, const string brand) :
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{
}

Clothing::~Clothing()
{
}

std::set<std::string> Clothing::keywords() const{
  set<string> words = parseStringToWords(name_);
  set<string> brand = parseStringToWords(brand_);
  set<string> result = setUnion(words, brand);
  return result;
}

std::string Clothing::displayString() const{
  std::stringstream out;
  out << fixed << setprecision(2);
  out << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left." << endl; 
  return out.str();
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
