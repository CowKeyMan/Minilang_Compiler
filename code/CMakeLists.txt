cmake_minimum_required (VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project (Tutorials C CXX)

add_executable(a src/main.cpp src/Lexer/Token.cpp src/Lexer/Lexer.cpp src/Helper/Helper.cpp src/Parser/TokenManager.cpp src/Parser/Parser.cpp src/Parser/AST.cpp)
set_target_properties(a PROPERTIES LINKER_LANGUAGE CXX)

#[[if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()]]
#[[]]
