#include <vector>
#include "../Lexer/Token.h"

using std::vector;

class TokenManager{
  private:
    int tokenIndex = -1; // The index, for the token queue
    vector<Token> *tokens; // Token queue
  public:
    TokenManager(vector<Token> *_tokens){ tokens = _tokens; };
    Token *nextToken(); // Dequeue and return next token
    Token *peekToken(int steps); // Peek more than 1 token away
    Token *peekToken(); // See what the next token is without dequeuing it
	  Token *currentToken();
};
