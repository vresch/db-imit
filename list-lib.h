/* Library file for list manipulations: 
    create list of entries from database file input,
    select/deselect entries of list,
    display on screen, etc*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <set>

const char Delimiter = '|';

struct Entry 
{
    int id;
    std::string value;
};

// operator< overload for std::set
bool operator< (const Entry &e1, const Entry &e2)
{
    return e1.id < e2.id;
}

std::vector<std::string> split_string(const std::string &str, char delimiter)
{
    std::stringstream input(str);
    std::vector<std::string> substrings;
    std::string substring;
    while ( std::getline(input, substring, delimiter) ) {
        substrings.push_back(substring);
    }
    return substrings;
}

Entry create_entry(const std::string &str) 
{
    auto substrings = split_string(str, Delimiter);
    int id = std::stoi(substrings[0]);
    std::string value = substrings[1];

    // C99 syntacs for struct initialisation
    return Entry{.id = id, .value = value};
}

std::vector<Entry> create_entries(const std::string &filename) 
{
    std::ifstream input(filename);
    std::vector<Entry> entries;
    std::string line;
    while ( std::getline(input, line) ) {
        entries.push_back( create_entry(line) );
    }
    return entries;
}

void display_entries(const std::vector<Entry> &entries, const std::set<Entry> &selected) 
{
    int i = 1;
    for (auto e : entries) {
       std::string sel = selected.count(e) ? "* " : "  " ;
        std::cout << sel << i << ". "  << e.id << "|" << e.value << '\n';
        i++;
    }
}

void export_selected(const std::set<Entry> &selected, const std::string &filename)
{
    std::ofstream output(filename);
    for ( auto s : selected) {
        output << s.id << "|" << s.value << '\n';
    }
}

std::set<Entry> import_selected(const std::string &filename)
{
    std::ifstream input(filename);
    std::set<Entry> selected;
    std::string line;
    while ( std::getline(input, line) ) {
        selected.insert( create_entry(line) );
    }
    return selected;
}

void run_ui(const std::vector<Entry> &entries, const std::string &selectedfilename) {
    const std::string Prompt = ">";

    std::set<Entry> selected_entries = import_selected(selectedfilename);
    while (true) {
        display_entries(entries, selected_entries);

        std::string user_input;
        std::cout << Prompt << " ";
        std::cin >> user_input;

        if (user_input == "exit" || user_input == "e" ||
            user_input == "quit" || user_input == "q" ||
            user_input == "0")
        {
            break;
        } else if ( stoi(user_input) > 0 && stoi(user_input) < entries.size() ) {
            int index = std::stoi(user_input) - 1;
            Entry entry = entries.at(index);
            if ( selected_entries.count(entry) )
            {
                selected_entries.erase(entry);
            } else {
                selected_entries.insert(entry);
            }
        }
    }
    export_selected(selected_entries, selectedfilename);
}
