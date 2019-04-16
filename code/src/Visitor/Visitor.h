#ifndef VISITOR_H
#define VISITOR_H

#include <sstream>

#include "../Parser/AST.h"

using std::stringstream;

class ASTNode;
class ASTNodeType;
class ASTNodeLiteral;
class ASTNodeIdentifier;
class ASTNodeMultiplicativeOp;
class ASTNodeAdditiveOp;
class ASTNodeRelationalOp;
class ASTNodeActualParams;
class ASTNodeFunctionCall;
class ASTNodeSubExpression;
class ASTNodeUnary;
class ASTNodeFactor;
class ASTNodeTerm;
class ASTNodeSimpleExpression;
class ASTNodeExpression;
class ASTNodeAssignment;
class ASTNodeVariableDecl;
class ASTNodeReturnStatement;
class ASTNodeIfStatement;
class ASTNodeForStatement;
class ASTNodeFormalParam;
class ASTNodeFormalParams;
class ASTNodeFunctionDecl;
class ASTNodeStatement;
class ASTNodeBlock;
class ASTNodeProgram;

class Visitor{
  public:
    Visitor(){};
    virtual ~Visitor(){};
    virtual void visit(ASTNode *n) = 0;
    virtual void visit(ASTNodeType *n){};
    virtual void visit(ASTNodeLiteral*){};
    virtual void visit(ASTNodeIdentifier*){};
    virtual void visit(ASTNodeMultiplicativeOp*){};
    virtual void visit(ASTNodeAdditiveOp*){};
    virtual void visit(ASTNodeRelationalOp*){};
    virtual void visit(ASTNodeActualParams*){};
    virtual void visit(ASTNodeFunctionCall*){};
    virtual void visit(ASTNodeSubExpression*){};
    virtual void visit(ASTNodeUnary*){};
    virtual void visit(ASTNodeFactor*){};
    virtual void visit(ASTNodeTerm*){};
    virtual void visit(ASTNodeSimpleExpression*){};
    virtual void visit(ASTNodeExpression*){};
    virtual void visit(ASTNodeAssignment*){};
    virtual void visit(ASTNodeVariableDecl*){};
    virtual void visit(ASTNodeReturnStatement*){};
    virtual void visit(ASTNodeIfStatement*){};
    virtual void visit(ASTNodeForStatement*){};
    virtual void visit(ASTNodeFormalParam*){};
    virtual void visit(ASTNodeFormalParams*){};
    virtual void visit(ASTNodeFunctionDecl*){};
    virtual void visit(ASTNodeStatement*){};
    virtual void visit(ASTNodeBlock*){};
    virtual void visit(ASTNodeProgram*){};
};

class XMLVisitor : virtual public Visitor{
  public:
    XMLVisitor(){};
    virtual ~XMLVisitor(){};
    virtual void visit(ASTNode*){};
    virtual void visit(ASTNodeType *n);
    virtual void visit(ASTNodeLiteral *n);
    virtual void visit(ASTNodeIdentifier *n);
    virtual void visit(ASTNodeMultiplicativeOp *n);
    virtual void visit(ASTNodeAdditiveOp *n);
    virtual void visit(ASTNodeRelationalOp *n);
    virtual void visit(ASTNodeActualParams *n);
    virtual void visit(ASTNodeFunctionCall *n);
    virtual void visit(ASTNodeSubExpression *n);
    virtual void visit(ASTNodeUnary *n);
    virtual void visit(ASTNodeFactor *n);
    virtual void visit(ASTNodeTerm *n);
    virtual void visit(ASTNodeSimpleExpression *n);
    virtual void visit(ASTNodeExpression *n);
    virtual void visit(ASTNodeAssignment *n);
    virtual void visit(ASTNodeVariableDecl *n);
    virtual void visit(ASTNodeReturnStatement *n);
    virtual void visit(ASTNodeIfStatement *n);
    virtual void visit(ASTNodeForStatement *n);
    virtual void visit(ASTNodeFormalParam *n);
    virtual void visit(ASTNodeFormalParams *n);
    virtual void visit(ASTNodeFunctionDecl *n);
    virtual void visit(ASTNodeStatement *n);
    virtual void visit(ASTNodeBlock *n);
    virtual void visit(ASTNodeProgram *n);
    void trimXMLNewLines(); // remove empty lines from xml
    string getXML(){ return xml.str(); }
  private:
    stringstream xml;
    unsigned int numberOfTabs = 0;
    string tabsString();
};

#endif // VISITOR_H
