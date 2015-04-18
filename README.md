Expr
====

Expr is a simple toy scripting language in the making. So far it can
handle C-like expressions and can export C++ functions to the
scripting side.


Usage
-----

    $ ./expr 5 + 5
    Syntax Tree: (+ 5 5)
    Expr::eval(): integer:10
    EvalVisitor:  integer:10

    $ ./expr "sqrt(2)"
    Syntax Tree: (sqrt ...)
    Expr::eval(): real:1.414214
    EvalVisitor:  real:1.414214


[![Build Status](https://travis-ci.org/Grumbel/Expr.svg?branch=master)](https://travis-ci.org/Grumbel/Expr)
