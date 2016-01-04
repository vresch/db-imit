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
 std::ifstream ifs; // possible to open file in construcor
 ifs.open("city.db", std::ifstream::in);

 /* read file by lines and push them in vector */
 std::vector<city> citydb;
 while( !ifs.eof() ) {
  city inc, outc;
  std::string id;
  std::getline(ifs, id, '|');
  inc.id = stoi(id);
  //std::cout << inc.id << " |"; // check file read by line to struct object
  std::getline(ifs, inc.value);
  //std::cout << inc.value << '\n'; // check file read by line to struct object
  
  citydb.push_back(inc);
  outc = citydb.back();
  std::cout << outc.id << " |" << outc.value << '\n'; // check vector pushing
 }
 ifs.close(); // finished file read to vector and close file stream

 /* selection, make function */
 
 int sel;
 std::cout << "Input ID Number of item to select/deselect (0 - to quit): ";
 std::cin >> sel;
 std::set<int> citysel;

 
 if (sel == 0) return 0;
 if ( citysel.find(sel) != citysel.end() ) {
  citysel.erase(sel);
 }
 else {
  citysel.insert(sel);
  //std::cout << citysel(sel); // error 'nor call operation'
 }
 
 /* print vector with selection, make deselection, make function */
 for(int i = 0; i < citydb.size(); i++) {
  city outc;
  outc = citydb.at(i);
  if ( citysel.count(outc.id) != 0)
   std::cout << '*';
  std::cout << outc.id << '\n';
 }

 return 0;
}
