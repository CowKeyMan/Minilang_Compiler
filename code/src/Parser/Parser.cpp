#include "Parser.h"

using std::unique_ptr;
using std::shared_ptr;

Parser::Parser(vector<Token> *tokens){
  tokenManager = shared_ptr<TokenManager>( new TokenManager(tokens) );
  tree = unique_ptr<ASTNode>( new ASTNodeProgram(tokenManager));
};

void Parser::parse(){
  tree->parse();
}