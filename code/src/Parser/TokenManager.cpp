#include "TokenManager.h"

#include <iostream>

Token *TokenManager::nextToken(){
  if(tokenIndex+1 < tokens->size()){
    return &tokens->at(tokenIndex++);
  }
  return nullptr;
}

Token *TokenManager::peekToken(int steps){
  std::cout << "HELLOFROMABOVE\n";
  std::cout << tokens << "\n";
  tokens->at(0).printToken();
  if(tokenIndex+steps < tokens->size()){
    std::cout << "HELLOFROMABOVE2\n";
    return &tokens->at(tokenIndex + steps);
  }
  std::cout << "HELLOFROMABOVE3\n";
  return nullptr;
}

Token *TokenManager::peekToken(){
  return peekToken(1);
}

Token *TokenManager::currentToken(){
  return peekToken(0);
}
