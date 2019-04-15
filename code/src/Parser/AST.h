#ifndef  AST_H
#define AST_H

#include <memory>
#include "TokenManager.h"

using std::shared_ptr;

class ASTNode{
  public:
    ASTNode(shared_ptr<TokenManager> _tokenManager){ tokenManager = _tokenManager; };
    virtual ~ASTNode(){};
    virtual bool parse() = 0; // returns true if parse was successful
    // ASTNode *parseOptional();
    // vector<ASTNode*> parseMultiple();
  protected:
    shared_ptr<TokenManager> tokenManager;
    Token *match(TokenType tokenType); // match a TokenType, make sure it exists
};

class ASTNodeType : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeType(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeType(){};
    virtual bool parse(); // returns true if parse was successful
  private:
    Token* token; 
};

class ASTNodeLiteral : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeLiteral(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeLiteral(){};
    virtual bool parse(); // returns true if parse was successful
  private:
    Token* token;
};

class ASTNodeIdentifier : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeIdentifier(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeIdentifier(){};
    virtual bool parse(); // returns true if parse was successful
  private:
    Token* token;
};

class ASTNodeMultiplicativeOp : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeMultiplicativeOp(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeMultiplicativeOp(){};
    virtual bool parse(); // returns true if parse was successful
  private:
    Token* token;
};

class ASTNodeAdditiveOp : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeAdditiveOp (shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeAdditiveOp (){};
    virtual bool parse(); // returns true if parse was successful
  private:
    Token* token; // statement node
};

class ASTNodeRelationalOp : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeRelationalOp (shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeRelationalOp(){};
    virtual bool parse(); // returns true if parse was successful
  private:
    Token* token;
};

class ASTNodeActualParams : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeActualParams (shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeActualParams(){};
    virtual bool parse(); // returns true if parse was successful
  private:
    vector<ASTNode*> expressions;
};

class ASTNodeFunctionCall : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeFunctionCall (shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeFunctionCall();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* identifier;
    ASTNode* actualParams;
};

class ASTNodeSubExpression : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeSubExpression (shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeSubExpression();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* expression;
};

class ASTNodeUnary: virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeUnary (shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeUnary();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* expression;
};

class ASTNodeFactor: virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeFactor(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeFactor();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* node;
};

class ASTNodeTerm: virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeTerm(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
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
    ASTNodeSimpleExpression(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
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
    ASTNodeExpression(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
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
    ASTNodeAssignment(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeAssignment();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode *identifier;
    ASTNode *expression;
};

class ASTNodeVariableDecl : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeVariableDecl(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
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
    ASTNodeReturnStatement(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeReturnStatement();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* expression;
};

class ASTNodeIfStatement : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeIfStatement(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
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
    ASTNodeForStatement(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
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
    ASTNodeFormalParam(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeFormalParam();
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* identifier;
    ASTNode* type;
};

class ASTNodeFormalParams : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeFormalParams(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeFormalParams();
    virtual bool parse(); // returns true if parse was successful
  private:
    vector<ASTNode*> formalParams;
};

class ASTNodeFunctionDecl : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeFunctionDecl(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
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
    ASTNodeStatement(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeStatement(void);
    virtual bool parse(); // returns true if parse was successful
  private:
    ASTNode* statement; // statement node
};

class ASTNodeBlock : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeBlock(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeBlock();
    virtual bool parse(); // returns true if parse was successful
  private:
    vector<ASTNode*> statements; // statement nodes (multiple)
};

class ASTNodeProgram : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeProgram(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeProgram();
    virtual bool parse(); // returns true if parse was successful
  private:
    vector<ASTNode*> statements; // statement nodes (multiple)
};

#endif // ASTNODE_H