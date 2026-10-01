#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <set>
#include <vector>
#include <map>

class MyDataStore : public DataStore{
  public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void executeCommand(std::string cmd, std::string username, Product* product);

  private:
    std::set<Product*> products_;
    std::vector<User*> users_;
    //maps a single keyword to products that contain the keyword
    std::map<std::string, std::set<Product*>> keywords_;
    //maps username to cart items
    std::map<std::string, std::vector<Product*>> carts_;
};

#endif