Greval
======

Greval is a simple toy scripting language in the making. So far it can
handle C-like expressions and can export C++ functions to the
scripting side.


Usage
-----

    $ greval-eval 5 + 5
    Syntax Tree: (+ 5 5)
    EvalVisitor: integer:10

    $ greval-eval "sqrt(2)"
    Syntax Tree: (sqrt 2)
    EvalVisitor: real:1.414214

