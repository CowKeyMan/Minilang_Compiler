#include "Helper/helper.h"
#include "Lexer/Lexer.h"

#include <iostream>
#include <fstream>

#define FILENAME "input.txt"

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

  // cout << file;

  cout << keyword_or_id("if");
  Token a;
}

void cleanup(){
  if(file){
    delete file;
  }
}
