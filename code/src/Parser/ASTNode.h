#ifndef  ASTNODE_H
#define ASTNODE_H

#include <memory>
#include "TokenManager.h"

using std::shared_ptr;

class ASTNode{
  public:
    ASTNode(shared_ptr<TokenManager> _tokenManager){ tokenManager = _tokenManager; };
    virtual ~ASTNode(void){};
    virtual void parse() = 0;
    bool parseOptional();
    void parseMultiple();
  protected:
    shared_ptr<TokenManager> tokenManager;
    void match(TokenType tokenType); // match a TokenType, make sure it exists
    virtual vector<TokenType> startTokens() = 0; // returns the startTokens
};

class ASTNodeProgram : virtual public ASTNode{
  public:
    ASTNodeProgram(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
    virtual ~ASTNodeProgram(void){};
    virtual void parse(){};
  protected:
    vector<TokenType> startTokens(){ return _startTokens; };
  private:
    vector<ASTNode*> statements; // statement node
    static vector<TokenType> _startTokens;
};

// class ASTNodeStatement : virtual public ASTNode{
//   public:
//     ASTNodeStatement(shared_ptr<TokenManager> tokenManger) : ASTNode(tokenManager) {};
//     void parse();
//   private:
//     // VariableDecl/Assignemnt/PrintStatemenet/
//     // IfStatement/ForStatementReturnStatement/FunctionDecl/Block
//     ASTNode* node; 
// };

#endif // ASTNODE_H