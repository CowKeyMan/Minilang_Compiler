#include "TokenManager.h"

Token TokenManager::nextToken(){
  return tokens->at(tokenIndex++);
}

Token TokenManager::peekToken(){
  return tokens->at(tokenIndex);
}