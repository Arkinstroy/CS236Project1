cmake_minimum_required(VERSION 3.20)
project(CS236Project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS236Project1
        Automaton.h
        AddAutomaton.cpp
        AddAutomaton.h
        CommaAutomaton.cpp
        CommaAutomaton.h
        CommentAutomaton.cpp
        CommentAutomaton.h
        FactsAutomaton.cpp
        FactsAutomaton.h
        IDAutomaton.cpp
        IDAutomaton.h
        LeftParenAutomaton.cpp
        LeftParenAutomaton.h
        MultiplyAutomaton.cpp
        MultiplyAutomaton.h
        PeriodAutomaton.cpp
        PeriodAutomaton.h
        QueriesAutomaton.cpp
        QueriesAutomaton.h
        QuestionMarkAutomaton.cpp
        QuestionMarkAutomaton.h
        RightParenAutomaton.cpp
        RightParenAutomaton.h
        RulesAutomaton.cpp
        RulesAutomaton.h
        SchemesAutomaton.cpp
        SchemesAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h)
