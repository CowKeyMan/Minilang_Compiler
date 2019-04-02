#include <vector>
#include "Token.h"

using std::vector;

class Lexer{
  private:
    int fileIndex; // current index in the file
    int lineNumber = 0; // for debugging purposes
    string file; // pointer to the file
    enum State{
      STA, S00, S01, S02, S03, S04, S05, S06, S07, S08, S09, S10, S11, S12, S13, S14, S15, S16, S17, ERR
    }; // S is the start state
    State transitionTable[19][12] = {
      /*      0         1    2    3      4      5    6    7    8    9          10   11
              +(){};:,  !    .    digit  alpha  /    \n   *    =    space/tab  <>   other*/
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
    char nextChar(); // next character from file
    int getColumn(char c); // see to which column the character belongs to
    // see to which token the lexeme belongs to and add it to the list of vectors/report error
    void process_lexeme(string lexeme, State state);
    vector<Token> tokens; // the list of tokens
  public:
    Lexer(string filestring); // needs to be given the string to lex
    void lex(); // main method to get tokens from file
    vector<Token> get_tokens(); // return the list of tokens (read only)
};