#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>

#include "../Lexer/Token.h"
#include "AST.h"

using std::vector;
using std::unique_ptr;
using std::shared_ptr;

class Parser{
  private:
    TokenManager* tokenManager;
    ASTNode* tree;
  public:
    Parser(vector<Token> *tokens);
    void parse();
};

#endif // PARSER_H