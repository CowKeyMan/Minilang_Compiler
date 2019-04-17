#include "Visitor.h"

#include <iostream>

string XMLVisitor::tabsString(){
  if(xml.str().back() == ' ') return "";
  string ret;
  for(unsigned int i = 0; i < numberOfTabs; ++i){
    ret.append("  "); // tab is 2 whitespaces
  }
  return ret;
}

void XMLVisitor::trimXMLNewLines(){
  string s = xml.str();

  unsigned int newLineCount = 0, numberToDelete = 1;
  for(int i = 0; i < s.length(); ++i){
    if(s.at(i) == '\n'){
      newLineCount++;
      if(newLineCount == 2){
        s.erase(i-numberToDelete, numberToDelete);
        i--;
        newLineCount = 1;
      }
    }else if(s.at(i) != ' '){
      newLineCount = 0;
      numberToDelete = 1;
    }else if(s.at(i) == ' '){
      numberToDelete++;
    }
  }

  xml.str("");
  xml << s;
}

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
void XMLVisitor::visit(ASTNodeActualParams *n){
  for(int i = 0; i < n->expressions.size(); ++i){
    xml << "\n" << tabsString() << "<A_Param>\n";
    numberOfTabs++;
    n->expressions.at(i)->accept(this);
    numberOfTabs--;
    xml << "\n" << tabsString() << "</A_Param>\n";
  }
}
void XMLVisitor::visit(ASTNodeFunctionCall *n){
  xml << "<FN_CALL FN=\"";
  n->identifier->accept(this);
  xml << "\"\n";
  numberOfTabs++;
  n->actualParams->accept(this);
  numberOfTabs--;
  xml << "\n</FN_CALL FN>";
}
void XMLVisitor::visit(ASTNodeSubExpression *n){
  n->expression->accept(this);
}
void XMLVisitor::visit(ASTNodeUnary *n){
  xml << "\n" << tabsString() << "UnaryExpr OP=\"";
  xml << ((n->token->type == MINUS)? "-" : "not");
  xml << "\"";
  
  xml << ">\n";
  numberOfTabs++;
  xml << tabsString();
  n->expression->accept(this);
  xml << "\n";
  numberOfTabs--;
  xml << tabsString() << "</UnaryExpr>\n";
}
void XMLVisitor::visit(ASTNodeFactor *n){
  n->node->accept(this);
}
void XMLVisitor::visit(ASTNodeTerm *n){
  unsigned int factorsIndex = 0;
  for(unsigned int multOpIndex = 0; multOpIndex < n->multiplicativeOP.size(); ++multOpIndex){
    xml << "\n" << tabsString() << "<BinExpr ";
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
    xml << tabsString() << "</BinExpr>\n";
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
    xml << "\n";
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
  unsigned int factorsIndex = 0;
  for(unsigned int multOpIndex = 0; multOpIndex < n->relationalOp.size(); ++multOpIndex){
    xml << tabsString() << "<BinExprNode ";
    n->relationalOp.at(multOpIndex)->accept(this);
    xml << ">\n";
    numberOfTabs++;
    xml << tabsString();
    n->simpleExpressions.at(factorsIndex++)->accept(this);
    xml << "\n";
  }
  xml << tabsString();
  n->simpleExpressions.at(factorsIndex++)->accept(this);
  xml << "\n";
  for(unsigned int multOpIndex = 0; multOpIndex < n->relationalOp.size(); ++multOpIndex){
    numberOfTabs--;
    xml << tabsString() << "</BinExprNode>\n";
  }
}
void XMLVisitor::visit(ASTNodeAssignment *n){
  xml << "\n" << tabsString() << "<Assign>\n";
  numberOfTabs++;
  xml << tabsString();
  n->identifier->accept(this);
  xml << "\n";
  xml << tabsString();
  n->expression->accept(this);
  numberOfTabs--;
  xml << "\n" << tabsString() << "</Assign>\n";
}
void XMLVisitor::visit(ASTNodeVariableDecl *n){
  xml << "\n" << tabsString() << "<Decl>\n";
  numberOfTabs++;
  xml << tabsString() << "<Var ";
  n->type->accept(this);
  xml << ">";
  n->identifier->accept(this);
  xml << "\n";
  n->expression->accept(this);
  numberOfTabs--;
  xml << "\n" << tabsString() << "</Decl>\n";
}
void XMLVisitor::visit(ASTNodeReturnStatement *n){
  xml << "\n" << tabsString() << "<Return>\n";
  numberOfTabs++;
  n->expression->accept(this);
  numberOfTabs--;
  xml << "\n" << tabsString() << "</Return>\n";
}
void XMLVisitor::visit(ASTNodeIfStatement *n){
  xml << "\n" << tabsString() << "<IF>\n";
  numberOfTabs++;
  n->expression->accept(this);
  numberOfTabs--;
  xml << "\n" << tabsString() << "<THEN>\n";
  numberOfTabs++;
  n->block->accept(this);
  numberOfTabs--;
  if(n->elseBlock){
    xml << "\n" << tabsString() << "<ELSE>\n";
    numberOfTabs++;
    n->elseBlock->accept(this);
    numberOfTabs--;
  }
  xml << "\n" << tabsString() << "<ENDIF>\n";
}
void XMLVisitor::visit(ASTNodeForStatement *n){
  xml << "\n" << tabsString() << "<FOR>\n";
  numberOfTabs++;
  if(n->variableDecl) n->variableDecl->accept(this);
  n->expression->accept(this);
  if(n->assignment) n->assignment->accept(this);
  numberOfTabs--;
  xml << "\n" << tabsString() << "<DO>\n";
  numberOfTabs++;
  n->block->accept(this);
  numberOfTabs--;
  xml << "\n" << tabsString() << "<ENDFOR>\n";
}
void XMLVisitor::visit(ASTNodeFormalParam *n){
  xml << "\n" << tabsString() << "<F_Param>\n";
  numberOfTabs++;
  n->identifier->accept(this);
  xml << ":";
  n->type->accept(this);
  numberOfTabs--;
  xml << tabsString() << "\n</F_Param>\n";
}
void XMLVisitor::visit(ASTNodeFormalParams *n){
  for(int i = 0; i < n->formalParams.size(); ++i){
    n->formalParams.at(i)->accept(this);
  }
}
void XMLVisitor::visit(ASTNodeFunctionDecl *n){}
void XMLVisitor::visit(ASTNodeStatement *n){
  n->statement->accept(this);
}
void XMLVisitor::visit(ASTNodeBlock *n){
  for(int i = 0; i < n->statements.size(); ++i){
    n->statements.at(i)->accept(this);
  }
}
void XMLVisitor::visit(ASTNodeProgram *n){
  for(int i = 0; i < n->statements.size(); ++i){
    n->statements.at(i)->accept(this);
  }
}