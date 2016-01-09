/*  DB imitation*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>

const char Delimiter = '|';

struct Entry {
    int id;
    std::string value;
};

bool operator < (const Entry &e1, const Entry &e2) { return e1.id < e2.id; }
std::vector<std::string> split_string(const std::string &str, char delimiter);
Entry line_to_entry(const std::string &str);
std::vector<Entry> create_entries(std::ifstream &input);
void display_entries(const std::vector<Entry> &entries, const std::set<Entry> &selected);
void run_ui(const std::vector<Entry> &entries);

const std::string FilenameData = "city.db";

int main() 
{
    std::ifstream input(FilenameData);
    std::vector<Entry> cities = create_entries(input);
    run_ui(cities);

    return 0;
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

std::vector<Entry> create_entries(std::ifstream &input) 
{
    std::vector<Entry> entries;
    std::string line;
    while ( std::getline(input, line) ) {
        entries.push_back( line_to_entry(line) );
    }
    return entries;
}

Entry line_to_entry(const std::string &str) 
{
    auto substrings = split_string(str, Delimiter);
    int id = std::stoi(substrings[0]);
    std::string value = substrings[1];

    // C99 syntacs for struct initialisation
    return Entry{.id = id, .value = value};
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

void run_ui(const std::vector<Entry> &entries) {
    const std::string Prompt = ">";
    std::set<Entry> selected_entries;
    while (true) {
        display_entries(entries, selected_entries);

        std::string user_input;
        std::cout << Prompt << " ";
        std::cin >> user_input;

        if (user_input == "exit" ||
            user_input == "quit")
        {
            break;
        } else {
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
}
