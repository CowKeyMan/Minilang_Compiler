#include <iostream>

#include "Visitor.h"

using std::map;
using std::cerr;
using std::cout;

void IVisitor::newScope(){
  scope.insert(scope.begin() ,map<string, ValueType>());
}
void IVisitor::insert(string s, ValueType vt){
  // if lexeme already exists in current scope or is a function name
  if(scope[0].count(s) || functions.count(s)){
    cerr << "Symbol " << s << " at line " << lineNumber;
    cerr << " already exists\n";
    exit(EXIT_FAILURE);
  }
  scope[0][s] = vt;
}
void IVisitor::removeScope(){
  scope.erase(scope.begin());
}
ValueType *IVisitor::lookup(string s){
  for(unsigned int i = 0; i < scope.size(); ++i){
    if(scope[i].count(s)){ // if key exists
      return &scope[i].find(s)->second;
    }
  }
  return nullptr;
}
void IVisitor::printSymbolTable(){
  cout << "Symbol Table:\n";
  for(unsigned int i = 0; i < scope.size(); ++i){
    cout << "scope " << i << std::endl;
    map<string, ValueType>::iterator it;
    for ( it = scope[i].begin(); it != scope[i].end(); it++ ){
      cout << it->first << " : " << *(float*)it->second.value << ", " << Token::TokenString[it->second.type];
    }
    cout << "\n\n";
  }
  cout << "Functions Table:\n";
  map<string, ASTNode*>::iterator it;
  for ( it = functions.begin(); it != functions.end(); it++ ){
    cout << it->first << "\n";
  }
  cout << "\n";
}
void IVisitor::printValue(ValueType* vt){
  if(vt != NULL){
    switch(vt->type){
      case BOOL:
        if(*(bool*)vt->value == true){
          cout << "true";
        }else{
          cout << "true";
        }
      break;
      case FLOAT:
        cout << *(float*)vt->value;
      break;
      case INT:
        cout << *(int*)vt->value;
      break;
      default:
      break;
    }
  }else{
    cout << "NULL";
  }
}

void *IVisitor::visit(ASTNodeType *n){
  lineNumber = n->token->lineNumber;
  return 0;
}
void *IVisitor::visit(ASTNodeLiteral *n){
  lineNumber = n->token->lineNumber;
  return (ValueType*)(new ValueType(&n->token->number, n->token->type));
}
void *IVisitor::visit(ASTNodeIdentifier *n){}
void *IVisitor::visit(ASTNodeMultiplicativeOp *n){}
void *IVisitor::visit(ASTNodeAdditiveOp *n){}
void *IVisitor::visit(ASTNodeRelationalOp *n){}
void *IVisitor::visit(ASTNodeActualParams *n){}
void *IVisitor::visit(ASTNodeFunctionCall *n){}
void *IVisitor::visit(ASTNodeSubExpression *n){}
void *IVisitor::visit(ASTNodeUnary *n){}
void *IVisitor::visit(ASTNodeFactor *n){}
void *IVisitor::visit(ASTNodeTerm *n){}
void *IVisitor::visit(ASTNodeSimpleExpression *n){}
void *IVisitor::visit(ASTNodeExpression *n){}
void *IVisitor::visit(ASTNodeAssignment *n){}
void *IVisitor::visit(ASTNodeVariableDecl *n){}
void *IVisitor::visit(ASTNodePrintStatement*){}
void *IVisitor::visit(ASTNodeReturnStatement *n){}
void *IVisitor::visit(ASTNodeIfStatement *n){}
void *IVisitor::visit(ASTNodeForStatement *n){}
void *IVisitor::visit(ASTNodeFormalParam *n){}
void *IVisitor::visit(ASTNodeFormalParams *n){}
void *IVisitor::visit(ASTNodeFunctionDecl *n){}
void *IVisitor::visit(ASTNodeStatement *n){}
void *IVisitor::visit(ASTNodeBlock *n){}
void *IVisitor::visit(ASTNodeProgram *n){}