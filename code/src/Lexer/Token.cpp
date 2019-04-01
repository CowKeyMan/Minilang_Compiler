#include "Token.h"
#include "../Helper/helper.h"
#include <stdlib.h>
#include <iostream>

// Used to check if a given string is a keyword (or identifier), and what type of keyword it is
struct Keyword{
  string text;
  Token::TokenType tok_type;
};

Keyword mykeywords[] = {
  {"and", Token::AND},
  {"or", Token::OR},
  {"not", Token::NOT},
  {"if", Token::IF},
  {"else", Token::ELSE},
  {"for", Token::FOR},
  {"while", Token::WHILE},
  {"fn", Token::FN},
  {"return", Token::RETURN},
  {"bool", Token::BOOL},
  {"float", Token::FLOAT},
  {"int", Token::INT},
  {"var", Token::VAR},
  {"true", Token::BOOL},
  {"false", Token::BOOL}
};

Token::TokenType keyword_or_id(string s){
  for(int i = 0; i < arraysize(mykeywords); ++i){
    if(s == mykeywords[i].text){
      return mykeywords[i].tok_type;
    }
  }
  return Token::ID;
}
