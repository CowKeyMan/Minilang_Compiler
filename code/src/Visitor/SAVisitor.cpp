#include <iostream>

#include "Visitor.h"
#include "../Helper/Helper.h"

using std::map;
using std::cerr;

void SAVisitor::newScope(){
  scope.push_back(map<string, TokenType>());
}
void SAVisitor::insert(string s, TokenType tt){
  // if lexeme already exists in current scope or is a function name
  if(scope[0].count(s) || functions.count(s)){
    cerr << "Symbol " << s << " at line " << lineNumber;
    cerr << " already exists\n";
    exit(EXIT_FAILURE);
  }
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
  TokenType* tt = nullptr;
  switch(n->token->type){
    case TYPE_FLOAT:
      *tt = FLOAT;
    break;
    case TYPE_INT:
      *tt = INT;
    break;
    case TYPE_BOOL:
      *tt = BOOL;
    break;
    default:
    break;
  }
  lineNumber = n->token->lineNumber;
  return (TokenType*)tt;
}
void *SAVisitor::visit(ASTNodeLiteral *n){
  lineNumber = n->token->lineNumber;
  return (TokenType*)&n->token->type;
}
void *SAVisitor::visit(ASTNodeIdentifier *n){
  lineNumber = n->token->lineNumber;
  return 0;
}
void *SAVisitor::visit(ASTNodeMultiplicativeOp *n){
  lineNumber = n->token->lineNumber;
  return (TokenType*)&n->token->type;
}
void *SAVisitor::visit(ASTNodeAdditiveOp *n){
  lineNumber = n->token->lineNumber;
  return (TokenType*)&n->token->type;
}
void *SAVisitor::visit(ASTNodeRelationalOp *n){
  lineNumber = n->token->lineNumber;
  return (TokenType*)&n->token->type;
}
void *SAVisitor::visit(ASTNodeActualParams *n){
  vector<TokenType*> *types = new vector<TokenType*>();
  for(unsigned int i = 0; i < n->expressions.size(); ++i){
    types->push_back((TokenType*)n->expressions[i]->accept(this));
  }
  return (vector<TokenType*>*)types;
}
void *SAVisitor::visit(ASTNodeFunctionCall *n){
  // if function not found in functions table
  string fname = *(string*)n->identifier->accept(this);
  if(! functions.count( fname )){
    cerr << fname << " at line number ";
    cerr << lineNumber << " is not a function." << "\n";
    exit(EXIT_FAILURE);
  }
  if(n->actualParams != NULL){
    vector<TokenType> *vtt = (vector<TokenType>*)n->actualParams->accept(this);

    if(! vectors_equal(*vtt, functions.find(fname)->second)){
      cerr << "Invalid parameters for function " << fname;
      cerr << " at line number " << fname << "\n";
      exit(EXIT_FAILURE);
    }
  }
  return (TokenType*)lookup(fname);
}
void *SAVisitor::visit(ASTNodeSubExpression *n){
  return (TokenType*)n->expression->accept(this);
}
void *SAVisitor::visit(ASTNodeUnary *n){
  TokenType *tt = (TokenType*)n->expression->accept(this);
  lineNumber = n->token->type;

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
  return (TokenType*)tt;
}
void *SAVisitor::visit(ASTNodeFactor *n){
  return (TokenType*)n->node->accept(this);
}
void *SAVisitor::visit(ASTNodeTerm *n){
  // first factor is taken as reference
  TokenType *refType = (TokenType*)n->factors[0]->accept(this);

  for(unsigned int i = 0; i < n->multiplicativeOP.size(); ++i){
    TokenType multT = *(TokenType*)n->multiplicativeOP[i]->accept(this);
    // new type
    TokenType *newT = (TokenType*)n->factors[i+1]->accept(this);
    switch(multT){
      case TIMES:
      case DIVISION:
        if(*refType == BOOL || *newT == BOOL){
          cerr << "Type mismatch for operator" << Token::TokenString[multT];
          cerr << " at line " << lineNumber << "\n";
          exit(EXIT_FAILURE);
        }

        if(*refType == FLOAT || *newT == FLOAT) {
          *refType = FLOAT;
        }
        // else leave reftype as int, if both are integers
      break;
      case AND:
        if(*refType != BOOL || *newT != BOOL){ // both must be BOOL
          cerr << "Type mismatch for operator" << Token::TokenString[multT];
          cerr << " at line " << lineNumber << "\n";
          exit(EXIT_FAILURE);
        }
        // else leve reftype as bool
      break;
      default:
      break;
    }
  }

  return (TokenType*) refType;
}
void *SAVisitor::visit(ASTNodeSimpleExpression *n){
  // first factor is taken as reference
  TokenType *refType = (TokenType*)n->terms[0]->accept(this);

  for(unsigned int i = 0; i < n->additiveOP.size(); ++i){
    TokenType addT = *(TokenType*)n->additiveOP[i]->accept(this);
    // new type
    TokenType *newT = (TokenType*)n->terms[i+1]->accept(this);
    switch(addT){
      case PLUS:
      case MINUS:
        if(*refType == BOOL || *newT == BOOL){
          cerr << "Type mismatch for operator" << Token::TokenString[addT];
          cerr << " at line " << lineNumber << "\n";
          exit(EXIT_FAILURE);
        }

        if(*refType == FLOAT || *newT == FLOAT) {
          *refType = FLOAT;
        }
        // else leave reftype as int, if both are integers
      break;
      case OR:
        if(*refType != BOOL || *newT != BOOL){ // both must be BOOL
          cerr << "Type mismatch for operator" << Token::TokenString[addT];
          cerr << " at line " << lineNumber << "\n";
          exit(EXIT_FAILURE);
        }
        // else leve reftype as bool
      break;
      default:
      break;
    }
  }

  return (TokenType*) refType;
}
void *SAVisitor::visit(ASTNodeExpression *n){
  // first factor is taken as reference
  TokenType *refType = (TokenType*)n->simpleExpressions[0]->accept(this);

  // if there is a relop, then expression must be boolean
  for(unsigned int i = 0; i < n->relationalOp.size(); ++i){
    n->relationalOp[i]->accept(this); // just to set new line number
    // new type
    TokenType *newT = (TokenType*)n->simpleExpressions[i+1]->accept(this);
    if(*refType != BOOL || *newT != BOOL){
      cerr << "Type mismatch at line " << lineNumber << "\n";
      exit(EXIT_FAILURE);
    }
  }

  return (TokenType*) refType;
}
void *SAVisitor::visit(ASTNodeAssignment *n){
  string name = *(string*)n->identifier->accept(this);

  if(functions.count(name)){ // if trying to assign a function
    cerr << name << " at line " << lineNumber;
    cerr << " already defined as  function";
    exit(EXIT_FAILURE);
  }

  if(*lookup(name) != *(TokenType*)n->expression->accept(this)){
    cerr << "Type mismatch at line " << lineNumber << "\n";
    exit(EXIT_FAILURE);
  }
  return 0;
}
void *SAVisitor::visit(ASTNodeVariableDecl *n){
  TokenType type = *(TokenType*)n->type->accept(this);
  string name = *(string*)n->identifier->accept(this);
  insert( name , type );

  if(type != *(TokenType*)n->expression->accept(this)){
    cerr << "Type mismatch at line " << lineNumber << "\n";
    exit(EXIT_FAILURE);
  }
  return 0;
}
void *SAVisitor::visit(ASTNodePrintStatement *n){
  n->expression->accept(this);
  return 0;
}
void *SAVisitor::visit(ASTNodeReturnStatement *n){
  TokenType tt = *(TokenType*)n->expression->accept(this);

  if(currentFunctionType != tt){
    cerr << "Bad return type at line " << lineNumber << "\n";
    exit(EXIT_FAILURE);
  }
  return 0;
}
void *SAVisitor::visit(ASTNodeIfStatement *n){
  TokenType tt = *(TokenType*)n->expression->accept(this);
  // expression must be true or false
  if(tt != BOOL){
    cerr << "Expression must be a condition at line " << lineNumber << "\n";
    exit(EXIT_FAILURE);
  }

  n->block->accept(this);

  if(n->elseBlock) n->block->accept(this);

  return 0;
}
void *SAVisitor::visit(ASTNodeForStatement *n){
  newScope();
  if(n->variableDecl) n->variableDecl->accept(this);

  TokenType tt = *(TokenType*)n->expression->accept(this);
  if(tt != BOOL){
    cerr << "Expression must be a condition at line " << lineNumber << "\n";
    exit(EXIT_FAILURE);
  }

  if(n->assignment) n->assignment->accept(this);

  n->block->accept(this);
  removeScope();

  return 0;
}
void *SAVisitor::visit(ASTNodeFormalParam *n){
  string name = *(string*)n->identifier->accept(this);
  TokenType *ttl = (TokenType*)n->type->accept(this);
  insert( name, *ttl );

  return (TokenType*)ttl; 
}
void *SAVisitor::visit(ASTNodeFormalParams *n){
  vector<TokenType> *tt = new vector<TokenType>();
  for(unsigned int i = 0; i < n->formalParams.size(); ++i){
    tt->push_back( *(TokenType*)n->formalParams[i]->accept(this) );
  }
  return (vector<TokenType>*)tt;
}
void *SAVisitor::visit(ASTNodeFunctionDecl *n){
  newScope();
  string name = *(string*)n->identifier->accept(this);
  TokenType tt = *(TokenType*)n->type->accept(this);
  insert(name, tt);

  vector<TokenType> vtt = *(vector<TokenType>*)n->formalParams->accept(this);
  functions[name] = vtt;

  n->block->accept(this);

  removeScope();

  return 0;
}
void *SAVisitor::visit(ASTNodeStatement *n){
  n->statement->accept(this);

  return 0;
}
void *SAVisitor::visit(ASTNodeBlock *n){
  newScope();
  for(unsigned int i = 0; i < n->statements.size(); ++i){
    n->statements[i]->accept(this);
  }
  removeScope();

  return 0;
}
void *SAVisitor::visit(ASTNodeProgram *n){
  newScope();
  for(unsigned int i = 0; i < n->statements.size(); ++i){
    n->statements[i]->accept(this);
  }
  removeScope();

  return 0;
}