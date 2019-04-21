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
          cout << "false";
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
  cout << "\n";
}

void *IVisitor::visit(ASTNodeType *n){
  lineNumber = n->token->lineNumber;
  return 0;
}
void *IVisitor::visit(ASTNodeLiteral *n){
  lineNumber = n->token->lineNumber;
  ValueType *vt = new ValueType(0, n->token->type);
  switch(n->token->type){
    case BOOL:
    case INT:
      vt->value = new int((int)(*(float*)&n->token->number));
    break;
    case FLOAT:
      vt->value = (float*)&n->token->number;
    break;
    default:
    break;
  }
  return (ValueType*)vt;
}
void *IVisitor::visit(ASTNodeIdentifier *n){
  lineNumber = n->token->lineNumber;
  return (string*)(&n->token->lexeme);
}
void *IVisitor::visit(ASTNodeMultiplicativeOp *n){
  lineNumber = n->token->lineNumber;
  return (TokenType*)&n->token->type;
}
void *IVisitor::visit(ASTNodeAdditiveOp *n){
  lineNumber = n->token->lineNumber;
  return (TokenType*)&n->token->type;
}
void *IVisitor::visit(ASTNodeRelationalOp *n){
  lineNumber = n->token->lineNumber;
  return (TokenType*)&n->token->type;
}
void *IVisitor::visit(ASTNodeActualParams *n){
  vector<ValueType*> *values = new vector<ValueType*>();
  for(unsigned int i = 0; i < n->expressions.size(); ++i){
    values->push_back((ValueType*)n->expressions[i]->accept(this));
  }
  return (vector<ValueType*>*)values;
}
void *IVisitor::visit(ASTNodeFunctionCall *n){}
void *IVisitor::visit(ASTNodeSubExpression *n){
  return n->expression->accept(this);
}
void *IVisitor::visit(ASTNodeUnary *n){}
void *IVisitor::visit(ASTNodeFactor *n){
  if(ASTNodeIdentifier* n2 = dynamic_cast<ASTNodeIdentifier*>(n->node)){
    string name = *(string*)n2->accept(this);
    return (ValueType*)lookup(name);
  }
  return (ValueType*)n->node->accept(this);
}
void *IVisitor::visit(ASTNodeTerm *n){
  // first factor is taken as reference
  ValueType *refValue = (ValueType*)n->factors[0]->accept(this);

  for(unsigned int i = 0; i < n->multiplicativeOP.size(); ++i){
    TokenType multT = *(TokenType*)n->multiplicativeOP[i]->accept(this);

    // new type
    ValueType *newValue = (ValueType*)n->factors[i+1]->accept(this);
    switch(multT){
      void *toReturn;
      case TIMES:
        if(refValue->type == INT && newValue->type == INT){
          toReturn = new int(*(int*)refValue->value * *(int*)newValue->value);
          refValue = (ValueType*)(new ValueType(toReturn, INT));
        }else{
          toReturn = new float(*(float*)refValue->value * *(float*)newValue->value);
          refValue = (ValueType*)(new ValueType(toReturn, FLOAT));
        }
      break;
      case DIVISION:
        if(refValue->type == INT && newValue->type == INT){
          toReturn = new int(*(int*)refValue->value / *(int*)newValue->value);
          refValue = (ValueType*)(new ValueType(toReturn, INT));
        }else{
          toReturn = new float(*(float*)refValue->value / *(float*)newValue->value);
          refValue = (ValueType*)(new ValueType(toReturn, FLOAT));
        }
      break;
      case AND:
        toReturn = new bool(*(bool*)refValue->value && *(bool*)newValue->value);
        refValue = (ValueType*)(new ValueType(toReturn, BOOL));
      break;
      default:
      break;
    }
  }
  return refValue;
}
void *IVisitor::visit(ASTNodeSimpleExpression *n){
  // first factor is taken as reference
  ValueType *refValue = (ValueType*)n->terms[0]->accept(this);

  for(unsigned int i = 0; i < n->additiveOP.size(); ++i){
    TokenType multT = *(TokenType*)n->additiveOP[i]->accept(this);

    // new type
    ValueType *newValue = (ValueType*)n->terms[i+1]->accept(this);
    switch(multT){
      void *toReturn;
      case PLUS:
        if(refValue->type == INT && newValue->type == INT){
          toReturn = new int(*(int*)refValue->value + *(int*)newValue->value);
          refValue = (ValueType*)(new ValueType(toReturn, INT));
        }else{
          toReturn = new float(*(float*)refValue->value + *(float*)newValue->value);
          refValue = (ValueType*)(new ValueType(toReturn, FLOAT));
        }
      break;
      case MINUS:
        if(refValue->type == INT && newValue->type == INT){
          toReturn = new int(*(int*)refValue->value - *(int*)newValue->value);
          refValue = (ValueType*)(new ValueType(toReturn, INT));
        }else{
          toReturn = new float(*(float*)refValue->value - *(float*)newValue->value);
          refValue = (ValueType*)(new ValueType(toReturn, FLOAT));
        }
      break;
      case OR:
        toReturn = new bool(*(bool*)refValue->value || *(bool*)newValue->value);
        refValue = (ValueType*)(new ValueType(toReturn, BOOL));
      break;
      default:
      break;
    }
  }
  return refValue;
}
void *IVisitor::visit(ASTNodeExpression *n){
  // first factor is taken as reference
  ValueType *refValue = (ValueType*)n->simpleExpressions[0]->accept(this);

  // if there is a relop, then expression must be boolean
  for(unsigned int i = 0; i < n->relationalOp.size(); ++i){
    TokenType tt = *(TokenType*)n->relationalOp[i]->accept(this); // just to set new line number
    // new type
    ValueType *newValue = (ValueType*)n->simpleExpressions[i+1]->accept(this);

    bool *b;

    switch (tt)
    {
      case ST:
        b = new bool( *(float*)refValue->value < *(float*)newValue->value );
      break;
      case GT:
        b = new bool( *(float*)refValue->value > *(float*)newValue->value );
      break;
      case EQQ:
        b = new bool( *(float*)refValue->value == *(float*)newValue->value );
      break;
      case NE:
        b = new bool( *(float*)refValue->value != *(float*)newValue->value );
      break;
      case SE:
        b = new bool( *(float*)refValue->value <= *(float*)newValue->value );
      break;
      case GE:
        b = new bool( *(float*)refValue->value >= *(float*)newValue->value );
      break;
      default:
      break;
    }

    refValue = new ValueType(b ,BOOL);
  }

  return (ValueType*) refValue;
}
void *IVisitor::visit(ASTNodeAssignment *n){}
void *IVisitor::visit(ASTNodeVariableDecl *n){}
void *IVisitor::visit(ASTNodePrintStatement* n){
  printValue((ValueType*)n->expression->accept(this));
}
void *IVisitor::visit(ASTNodeReturnStatement *n){}
void *IVisitor::visit(ASTNodeIfStatement *n){}
void *IVisitor::visit(ASTNodeForStatement *n){}
void *IVisitor::visit(ASTNodeFormalParam *n){}
void *IVisitor::visit(ASTNodeFormalParams *n){}
void *IVisitor::visit(ASTNodeFunctionDecl *n){}
void *IVisitor::visit(ASTNodeStatement *n){}
void *IVisitor::visit(ASTNodeBlock *n){}
void *IVisitor::visit(ASTNodeProgram *n){}