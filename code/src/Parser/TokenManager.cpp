#include "TokenManager.h"

Token *TokenManager::nextToken(){
  if(tokenIndex+1 < tokens->size()){
    return &tokens->at(tokenIndex++);
  }
  return nullptr;
}

Token *TokenManager::peekToken(){
  if(tokenIndex+1 < tokens->size()){
    return &tokens->at(tokenIndex + 1);
  }
  return nullptr;
}