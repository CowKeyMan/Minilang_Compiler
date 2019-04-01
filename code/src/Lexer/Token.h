#include <string>

using std::string;

class Token{
  public:
    enum TokenType{
      ID, BOOL, FLOAT, INT, // ID and constants
      ST, SE, GT, GE, EQQ, NE, AND, OR, NOT, // conditional operators
      EQ, PLUS, MINUS, TIMES, DIVISION, //arithmetic operators
      IF, ELSE, FOR, WHILE, FN, RETURN, TYPE_BOOL, TYPE_FLOAT, TYPE_INT, VAR, //keywords
      COLON, SEMI_COLON, COMMA, //punctuation
      OPEN_BRACKET, CLOSED_BRACKET, OPEN_BRACE, CLOSED_BRACE, //brackets punctuation
      COMMENT
    };
    TokenType type;
    string text = "";
    float number;
};

Token::TokenType keyword_or_id(string s);
