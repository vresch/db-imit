/* Command line version of list program */

#include "list-lib.h"

const std::string DataFilename = "data-city.db";
const std::string SelectedFilename = "data-city-sel";

int main(int argc, char *argv[])
{
    std::vector<Entry> entries = create_entries(DataFilename);
    std::set<Entry> selected_entries = import_selected(SelectedFilename);
    if (argc > 1)
    {
        if ( !std::strcmp(argv[1], "--select") ||
             !std::strcmp(argv[1], "-s") )
        {
            if ( argv[2] && std::atoi(argv[2]) > 0 && std::atoi(argv[2]) <= entries.size() ) 
            {
                int index = std::atoi(argv[2]) - 1;
                Entry entry = entries.at(index);
                if ( selected_entries.count(entry) )
                {
                    selected_entries.erase(entry);
                } else {
                    selected_entries.insert(entry);
                }
                export_selected(selected_entries, SelectedFilename);
            } else {
                std::cout << argv[2] << " is out of range" << '\n';
                return 0;
            }
        } else {
            std::cout << argv[1] << " - unknown command, try: --select [N]" << '\n';
            return 0;
        }
    }
    display_entries(entries, selected_entries);

    return 0;
}
