env = Environment()
env.Append(CXXFLAGS = [ "-g", "-O0", "-ansi", "-pedantic", "-Wall", "-Weffc++", "-Wconversion", "-Werror" ])
env.Program("expr", [ "expr.cpp",
                      "lexer.cpp",
                      "parser.cpp",
                      "token.cpp",
                      "value.cpp",
                      "environment.cpp",
                      "print_visitor.cpp",
                      "eval_visitor.cpp"
                      ] )

env.Program("lexer_test", [ "lexer_test.cpp",
                            "lexer.cpp",
                            "parser.cpp",
                            "token.cpp",
                            "value.cpp",
                            "environment.cpp" ] )

# EOF #
