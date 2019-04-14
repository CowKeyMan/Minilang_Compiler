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

void printParseErrorAndExit(Token *token){
  cerr << "error, could not parse token " << token->lexeme << "at line " << token->lineNumber;
  exit(EXIT_FAILURE);
}

void ASTNode::match(TokenType tt){
  Token *current = tokenManager->nextToken();
  if(current->type != tt){
    cerr << "error, could not match " << Token::TokenString[tt] << "at line " << current->lineNumber;
	 exit(EXIT_FAILURE);
  }
}

// Program Node
vector<TokenType> ASTNodeProgram::_startTokens = vector<TokenType>(); // empty
bool ASTNodeProgram::parse(){
  while(true){ // parse multiple statements
    if (tokenManager->peekToken() == nullptr) break;
    
    ASTNode *statement = new ASTNodeStatement(tokenManager);
    // statement must be parsable if a token exists
    if (statement->parse() == false) printParseErrorAndExit(tokenManager->currentToken()); 
    
    statements.push_back(statement);
  }

  if (statements.size() > 0) return true; // needs to be at least one statement
  return false;
}
ASTNodeProgram::~ASTNodeProgram(void){
  for(int i = 0; i < statements.size(); ++i){
    delete statements.at(i);
  }
}

// Statement Node
vector<TokenType> ASTNodeStatement::_startTokens = {IF};
bool ASTNodeStatement::parse(){
  switch(tokenManager->peekToken()->type){
    case VAR:
      statement = new ASTNodeVariableDecl(tokenManager);
    break;

    case ID:
      // statement = new ASTNodeAssignment(tokenManager);
    break;

    case IF:
      // statement = new ASTNodeIfStatement(tokenManager);
    break;

    case FOR:
      // statement = new ASTNodeForStatement(tokenManager);
    break;

    case RETURN:
      // statement = new ASTNodeReturnStatement(tokenManager);
    break;

    case FN:
      // statement = new ASTNodeFunctionDecl(tokenManager);
    break;

    case OPEN_BRACE:
      // statement = new ASTNodeBlock(tokenManager);
    break;
  }
  
  if(statement->parse()) return true;

  return false;
}
ASTNodeStatement::~ASTNodeStatement(void){
  delete statement;
}

bool ASTNodeVariableDecl::parse(){
  return false;
}
