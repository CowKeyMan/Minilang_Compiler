#include <string>

using std::string;

class Token{
  public:
    static string TokenString[]; // Stings corresponding to the enum of token types
    enum TokenType{
      ID, BOOL, FLOAT, INT, // ID and constants
      ST, SE, GT, GE, EQQ, NE, AND, OR, NOT, // conditional operators
      EQ, PLUS, MINUS, TIMES, DIVISION, //arithmetic operators
      IF, ELSE, FOR, WHILE, FN, RETURN, TYPE_BOOL, TYPE_FLOAT, TYPE_INT, VAR, //keywords
      COLON, SEMI_COLON, COMMA, //punctuation
      OPEN_BRACKET, CLOSED_BRACKET, OPEN_BRACE, CLOSED_BRACE, //brackets punctuation
      COMMENT
    };

    // the Token parameters
    TokenType type;
    string lexeme = "";
    float number;

    // constructor
    Token (TokenType _type, string _lexeme, float _number){
      type = _type;
      lexeme = _lexeme;
      number = _number;
    }

    // helper method to neatly print the current token
    void printToken();
};

// given a string, it checks if it is a keyword or an identifier
Token processAlpha(string lexeme);
// given a single character string, it checks if it is a singular punctuation (ex. '+','-',';' etc)
Token processNormalPunctuation(string lexeme);