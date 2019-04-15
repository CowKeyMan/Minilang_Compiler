#include <iostream>

#include "AST.h"

using std::cerr;

void printParseErrorAndExit(Token *token){
  cerr << "error, could not parse token " << token->lexeme << "at line " << token->lineNumber;
  exit(EXIT_FAILURE);
}

Token *ASTNode::match(TokenType tt){
  Token *token = tokenManager->nextToken();
  if(token->type != tt){
    cerr << "error, could not match " << Token::TokenString[tt] << "at line " << token->lineNumber;
	  exit(EXIT_FAILURE);
  }else{
    return token;
  }
}

// Type Node
bool ASTNodeType::parse(){
  switch(tokenManager->peekToken()->type){
    case TYPE_FLOAT:
    case TYPE_INT:
    case TYPE_BOOL:
      token = tokenManager->nextToken();
      return true;
    break;
    default:
      return false;
  }
}

// Literal Node
bool ASTNodeLiteral::parse(){
  switch(tokenManager->peekToken()->type){
    case FLOAT:
    case INT:
    case BOOL:
      token = tokenManager->nextToken();
      return true;
    break;
    default:
      return false;
  }
}

// Literal Node
bool ASTNodeIdentifier::parse(){
  token = match(ID);
  return true;
}

// MultiplictiveOp Node
bool ASTNodeMultiplicativeOp::parse(){
  switch(tokenManager->peekToken()->type){
    case TIMES:
    case DIVISION:
    case AND:
      token = tokenManager->nextToken();
      return true;
    break;
    default:
      return false;
  }
}

// AdditiveOp Node
bool ASTNodeAdditiveOp::parse(){
  switch(tokenManager->peekToken()->type){
    case PLUS:
    case MINUS:
    case OR:
      token = tokenManager->nextToken();
      return true;
    break;
    default:
      return false;
  }
}

// AdditiveOp Node
bool ASTNodeRelationalOp::parse(){
  switch(tokenManager->peekToken()->type){
    case ST:
    case GT:
    case EQQ:
    case NE:
    case SE:
    case GE:
      token = tokenManager->nextToken();
      return true;
    break;
    default:
      return false;
  }
}

// ActualParams Node
bool ASTNodeActualParams::parse(){
  ASTNode *expr = new ASTNodeExpression(tokenManager);
  if (expr->parse() == false) return false; // expression must be valid
  expressions.push_back(expr);
  while(tokenManager->peekToken()->type == COMMA){
    tokenManager->currentToken();
    ASTNode* expr = new ASTNodeExpression(tokenManager);
    if (expr->parse() == false) return false; // expression must be valid
    expressions.push_back(expr);
  }
  return true;
}

// FunctionCall Node
bool ASTNodeFunctionCall::parse(){
  ASTNode *id= new ASTNodeActualParams(tokenManager);
  if (id->parse() == false) return false;
  identifier = id;
  
  match(OPEN_BRACKET);

  // peeking to check if there is an actualparam or not
  if(tokenManager->peekToken()->type != CLOSED_BRACKET){
    ASTNode *actualP= new ASTNodeActualParams(tokenManager);
    if (actualP->parse() == false) return false;
    actualParams = actualP;
  }
  match(CLOSED_BRACKET);
  return true;
}
ASTNodeFunctionCall::~ASTNodeFunctionCall(){
  delete actualParams;
}

// SubExpression Node
bool ASTNodeSubExpression::parse(){
  match(OPEN_BRACKET);
  ASTNode *expr= new ASTNodeActualParams(tokenManager);
  if (expr->parse() == false) return false;
  expression = expr;
  match(CLOSED_BRACKET);
  return true;
}
ASTNodeSubExpression::~ASTNodeSubExpression(){
  delete expression;
}

// Unary Node
bool ASTNodeUnary::parse(){
  switch (tokenManager->peekToken()->type)
  {
    case MINUS:
      match(MINUS);
    break;
    case NOT:
      match(NOT);
    break;
    default:
      return false;
  }

  ASTNode *expr= new ASTNodeActualParams(tokenManager);
  if (expr->parse() == false) return false;
  expression = expr;

  return true;
}
ASTNodeUnary::~ASTNodeUnary(){
  delete expression;
}

// Factor Node
bool ASTNodeFactor::parse(){
  ASTNode *n;
  switch (tokenManager->peekToken()->type)
  {
    case FLOAT:
    case INT:
    case BOOL:
      n = new ASTNodeLiteral(tokenManager);  
    break;
    case ID:
      if(tokenManager->peekToken(2)->type == OPEN_BRACKET){
        n = new ASTNodeFunctionCall(tokenManager);
      }else{
        n = new ASTNodeIdentifier(tokenManager);
      }
    break;
    case OPEN_BRACKET:
      n = new ASTNodeSubExpression(tokenManager);
    break;
    case MINUS:
    case NOT:
      n = new ASTNodeUnary(tokenManager);
    break;
    default:
      return false;
  }
  if (n->parse() == false) return false;
  node = n;
  return true;
}
ASTNodeFactor::~ASTNodeFactor(){
  delete node;
}

// Term Node
bool ASTNodeTerm::parse(){
  ASTNode *n = new ASTNodeFactor(tokenManager);
  if (n->parse() == false) return false;
  factor = n;

  while(true){
    ASTNode *n2, *n3;
    switch (tokenManager->peekToken()->type){
      case TIMES:
      case DIVISION:
      case AND:
        n2 = new ASTNodeFactor(tokenManager);
        if (n2->parse() == false) return false;
        multiplicativeOP.push_back(n2);

        n3 = new ASTNodeFactor(tokenManager);
        if (n3->parse() == false) return false;
        factors.push_back(n3);
      break;
      default:
        return true;
    }
  }
}
ASTNodeTerm::~ASTNodeTerm(){
  delete factor;
  for(uint8_t i = 0; i < factors.size(); ++i){
    delete multiplicativeOP.at(i);
    delete factors.at(i);
  }
}

bool ASTNodeSimpleExpression::parse(){
  ASTNode *n = new ASTNodeTerm(tokenManager);
  if (n->parse() == false) return false;
  term = n;

  while(true){
    ASTNode *n2, *n3;
    switch (tokenManager->peekToken()->type){
      case PLUS:
      case MINUS:
      case OR:
        n2 = new ASTNodeAdditiveOp(tokenManager);
        if (n2->parse() == false) return false;
        additiveOP.push_back(n2);

        n3 = new ASTNodeTerm(tokenManager);
        if (n3->parse() == false) return false;
        terms.push_back(n3);
      break;
      default:
        return true;
    }
  }
}
ASTNodeSimpleExpression::~ASTNodeSimpleExpression(){
  delete term;
  for(uint8_t i = 0; i < terms.size(); ++i){
    delete additiveOP.at(i);
    delete terms.at(i);
  }
}

// Expression Node
bool ASTNodeExpression::parse(){
  ASTNode *n = new ASTNodeSimpleExpression(tokenManager);
  if (n->parse() == false) return false;
  simpleExpression = n;

  while(true){
    ASTNode *n2, *n3;
    switch (tokenManager->peekToken()->type){
      case ST:
      case GT:
      case EQQ:
      case NE:
      case SE:
      case GE:
        n2 = new ASTNodeRelationalOp(tokenManager);
        if (n2->parse() == false) return false;
        relationalOp.push_back(n2);

        n3 = new ASTNodeSimpleExpression(tokenManager);
        if (n3->parse() == false) return false;
        simpleExpressions.push_back(n3);
      break;
      default:
        return true;
    }
  }
}
ASTNodeExpression::~ASTNodeExpression(){
  delete simpleExpression;
  for(uint8_t i = 0; i < simpleExpressions.size(); ++i){
    delete relationalOp.at(i);
    delete simpleExpressions.at(i);
  }
}

// Assignment Node
bool ASTNodeAssignment::parse(){
  ASTNode *n = new ASTNodeIdentifier(tokenManager);
  if (n->parse() == false) return false;
  identifier = n;

  match(EQ);

  ASTNode *n2 = new ASTNodeExpression(tokenManager);
  if (n2->parse() == false) return false;
  expression = n2;

  return true;
}
ASTNodeAssignment::~ASTNodeAssignment(){
  delete identifier;
  delete expression;
}

// VariableDecl Node
bool ASTNodeVariableDecl::parse(){
  match(VAR);

  ASTNode *n = new ASTNodeIdentifier(tokenManager);
  if (n->parse() == false) return false;
  identifier = n;

  match(COLON);

  ASTNode *n2 = new ASTNodeType(tokenManager);
  if (n2->parse() == false) return false;
  type = n2;

  match(EQ);

  ASTNode *n3 = new ASTNodeExpression(tokenManager);
  if (n3->parse() == false) return false;
  expression = n3;

  return true;
}
ASTNodeVariableDecl::~ASTNodeVariableDecl(){
  delete identifier;
  delete type;
  delete expression;
}

// ReturnStatement Node
bool ASTNodeReturnStatement::parse(){
  match(RETURN);

  ASTNode *n = new ASTNodeExpression(tokenManager);
  if (n->parse() == false) return false;
  expression = n;

  return true;
}
ASTNodeReturnStatement::~ASTNodeReturnStatement(){
  delete expression;
}

// ReturnStatement Node
bool ASTNodeIfStatement::parse(){
  match(IF);
  match(OPEN_BRACKET);

  ASTNode *n = new ASTNodeExpression(tokenManager);
  if (n->parse() == false) return false;
  expression = n;
  
  match(CLOSED_BRACKET);

  ASTNode *n2 = new ASTNodeBlock(tokenManager);
  if (n2->parse() == false) return false;
  block = n2;

  if(tokenManager->peekToken()->type == ELSE){
    match(ELSE);

    ASTNode *n3 = new ASTNodeBlock(tokenManager);
    if (n3->parse() == false) return false;
    elseBlock = n3;
  }
}
ASTNodeIfStatement::~ASTNodeIfStatement(){
  delete expression;
  delete block;
  delete elseBlock;
}




// Statement Node
bool ASTNodeStatement::parse(){
  switch(tokenManager->peekToken()->type){
    case VAR:
      // statement = new ASTNodeVariableDecl(tokenManager);
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
    default:
      return false;
  }
  
  if(statement->parse()) return true;

  return false;
}
ASTNodeStatement::~ASTNodeStatement(void){
  delete statement;
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
ASTNodeProgram::~ASTNodeProgram(){
  for(uint8_t i = 0; i < statements.size(); ++i){
    delete statements.at(i);
  }
}