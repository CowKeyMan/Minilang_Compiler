#include "Lexer.h"

Lexer::Lexer(string _file){
  file = _file;
  fileIndex = 0;
}

char Lexer::nextChar(){
  return file[fileIndex++];
}