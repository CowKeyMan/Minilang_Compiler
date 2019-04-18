#include "Visitor.h"

using std::map;

void SAVisitor::newScope(){
  scope.push_back(map<string, TokenType>());
}
void SAVisitor::insert(string s, TokenType tt){
  scope[0][s] = tt;
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

}
void *SAVisitor::visit(ASTNodeIdentifier *n){}
void *SAVisitor::visit(ASTNodeMultiplicativeOp *n){}
void *SAVisitor::visit(ASTNodeAdditiveOp *n){}
void *SAVisitor::visit(ASTNodeRelationalOp *n){}
void *SAVisitor::visit(ASTNodeActualParams *n){}
void *SAVisitor::visit(ASTNodeFunctionCall *n){}
void *SAVisitor::visit(ASTNodeSubExpression *n){}
void *SAVisitor::visit(ASTNodeUnary *n){}
void *SAVisitor::visit(ASTNodeFactor *n){}
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