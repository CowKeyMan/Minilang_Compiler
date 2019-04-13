#include "ASTNode.h"

bool ASTNode::parseOptional(){
  if(tokenManager->peekToken() == nullptr) return false;

  TokenType tt = tokenManager->peekToken()->type;
  for(int i = 0; i < startTokens().size(); ++i){
    if(tt = startTokens()[i]){ // check if can be parsed
      parse(); 
      return true;
    }
  }
  return false;
}

void ASTNode::parseMultiple(){
  if(tokenManager->peekToken() == nullptr) return;

  bool cont;
  TokenType tt = tokenManager->peekToken()->type;
  do{
    cont = parseOptional();
  }while(cont); // do it until it's no longer possible
}

vector<TokenType> ASTNodeProgram::_startTokens = vector<TokenType>(); // empty