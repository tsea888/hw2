#include "mydatastore.h"
#include "util.h"
#include <set>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

MyDataStore::MyDataStore(){}

MyDataStore::~MyDataStore(){

}

void MyDataStore::addProduct(Product* p){
  products_.push_back(p);
  set<string> wordsInProduct = p->keywords();
  set<string>::iterator it = wordsInProduct.begin();
  for(it = wordsInProduct.begin(); it != wordsInProduct.end(); ++it){
    keywords_[*it].insert(*p);
  }
}

void MyDataStore::addUser(User* u){
  users_.push_back(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  vector<Product*> results;
  if(terms.empty()){
    return results;
  }
  vector<string>::iterator it = terms.begin();
  set<Product*> searchResults = terms[*it];

  for(it = terms.begin()+1; it != terms.end(); ++it){
    //go through each term and check if it's in the keyword map
    set<Product*> currentKeywordProducts = keywords_[i];
    //recall that in amazon.cpp, type 0 is and, 1 is or
    if(type == 0){
      searchResults = setIntersection(searchResults, currentKeywordProducts);
    }
    else{
      searchResults = setUnion(searchResults, currentKeywordProducts);
    }
  }

  vector<Product*>::iterator nit = searchResults.begin();
  for(nit = searchResults.begin(); nit != searchResults.end(); ++nit){
    results.push_back(*nit);
  }

  return results;
}

void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << endl;
  set<Product*>::iterator it = products_.begin();
  for(it = products_.begin(); it != products_.end(); ++it){
    *it->dump(ofile);
  } 

  ofile << "</products>" << endl;
  ofile<< "<users>" << endl;
  vector<User*>::iterator nit = users_.begin();
  for(nit = users_.begin(); nit != users_.end(); ++nit){
    *nit->dump(ofile);
  }
  ofile << "</users>" << endl;
}

void MyDataStore::executeCommand(string cmd, string username, Product* product){
  User* user = NULL;
  username = convToLower(username);
  for(int i = 0; i < users_.size(); i++){
    if(convToLower(users_[i]->getName()) == username){
      user = users_[i];
    }
  }
  vector<Product*> userCart = carts_[convToLower(username)];
  if(user == NULL){
    cout << "Invalid username" << endl;
  }
  else if(cmd == "ADD"){
    if(product == NULL){
      cout << "Invalid request" << endl;
    }
    else{
      userCart.push_back(product);
    }
  }
  else if(cmd == "VIEWCART"){
    vector<Product*>::iterator it = userCart.begin();
    for(it = userCart.begin(); it != userCart.end(); ++it){
      cout << i << endl;
      cout << userCart[i]->displayString() << endl;
    }
  }
  else{
    vector<Product*> notBought;
    vector<Product*>::iterator it = userCart.begin();
    for(it = userCart.begin(); it != userCart.end(); ++it){
      if(*it->getQty() != 0 && user->getBalance >= (*it->getPrice())){
        *it->subtractQty(1);
        user->deductAmount(*it->getPrice());
      }
      else{
        notBought.push_back(*it);
      }
    }
    userCart = notBought;
  }
}

