#include "Token.h"
#include "../Helper/helper.h"
#include <stdlib.h>
#include <iostream>

// Used to check if a given string is a keyword (or identifier), and what type of keyword it is
struct keyword_token{
  string text;
  Token::TokenType tok_type;
};

keyword_token my_keywords[] = {
  {"and", Token::AND},
  {"or", Token::OR},
  {"not", Token::NOT},
  {"if", Token::IF},
  {"else", Token::ELSE},
  {"for", Token::FOR},
  {"while", Token::WHILE},
  {"fn", Token::FN},
  {"return", Token::RETURN},
  {"bool", Token::TYPE_BOOL},
  {"float", Token::TYPE_FLOAT},
  {"int", Token::TYPE_INT},
  {"var", Token::VAR},
  {"true", Token::BOOL},
  {"false", Token::BOOL}
};

Token processAlpha(string lexeme){
  for(int i = 0; i < arraysize(my_keywords); ++i){
    if(lexeme == my_keywords[i].text){
      return Token(my_keywords[i].tok_type, lexeme, 0.0f);
    }
  }
  return Token(Token::ID, lexeme, 0.0f);
}

//struct used to assign tokens to normal punctuation
struct character_token{
  char character;
  Token::TokenType token;
};

character_token normal_punctuation[] = {
  {'+', Token::PLUS},
  {'-', Token::MINUS},
  {'(', Token::OPEN_BRACKET},
  {')', Token::CLOSED_BRACKET},
  {'{', Token::OPEN_BRACE},
  {'}', Token::CLOSED_BRACE},
  {':', Token::COLON},
  {';', Token::SEMI_COLON},
  {',', Token::COMMA},
  {'<', Token::ST},
  {'>', Token::GT},
  {'*', Token::TIMES}
};
// given column 0 (+(){};:), it needs to check which one of these and assign a token
Token processNormalPunctuation(string lexeme){
  for(int i = 0; i < arraysize(normal_punctuation); ++i){
    if(lexeme[0] == normal_punctuation[i].character){
      return {normal_punctuation[i].token, lexeme, 0.0f};
    }
  }
}

void Token::printToken(){
  std::cout << "<" << lexeme << ", " << TokenString[type] << ", " << number << ">\n";
}

string Token::TokenString[] = {
  "ID", "BOOL", "FLOAT", "INT", // ID and constants
  "ST", "SE", "GT", "GE", "EQQ", "NE", "AND", "OR", "NOT", // conditional operators
  "EQ", "PLUS", "MINUS", "TIMES", "DIVISION", //arithmetic operators
  "IF", "ELSE", "FOR", "WHILE", "FN", "RETURN", "TYPE_BOOL", "TYPE_FLOAT", "TYPE_INT", "VAR", //keywords
  "COLON", "SEMI_COLON", "COMMA", //punctuation
  "OPEN_BRACKET", "CLOSED_BRACKET", "OPEN_BRACE", "CLOSED_BRACE", //brackets punctuation
  "COMMENT"
};