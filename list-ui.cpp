/*  DB imitation*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

struct City {
    int id;
    std::string value;
};

City line_to_struct(std::ifstream &ifs);
std::vector<City> file_to_vector(const std::string filename, std::vector<City> &cities);
void display_vector(const std::vector<City> &cities, const std::set<int> &selected_cities);

int main() {
    std::vector<City> cities;
    std::set<int> selected_cities;
    std::string filename = "city.db";
    cities = file_to_vector(filename, cities);
    
    int sel = 1;
    while (sel) {
        display_vector(cities, selected_cities);
        std::cout << "Input ID Number of item to select/deselect (0 - to quit): ";
        std::cin >> sel;
        if ( selected_cities.find(sel) != selected_cities.end() )
            selected_cities.erase(sel);
        else
            selected_cities.insert(sel); // make check if SEL is in vector cities
    }

    return 0;
}

std::vector<City> file_to_vector(const std::string filename, std::vector<City> &cities) {
    std::ifstream ifs(filename, std::ifstream::in);
    while( !ifs.eof() ) {
        City city;
        city = line_to_struct(ifs);
        cities.push_back(city);
    }
    ifs.close();

    return cities;
}

City line_to_struct(std::ifstream &ifs) {
    City city;
    std::string id;
    std::getline(ifs, id, '|');
    city.id = stoi(id);
    std::getline(ifs, city.value);

    return city;
}

void display_vector(const std::vector<City> &cities, const std::set<int> &selected_cities) {
    for(int i = 0; i < cities.size(); i++) {
        if (selected_cities.count(cities.at(i).id) != 0)
            std::cout << '*';
        else
            std::cout << ' ';
        std::cout << cities.at(i).id << " |" << cities.at(i).value << '\n';
    }
}
