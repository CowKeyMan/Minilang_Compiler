#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include "Helper/helper.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

#define TEST_LEXER
#define FILENAME "InputFiles/Input.txt"

using std::cout;
using std::cerr;
using std::string;
using std::istreambuf_iterator;
using std::ifstream;
using std::unique_ptr;
using std::vector;

// read the file specified by the filename and assign it to s
void readFile(string &s);

unique_ptr<string> file;
unique_ptr<Lexer> lexer;
unique_ptr<Parser> parser;

vector<Token> tokens;

int main(){
  // Lexer
  file = unique_ptr<string>( new string() );
  readFile(*file);
  
  lexer = unique_ptr<Lexer>( new Lexer(*file) );
  lexer->lex();
  lexer->removeComments();
#ifdef TEST_LEXER
  lexer->printTokens(); // for debugging purposes
#endif
  tokens = lexer->get_tokens();
  file.reset();
  lexer.reset(); // freeing pointer optimistions

  //DELETE COMMENTS

  // Parser
  parser = unique_ptr<Parser>( new Parser(&tokens) );

  bool successParse = parser->parse();
  cout << (successParse? "\nParsing successful\n" : "\nError while parsing") << "\n";
  if(! successParse){
    cout << "Unexpected token " << tokens[parser->getTokenManagerIndex()].lexeme;
    cout << " at line " << tokens[parser->getTokenManagerIndex()].lineNumber << "\n";
    exit(EXIT_FAILURE);
  }

  ASTNode* tree = parser->getTree();
  
  // Do XML Generation pass and print it to user
  XMLVisitor *xmlv = new XMLVisitor();
  tree->accept(xmlv); // Generate the xml
  xmlv->trimXMLNewLines();
  cout << xmlv->getXML();
  delete xmlv;

  // Do Semantic Analysis pass 
  // (note: program exits during pass if this fails. reporting any necessary errors)
  SAVisitor *sav = new SAVisitor();
  tree->accept(sav);
  cout << "\nSemantic Analysis Succesful\n";
  delete sav;

  // Do Semantic Analysis pass 
  // (note: program exits during pass if this fails. reporting any necessary errors)
  IVisitor *iv = new IVisitor();
  tree->accept(iv);
  cout << "\nProgram finished execution with return value: ";
  // iv->printValue(iv->getReturnValue());
  iv->printValue(iv->getReturnValue()); // example showing bool works
  cout << "\n";
  delete iv;

  parser.reset();
  tokens = vector<Token>();

  return 0;

}

void readFile(string &s){

  ifstream ifs(FILENAME);

  if(ifs){ // if the file was read properly
    string str((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    s = str;
  }else{
    // if the file could not be read report the error and exit
    cerr << "Error, could not read file\n";
    exit(EXIT_FAILURE);
  }
}
