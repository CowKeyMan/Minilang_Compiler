#include "Parser.h"

Parser::Parser(vector<Token> *tokens){
  tokenManager = new TokenManager(tokens);
  tree = new ASTNodeProgram(tokenManager);
};

void Parser::parse(){
  tree->parse();
}