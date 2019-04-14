#ifndef  AST_H
#define AST_H

#include <memory>
#include "TokenManager.h"

using std::shared_ptr;

class ASTNode{
  public:
    ASTNode(shared_ptr<TokenManager> _tokenManager){ tokenManager = _tokenManager; };
    virtual ~ASTNode(void){};
    virtual bool parse() = 0; // returns true if parse was successful
    // ASTNode *parseOptional();
    // vector<ASTNode*> parseMultiple();
  protected:
    shared_ptr<TokenManager> tokenManager;
    void match(TokenType tokenType); // match a TokenType, make sure it exists
    virtual vector<TokenType> startTokens() = 0; // returns the startTokens
};

class ASTNodeProgram : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeProgram(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeProgram(void){};
    virtual bool parse(); // returns true if parse was successful
  protected:
    vector<TokenType> startTokens(){ return _startTokens; };
  private:
    vector<ASTNode*> statements; // statement nodes (multiple)
    static vector<TokenType> _startTokens;
};

class ASTNodeStatement : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeStatement(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeStatement(void){};
    virtual bool parse(); // returns true if parse was successful
  protected:
    vector<TokenType> startTokens(){ return _startTokens; };
  private:
    ASTNode* statement; // statement node
    static vector<TokenType> _startTokens;
};

class ASTNodeVariableDecl : virtual public ASTNode{
  public:
    // costructor is same as parent
    ASTNodeVariableDecl(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeVariableDecl(void){};
    virtual bool parse(); // returns true if parse was successful
  protected:
    vector<TokenType> startTokens(){ return _startTokens; };
  private:
    ASTNode* statement; // statement node
    static vector<TokenType> _startTokens;
};

#endif // ASTNODE_H