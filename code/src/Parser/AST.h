#ifndef  AST_H
#define AST_H

#include <memory>
#include "TokenManager.h"

using std::shared_ptr;

class ASTNode{
  public:
    ASTNode(TokenManager *_tokenManager){ tokenManager = _tokenManager; };
    virtual ~ASTNode(){};
    virtual bool parse() = 0; // returns true if parse was successful
  protected:
    TokenManager *tokenManager;
    Token *match(TokenType tokenType); // match a TokenType, make sure it exists
};

class ASTNodeType : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeType(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeType(){};
    virtual bool parse(); // returns true if parse was successful
  private:
    Token* token; 
};

class ASTNodeLiteral : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeLiteral(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeLiteral(){};
    virtual bool parse(); // returns true if parse was successful
  private:
    Token* token;
};

class ASTNodeIdentifier : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeIdentifier(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeIdentifier(){};
    virtual bool parse(); // returns true if parse was successful
  private:
    Token* token;
};

class ASTNodeMultiplicativeOp : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeMultiplicativeOp(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeMultiplicativeOp(){};
    virtual bool parse(); // returns true if parse was successful
  private:
    Token* token;
};

class ASTNodeAdditiveOp : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeAdditiveOp (TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeAdditiveOp (){};
    virtual bool parse(); // returns true if parse was successful
  private:
    Token* token; // statement node
};

class ASTNodeRelationalOp : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeRelationalOp (TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeRelationalOp(){};
    virtual bool parse(); // returns true if parse was successful
  private:
    Token* token;
};

class ASTNodeActualParams : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeActualParams (TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeActualParams(){};
    virtual bool parse(); // returns true if parse was successful
  private:
    vector<ASTNode*> expressions;
};

class ASTNodeFunctionCall : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeFunctionCall (TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeFunctionCall();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* identifier;
    ASTNode* actualParams;
};

class ASTNodeSubExpression : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeSubExpression (TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeSubExpression();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* expression;
};

class ASTNodeUnary: virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeUnary (TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeUnary();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* expression;
};

class ASTNodeFactor: virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeFactor(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeFactor();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* node;
};

class ASTNodeTerm: virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeTerm(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeTerm();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode *factor;
    vector<ASTNode*> multiplicativeOP;
    vector<ASTNode*> factors;
};

class ASTNodeSimpleExpression: virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeSimpleExpression(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeSimpleExpression();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode *term;
    vector<ASTNode*> additiveOP;
    vector<ASTNode*> terms;
};

class ASTNodeExpression: virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeExpression(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeExpression();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode *simpleExpression;
    vector<ASTNode*> relationalOp;
    vector<ASTNode*> simpleExpressions;
};

class ASTNodeAssignment: virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeAssignment(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeAssignment();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode *identifier;
    ASTNode *expression;
};

class ASTNodeVariableDecl : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeVariableDecl(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeVariableDecl();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* identifier;
    ASTNode* type;
    ASTNode* expression;
};

class ASTNodeReturnStatement : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeReturnStatement(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeReturnStatement();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* expression;
};

class ASTNodeIfStatement : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeIfStatement(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeIfStatement();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* expression;
    ASTNode* block;
    ASTNode* elseBlock;
};

class ASTNodeForStatement : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeForStatement(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeForStatement();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* variableDecl;
    ASTNode* expression;
    ASTNode* assignment;
    ASTNode* block;
};

class ASTNodeFormalParam : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeFormalParam(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeFormalParam();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* identifier;
    ASTNode* type;
};

class ASTNodeFormalParams : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeFormalParams(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeFormalParams();
    virtual bool parse(); // returns true if parse was successful
  private:
    vector<ASTNode*> formalParams;
};

class ASTNodeFunctionDecl : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeFunctionDecl(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeFunctionDecl();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* identifier;
    ASTNode* formalParams;
    ASTNode* type;
    ASTNode* block;
};

class ASTNodeStatement : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeStatement(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeStatement(void);
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* statement; // statement node
};

class ASTNodeBlock : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeBlock(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeBlock();
    virtual bool parse(); // returns true if parse was successful
  private:
    vector<ASTNode*> statements; // statement nodes (multiple)
};

class ASTNodeProgram : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeProgram(TokenManager *tokenManager) : ASTNode(tokenManager) {};
    virtual ~ASTNodeProgram();
    virtual bool parse(); // returns true if parse was successful
  private:
    vector<ASTNode*> statements; // statement nodes (multiple)
};

#endif // ASTNODE_H