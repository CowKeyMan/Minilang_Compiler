#include "Token.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

char nextChar(string file, int index);

class Lexer{
  private:
    int fileIndex; // current index in the file
    string file; // pointer to the file
    enum state{
      STA, S00, S01, S02, S03, S04, S05, S06, S07, S08, S09, S10, S11, S12, S13, S14, S15, S16, S17, ERR
    }; // S is the start state
    state transitionTable[19][12] = {
      /*      +(){};:,  !    .    digit  alpha  /    \n   *    =    space/tab  <>   other*/
      /*STA*/ {S00,     S01, S04, S03,   S06,   S07, S17, S00, S13, S17,       S15, ERR},
      /*S00*/ {ERR,     ERR, ERR, ERR,   ERR,   ERR, ERR, ERR, ERR, ERR,       ERR, ERR},
      /*S01*/ {ERR,     ERR, ERR, ERR,   ERR,   ERR, ERR, ERR, S02, ERR,       ERR, ERR},
      /*S02*/ {ERR,     ERR, ERR, ERR,   ERR,   ERR, ERR, ERR, ERR, ERR,       ERR, ERR},
      /*S03*/ {ERR,     ERR, S04, S03,   ERR,   ERR, ERR, ERR, ERR, ERR,       ERR, ERR},
      /*S04*/ {ERR,     ERR, ERR, S05,   ERR,   ERR, ERR, ERR, ERR, ERR,       ERR, ERR},
      /*S05*/ {ERR,     ERR, ERR, S05,   ERR,   ERR, ERR, ERR, ERR, ERR,       ERR, ERR},
      /*S06*/ {ERR,     ERR, ERR, S06,   S06,   ERR, ERR, ERR, ERR, ERR,       ERR, ERR},
      /*S07*/ {ERR,     ERR, ERR, ERR,   ERR,   S11, ERR, S08, ERR, ERR,       ERR, ERR},
      /*S08*/ {S08,     S08, S08, S08,   S08,   S08, S08, S09, S08, S08,       S08, S08},
      /*S09*/ {S08,     S08, S08, S08,   S08,   S10, S08, S08, S08, S08,       S08, S08},
      /*S10*/ {ERR,     ERR, ERR, ERR,   ERR,   ERR, ERR, ERR, ERR, ERR,       ERR, ERR},
      /*S11*/ {S11,     S11, S11, S11,   S11,   S11, S12, S11, S11, S11,       S11, S11},
      /*S12*/ {ERR,     ERR, ERR, ERR,   ERR,   ERR, ERR, ERR, ERR, ERR,       ERR, ERR},
      /*S13*/ {ERR,     ERR, ERR, ERR,   ERR,   ERR, S14, ERR, ERR, ERR,       ERR, ERR},
      /*S14*/ {ERR,     ERR, ERR, ERR,   ERR,   ERR, ERR, ERR, ERR, ERR,       ERR, ERR},
      /*S15*/ {ERR,     ERR, ERR, ERR,   ERR,   ERR, ERR, ERR, S16, ERR,       ERR, ERR},
      /*S16*/ {ERR,     ERR, ERR, ERR,   ERR,   ERR, ERR, ERR, ERR, ERR,       ERR, ERR},
      /*S17*/ {ERR,     ERR, ERR, ERR,   ERR,   ERR, S17, ERR, ERR, S17,       ERR, ERR} 
    };
    char nextChar();
    vector<Token> tokens;
  public:
    Lexer(string filestring);
    vector<string> lex();
    vector<Token> get_tokens();
};