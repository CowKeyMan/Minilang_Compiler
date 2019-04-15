#include "TokenManager.h"

Token *TokenManager::nextToken(){
  if(tokenIndex+1 < tokens->size()-1){
    return &tokens->at(tokenIndex++);
  }
  return nullptr;
}

Token *TokenManager::peekToken(int steps){
  if(tokenIndex+steps < tokens->size()-1){
    return &tokens->at(tokenIndex + steps);
  }
  return nullptr;
}

Token *TokenManager::peekToken(){
  return peekToken(1);
}

Token *TokenManager::currentToken(){
  return peekToken(0);
}
