#include <string>
#include <map>

using std::string;
using std::map;

// Keeps a correspondence between symbolic labels and numeric addresses 
class symbolTable {

    map<string, int> table;

public:
    // creates a new empty symbol table
    symbolTable();
    // adds the pair (sym, addr) to the table)
    void addEntry(string sym, int addr);
    // does the table contain sym?
    bool contains(string sym);
    // return the address associated with the symbol
    int getAddress(string sym);
};