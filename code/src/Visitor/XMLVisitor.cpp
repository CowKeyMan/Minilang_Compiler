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
      xml << "<FloatConst>" << n->token->number << "</FloatConst>";
    break;
    case INT:
      xml << "<IntConst>" << n->token->number << "</IntConst>";
    break;
    case BOOL:
      xml << "<BoolConst>" << n->token->lexeme << "</BoolConst>";
    break;
    default:
    break;
  }
}
void XMLVisitor::visit(ASTNodeIdentifier *n){
  xml << n->token->lexeme << "</ID>";
}
void XMLVisitor::visit(ASTNodeMultiplicativeOp *n){
  xml << "OP=\"" << n->token->lexeme << "\"";
}
void XMLVisitor::visit(ASTNodeAdditiveOp *n){
  xml << "OP=\"" << n->token->lexeme << "\"";
}
void XMLVisitor::visit(ASTNodeRelationalOp *n){
  xml << "OP=\"" << n->token->lexeme << "\"";
}
void XMLVisitor::visit(ASTNodeActualParams *n){}
void XMLVisitor::visit(ASTNodeFunctionCall *n){}
void XMLVisitor::visit(ASTNodeSubExpression *n){}
void XMLVisitor::visit(ASTNodeUnary *n){}
void XMLVisitor::visit(ASTNodeFactor *n){
  n->node->accept(this);
}
void XMLVisitor::visit(ASTNodeTerm *n){
  unsigned int factorsIndex = 0;
  for(unsigned int multOpIndex = 0; multOpIndex < n->multiplicativeOP.size(); ++multOpIndex){
    xml << tabsString() << "BinExprNode ";
    n->multiplicativeOP.at(multOpIndex)->accept(this);
    xml << ">\n";
    numberOfTabs++;
    xml << tabsString();
    n->factors.at(factorsIndex++)->accept(this);
    xml << "\n";
  }
  xml << tabsString();
  n->factors.at(factorsIndex++)->accept(this);
  xml << "\n";
  for(unsigned int multOpIndex = 0; multOpIndex < n->multiplicativeOP.size(); ++multOpIndex){
    numberOfTabs--;
    xml << tabsString() << "</BinExprNode>\n";
  }
}
void XMLVisitor::visit(ASTNodeSimpleExpression *n){
  unsigned int termsIndex = 0;
  for(unsigned int multOpIndex = 0; multOpIndex < n->additiveOP.size(); ++multOpIndex){
    xml << tabsString() << "BinExprNode ";
    n->additiveOP.at(multOpIndex)->accept(this);
    xml << ">\n";
    numberOfTabs++;
    xml << tabsString();
    n->terms.at(termsIndex++)->accept(this);
    // xml << "\n";
  }
  xml << tabsString();
  n->terms.at(termsIndex++)->accept(this);
  xml << "\n";
  for(unsigned int multOpIndex = 0; multOpIndex < n->additiveOP.size(); ++multOpIndex){
    numberOfTabs--;
    xml << tabsString() << "</BinExprNode>\n";
  }
}
void XMLVisitor::visit(ASTNodeExpression *n){
  
}
void XMLVisitor::visit(ASTNodeAssignment *n){}
void XMLVisitor::visit(ASTNodeVariableDecl *n){}
void XMLVisitor::visit(ASTNodeReturnStatement *n){}
void XMLVisitor::visit(ASTNodeIfStatement *n){}
void XMLVisitor::visit(ASTNodeForStatement *n){}
void XMLVisitor::visit(ASTNodeFormalParam *n){
  xml << "<Param>";

  n->identifier->accept(this);
  xml << ":";
  n->type->accept(this);

  xml << "</Param>";
}
void XMLVisitor::visit(ASTNodeFormalParams *n){
  for(int i = 0; i < n->formalParams.size(); ++i){
    n->formalParams.at(i)->accept(this);
  }
}
void XMLVisitor::visit(ASTNodeFunctionDecl *n){}
void XMLVisitor::visit(ASTNodeStatement *n){}
void XMLVisitor::visit(ASTNodeBlock *n){}
void XMLVisitor::visit(ASTNodeProgram *n){}