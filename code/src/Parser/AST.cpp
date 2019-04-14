#include <iostream>

#include "AST.h"

using std::cerr;

// ASTNode *ASTNode::parseOptional(){
//   if(tokenManager->peekToken() == nullptr) return NULL;

//   // is the start tokens are empty (any token goes), no need to check
//   if(startTokens().size() == 0){
//     parse();
//     return NULL;
//   }

//   TokenType tt = tokenManager->peekToken()->type;
//   for(int i = 0; i < startTokens().size(); ++i){
//     if(tt = startTokens()[i]){ // check if can be parsed
//       parse(); 
//       return true;
//     }
//   }
//   return NULL;
// }

// vector<ASTNode*> ASTNode::parseMultiple(){
//   if(tokenManager->peekToken() == nullptr) return;

//   bool cont;
//   TokenType tt = tokenManager->peekToken()->type;
//   do{
//     cont = parseOptional();
//   }while(cont); // do it until it's no longer possible
// }

void ASTNode::match(TokenType tt){
  Token *current = tokenManager->nextToken();
  if(current->type != tt){
    cerr << "error, could now match " << Token::TokenString[tt] << "at line " << current->lineNumber;
  }
}

// Program Node
vector<TokenType> ASTNodeProgram::_startTokens = vector<TokenType>(); // empty
bool ASTNodeProgram::parse(){
  while(true){ // parse multiple statements
    if (tokenManager->peekToken() == nullptr) break;
    
    ASTNode *statement = new ASTNodeStatement(tokenManager);
    if (statement->parse() == false) return false; // statement must be parsable if a token exists
    statements.push_back(statement);
  }

  if (statements.size() > 0) return true; // needs to be at least one statement
  return false;
}

// Statement Node
vector<TokenType> ASTNodeStatement::_startTokens = {IF};
bool ASTNodeStatement::parse(){
  return false;
}