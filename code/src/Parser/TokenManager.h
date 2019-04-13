#include <vector>
#include "../Lexer/Token.h"

using std::vector;

class TokenManager{
  private:
    int tokenIndex = 0; // The index, for the token queue
    vector<Token> *tokens; // Token queue
  public:
    TokenManager(vector<Token> *tokens){ TokenManager::tokens = tokens; };
    Token *nextToken(); // Dequeue and return next token
    Token *peekToken(); // See what the next token is without dequeuing it
};