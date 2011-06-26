env = Environment()
env.Append(CXXFLAGS = [ "-g", "-O0", "-ansi", "-pedantic", "-Wall", "-Weffc++" ])
env.Program("expr", [ "expr.cpp", "lexer.cpp", "parser.cpp", "token.cpp" ] )
env.Program("lexer_test", [ "lexer_test.cpp", "lexer.cpp", "parser.cpp", "token.cpp" ] )

# EOF #
