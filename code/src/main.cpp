#include "Helper/helper.h"
#include "Lexer/Lexer.h"

#include <iostream>
#include <fstream>

#define FILENAME "src/input.txt"

using std::cout;
using std::string;

void readFile(string &s){
  std::ifstream ifs(FILENAME);
  if(ifs){ // if the file was read properly
    std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    s = str;
  }else{
    std::cerr << "Error, could not read file\n";
    exit(EXIT_FAILURE);
  }
}

string *file;
int main(){
  atexit(cleanup);

  file = new string();
  readFile(*file);
  // cout << *file;

  // cout << std::stof(".45");
  string lexeme = "/* abcdefg */";
  string temp;
  int lexeme_length = lexeme.length();
  temp.assign(lexeme, 2, lexeme_length-4); // trim '//'

  Lexer lexer = Lexer(*file);
  lexer.lex();
  vector<Token> tokens = lexer.get_tokens();
  for(int i = 0; i < tokens.size(); ++i){
    tokens[i].printToken();
  }
}

void cleanup(){
  if(file){
    delete file;
  }
}
