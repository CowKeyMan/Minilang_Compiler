#include "Lexer.h"
#include "../Helper/Helper.h"
#include <iostream>

Lexer::Lexer(string _file){
  file = _file;
  fileIndex = 0;
}

char Lexer::nextChar(){
  return file[fileIndex++];
}

void Lexer::lex(){
  char c;
  State state = STA; // start state

  string lexeme = "";

  do{ // read character by character until end of file
    char c = nextChar();
    lineNumber++;
    State newState = transitionTable[state] [getColumn(c)];
    if(newState = ERR){ // if at an error state
      process_lexeme(lexeme, state);
      lexeme = c; //start new lexeme with c
    }else{
      lexeme += c; // append c to lexeme
      state = newState;
    }
  }while(c != EOF);
}

int Lexer::getColumn(char c){
  switch (c){
    case '+':
    case '(':
    case ')':
    case '{':
    case '}':
    case ';':
    case ':':
    case ',':
      return 0;
    break;
    
    case '!':
      return 1;
    break;

    case '.':
      return 2;
    break;

    case '/':
      return 5;
    break;

    case '\n':
      return 6;
    break;

    case '*':
      return 7;
    break;

    case '=':
      return 8;
    break;

    case ' ':
    case '\t':
      return 9;
    break;

    case '<':
    case '>':
      return 10;
    break;

    default:
      if(isdigit(c)){
        return 3;
      }else if(isalpha(c) || c == '_'){
        return 4;
      }else{
        return 11;
      }
  }
}

void Lexer::process_lexeme(string lexeme, State state){
  string temp; // needed in cases S10 and S12
  int lexeme_length; // needed in cases S10 and S12

  switch(state){
    case S00: // +(){};:
      tokens.push_back(processNormalPunctuation(lexeme));
    break;

    case S02: // !=
      tokens.push_back(Token(Token::NE, lexeme, 0.0f));
    break;
    
    case S03: // integer
      tokens.push_back(Token(Token::INT, lexeme, stoi(lexeme)));
    break;
    
    case S05: // float
      tokens.push_back(Token(Token::FLOAT, lexeme, stof(lexeme)));
    break;
    
    case S06: // random string (keyword or alpha)
      tokens.push_back(processAlpha(lexeme));
    break;
    
    case S07: // /
      tokens.push_back(Token(Token::DIVISION, lexeme, 0.0f));
    break;
    
    case S10: // multi line comment
      lexeme_length = lexeme.length();
      temp.assign(lexeme, 2, lexeme_length-4); // trim '/*' and '*/'
      tokens.push_back(Token(Token::COMMENT, temp, 0.0f));
    break;
 
    case S12: // single line comment
      lexeme_length = lexeme.length();
      temp.assign(lexeme, 2, lexeme_length-2); // trim '//'
      tokens.push_back(Token(Token::COMMENT, temp, 0.0f));
    break;

    case S13: // =
      tokens.push_back(Token(Token::EQ, lexeme, 0.0f));
    break;

    case S14: // ==
      tokens.push_back(Token(Token::EQQ, lexeme, 0.0f));
    break;

    case S15: // <>
      tokens.push_back(processNormalPunctuation(lexeme));
    break;

    case S16: // <= >=
      if(lexeme == "<="){
        tokens.push_back(Token(Token::ST, lexeme, 0.0f));
      }else{
        tokens.push_back(Token(Token::GT, lexeme, 0.0f));
      }
    break;

    case S17: //empty characters
      // do nothing
    break;

    default:
      std::cerr << "Invalid lexeme";
      exit(EXIT_FAILURE);
    break;
  }
}

