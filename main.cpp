/* DB imitation*/
// make functions for display(), file_read(), select(), etc..
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

struct city {
 int id;
 std::string value;
};

int main() {
 std::vector<city> citydb;
 std::ifstream ifs; // possible to open file in construcor
 ifs.open("city.db", std::ifstream::in);
 /* read file by lines and push them in vector */
 while( !ifs.eof() ) {
  city inc;
  std::string id;
  std::getline(ifs, id, '|');
  inc.id = stoi(id);
  //std::cout << inc.id << " |"; // check file read by line to struct object
  std::getline(ifs, inc.value);
  //std::cout << inc.value << '\n'; // check file read by line to struct object
  
  citydb.push_back(inc);
  std::cout << citydb.back().id << " |" << citydb.back().value << '\n'; // check vector pushing
 }
 ifs.close(); // finished file read to vector and close file stream

 /* selection, make function */
 std::set<int> citysel;
 int sel = 1;
 while (sel) {
  std::cout << "Input ID Number of item to select/deselect (0 - to quit): ";
  std::cin >> sel;
  if ( citysel.find(sel) != citysel.end() )
   citysel.erase(sel);
  else
   citysel.insert(sel); // make check if SEL is in vector CITYDB
 
  /* print vector with selection/deselection, make function display() */
  for(int i = 0; i < citydb.size(); i++) {
   if ( citysel.count(citydb.at(i).id) != 0)
    std::cout << '*';
   else
    std::cout << ' ';
   std::cout << citydb.at(i).id << " |" << citydb.at(i).value << '\n';
  }
 }

 return 0;
}
