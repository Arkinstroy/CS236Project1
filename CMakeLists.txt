cmake_minimum_required(VERSION 3.20)
project(CS236Project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS236Project1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h)
