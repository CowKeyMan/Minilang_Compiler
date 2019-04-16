#include "TokenManager.h"
#include <iostream>

Token *TokenManager::nextToken(){
  if(tokenIndex < tokens->size()){
    Token *ret = &tokens->at(tokenIndex);
    tokenIndex++;
    return ret;
  }
  return nullptr;
}

Token *TokenManager::peekToken(int steps){
  if(tokenIndex+steps < tokens->size()){
    return &tokens->at(tokenIndex + steps);
  }
  return nullptr;
}

Token *TokenManager::peekToken(){
  return peekToken(0);
}