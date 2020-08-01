// translates Hack assembly language mnemonics into binary codes.

#include <string>
using std::string;

int* dest(string mnem);
int* comp(string mnem);
int* jump(string mnem);