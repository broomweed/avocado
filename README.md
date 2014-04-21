Avocado
=======

Avocado is a tiny programming language, implemented using Lex and Yacc.

What does it do?
----------------

Nothing much, at the moment. It doesn't even have an IF statement. This repository is just for me to track my changes, right now.

Syntax overview
---------------

The syntax is fairly simple.
Statements must be terminated with semicolons.
Variables are declared using the `var` keyword, a la Javascript:
````
var x;
````
Variables can be assigned to using `=`, once they have been declared.
````
x = 5;
````
Variables can also be declared and initialized in one fell swoop:
````
var y = 5;
````
Variables can hold floating-point numbers as well:
````
var f = 5.34;
````
Strings are enclosed in single (or double) quotes. Variables can hold strings.
````
var h = 'Hello, world!';
var i = "I love ice cream!";
````
Comments are preceded by a `//`, and last until the end of the line:
````
// This is a comment
````
The `:` operator is used for concatenation of strings (and numbers):
````
var h5 = h:y;
// h5 now contains the string 'Hello, world!5'
````
You can use `+`, `-`, `*`, and `/` to add, subtract, multiply, and divide variables.
````
var z = x + y;
// z now contains 10 (i.e. 5 + 5)
````
You can construct arbitrarily complex expressions as well:
````
var c = h:x+4:(y*2)+5:'blah':6
// c now contains, uhh... 'Hello, world!915blah6'
````
String variables, but not string literals, can be coerced into integers if you so desire:
````
var ten = 2 * '5';      // doesn't work, syntax error

var five = '5';
var ten2 = 2 * five;
print ten2;             // works, prints 10
````
Finally, you can print out the value of any variable or expression with the `print` keyword:
````
print x;        // prints 5
print x+6;      // prints 11
print x:'t';    // prints 5t
print h:x;      // prints Hello, world!5
````
Newlines and tabs can be escaped in printed strings via `\n` and `\t`.
````
print '\t':x:'\n';   // prints 5, preceded by a tab and followed by a newline
````
