#include "Visitor.h"

#include <iostream>

void XMLVisitor::visit(ASTNodeType *n){
  xml << "Type = \"";
  switch(n->token->type){
    case TYPE_FLOAT:
      xml << "float";
    break;
    case TYPE_INT:
      xml << "int";
    break;
    case TYPE_BOOL:
      xml << "bool";
    break;
    default:
    break;
  }
  xml << "\"";
}

void XMLVisitor::visit(ASTNodeLiteral *n){
  switch(n->token->type){
    case FLOAT:
      xml << "<FloatConst>" << n->token->number << "</FloatConst>\n";
    break;
    case INT:
      xml << "<IntConst>" << n->token->number << "</IntConst>\n";
    break;
    case BOOL:
      xml << "<BoolConst>" << n->token->lexeme << "</BoolConst>\n";
    break;
    default:
    break;
  }
}
void XMLVisitor::visit(ASTNodeIdentifier *n){
  xml << n->token->lexeme << "</ID>\n";
}
void XMLVisitor::visit(ASTNodeMultiplicativeOp *n){
  
}
void XMLVisitor::visit(ASTNodeAdditiveOp *n){}
void XMLVisitor::visit(ASTNodeRelationalOp *n){}
void XMLVisitor::visit(ASTNodeActualParams *n){}
void XMLVisitor::visit(ASTNodeFunctionCall *n){}
void XMLVisitor::visit(ASTNodeSubExpression *n){}
void XMLVisitor::visit(ASTNodeUnary *n){}
void XMLVisitor::visit(ASTNodeFactor *n){}
void XMLVisitor::visit(ASTNodeTerm *n){}
void XMLVisitor::visit(ASTNodeSimpleExpression *n){}
void XMLVisitor::visit(ASTNodeExpression *n){}
void XMLVisitor::visit(ASTNodeAssignment *n){}
void XMLVisitor::visit(ASTNodeVariableDecl *n){}
void XMLVisitor::visit(ASTNodeReturnStatement *n){}
void XMLVisitor::visit(ASTNodeIfStatement *n){}
void XMLVisitor::visit(ASTNodeForStatement *n){}
void XMLVisitor::visit(ASTNodeFormalParam *n){}
void XMLVisitor::visit(ASTNodeFormalParams *n){}
void XMLVisitor::visit(ASTNodeFunctionDecl *n){}
void XMLVisitor::visit(ASTNodeStatement *n){}
void XMLVisitor::visit(ASTNodeBlock *n){}
void XMLVisitor::visit(ASTNodeProgram *n){}