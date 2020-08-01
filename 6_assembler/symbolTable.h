
#include <string>
using std::string;

// Keeps a correspondence between symbolic labels and numeric addresses 
class symbolTable {

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