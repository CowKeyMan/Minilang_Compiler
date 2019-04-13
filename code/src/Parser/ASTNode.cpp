#include "ASTNode.h"

void ASTNode::parseOptional(){
  TokenType tt = tokenManager->peekToken().type;
  for(int i = 0; i < startTokens().size(); ++i){
    if(tt = startTokens()[i]){ // check if can be parsed
      parse(); 
      break;
    }
  }
}

void ASTNode::parseMultiple(){
  bool cont = false;
  TokenType tt = tokenManager->peekToken().type;
  do{
    for(int i = 0; i < startTokens().size(); ++i){
      if(tt = startTokens()[i]){ // check if can be parsed
        parse();
        cont = true;
        break;
      }
    }
  }while(cont); // do it until it's no longer possible
}

vector<TokenType> ASTNodeProgram::_startTokens = vector<TokenType>(); // empty