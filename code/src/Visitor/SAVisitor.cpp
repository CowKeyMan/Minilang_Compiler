#include <iostream>

#include "Visitor.h"
#include "../Helper/Helper.h"

using std::map;
using std::cerr;

void SAVisitor::newScope(){
  scope.push_back(map<string, TokenType>());
}
void SAVisitor::insert(Token *t){
  // if lexeme already exists in current scope or is a function name
  if(scope[0].count(t->lexeme) || functions.count(t->lexeme)){
    cerr << "Symbol " << t->lexeme << " at line " << t->lineNumber;
    cerr << " already exists\n";
    exit(EXIT_FAILURE);
  }
  scope[0][t->lexeme] = t->type;
}
void SAVisitor::removeScope(){
  scope.erase(scope.begin());
}
TokenType* SAVisitor::lookup(string s){
  for(unsigned int i = 0; i < scope.size(); ++i){
    if(scope[i].count(s)){ // if key exists
      return &scope[i].find(s)->second;
    }
  }
  return nullptr;
}

void *SAVisitor::visit(ASTNodeType *n){
  switch(n->token->type){
    case TYPE_FLOAT:
      return (void*)FLOAT;
    case TYPE_INT:
      return (void*)INT;
    case TYPE_BOOL:
      return (void*)BOOL;
    default:
      return nullptr;
  }
}
void *SAVisitor::visit(ASTNodeLiteral *n){
  return &n->token->type;
}
void *SAVisitor::visit(ASTNodeIdentifier *n){
  TokenType *tt = lookup(n->token->lexeme);
  if(tt == nullptr) {
    cerr << "Could not find symbol " << n->token->lexeme;
    cerr << " at line number " << n->token->lineNumber << "\n";
    exit(EXIT_FAILURE);
  }
  return &n->token;
}
void *SAVisitor::visit(ASTNodeMultiplicativeOp *n){
  return &n->token;
}
void *SAVisitor::visit(ASTNodeAdditiveOp *n){
  return &n->token;
}
void *SAVisitor::visit(ASTNodeRelationalOp *n){
  return &n->token;
}
void *SAVisitor::visit(ASTNodeActualParams *n){
  vector<TokenType*> *types = new vector<TokenType*>();
  for(unsigned int i = 0; i < n->expressions.size(); ++i){
    types->push_back((TokenType*)n->expressions[i]->accept(this));
  }
  return types;
}
void *SAVisitor::visit(ASTNodeFunctionCall *n){
  // if function not found in functions table
  Token* identifier = ((Token*)visit(n->identifier));
  if(! functions.count( identifier->lexeme )){
    cerr << identifier->lexeme << " at line number ";
    cerr << identifier->lineNumber << " is not a function." << "\n";
    exit(EXIT_FAILURE);
  }
  if(n->actualParams != NULL){
    vector<TokenType> *vtt = (vector<TokenType>*)n->actualParams->accept(this);

    if(! vectors_equal(*vtt, functions.find(identifier->lexeme)->second)){
      cerr << "Invalid parameters for function " << identifier->lexeme;
      cerr << " at line number " << identifier->lineNumber << "\n";
      exit(EXIT_FAILURE);
    }
  }
  return &identifier->type;
}
void *SAVisitor::visit(ASTNodeSubExpression *n){
  return n->expression->accept(this);
}
void *SAVisitor::visit(ASTNodeUnary *n){
  TokenType *tt = (TokenType*)n->expression->accept(this);

  switch(*tt){
    case INT:
    case FLOAT:
      // unary operator must be 'MINUS' if float or int, not 'NOT'
      if(! (n->token->type == MINUS)) {
        cerr << "Invalid unary operator " << n->token->lexeme;
        cerr << " at line number " << n->token->lineNumber;
        cerr << ". Expression must be of numeric type\n";
        exit(EXIT_FAILURE);
      }
    break;
    case BOOL:
      // unary operator must be 'MINUS' if float or int, not 'NOT'
      if(! (n->token->type == NOT)){
        cerr << "Invalid unary operator " << n->token->lexeme;
        cerr << " at line number " << n->token->lineNumber;
        cerr << ". Expression must be of boolean type\n";
        exit(EXIT_FAILURE);
      }
    break;
    default:
    break;
  }
  return tt;
}
void *SAVisitor::visit(ASTNodeFactor *n){
  // return 
}
void *SAVisitor::visit(ASTNodeTerm *n){}
void *SAVisitor::visit(ASTNodeSimpleExpression *n){}
void *SAVisitor::visit(ASTNodeExpression *n){}
void *SAVisitor::visit(ASTNodeAssignment *n){}
void *SAVisitor::visit(ASTNodeVariableDecl *n){}
void *SAVisitor::visit(ASTNodePrintStatement *n){}
void *SAVisitor::visit(ASTNodeReturnStatement *n){}
void *SAVisitor::visit(ASTNodeIfStatement *n){}
void *SAVisitor::visit(ASTNodeForStatement *n){}
void *SAVisitor::visit(ASTNodeFormalParam *n){}
void *SAVisitor::visit(ASTNodeFormalParams *n){}
void *SAVisitor::visit(ASTNodeFunctionDecl *n){}
void *SAVisitor::visit(ASTNodeStatement *n){}
void *SAVisitor::visit(ASTNodeBlock *n){}
void *SAVisitor::visit(ASTNodeProgram *n){}