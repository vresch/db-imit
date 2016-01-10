/* User Interface (UI) file for list manipulations */

#include "list-lib.h"

const std::string DataFilename = "data-city.db";
const std::string SelectedFilename = "data-city-sel";

int main() 
{
    std::vector<Entry> entries = create_entries(DataFilename);
    run_ui(entries, SelectedFilename);

    return 0;
}
