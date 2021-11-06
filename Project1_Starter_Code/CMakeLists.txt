project(Project1_Starter_Code)
cmake_minimum_required(VERSION 3.16.3)


set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project1_Starter_Code
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h
        CommaAutomaton.h
        CommaAutomaton.cpp
        PeriodAutomaton.cpp
        PeriodAutomaton.h
        Q_MarkAutomaton.cpp
        Q_MarkAutomaton.h
        Left_ParenAutomaton.cpp
        Left_ParenAutomaton.h
        Right_ParenAutomaton.cpp
        Right_ParenAutomaton.h
        MultiplyAutomaton.cpp
        MultiplyAutomaton.h
        AddAutomaton.cpp
        AddAutomaton.h
        SchemesAutomaton.cpp
        SchemesAutomaton.h
        FactsAutomaton.cpp
        FactsAutomaton.h
        QueriesAutomaton.cpp
        QueriesAutomaton.h
        IDAutomaton.cpp
        IDAutomaton.h
        RulesAutomaton.cpp
        RulesAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        LComAutomaton.cpp
        LComAutomaton.h
        Parser.cpp
        Parser.h
        DatalogProgram.cpp
        DatalogProgram.h
        Parameter.cpp
        Parameter.h
        Predicate.cpp
        Predicate.h
        Rule.cpp
        Rule.h
        Tuple.cpp
        Tuple.h
        Header.cpp
        Header.h
        Relation.cpp
        Relation.h
        DataBase.cpp
        DataBase.h
        Interpreter.cpp
        Interpreter.h)
