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
Strings are enclosed in single quotes. Variables can hold strings.
````
var h = 'Hello, world!';
````
The `:` operator is used for concatenation:
````
var h5 = h:y;
// h5 now contains the string 'Hello, world!5'
````
You can use +, -, *, and / for mathematical operations, although floating-point numbers haven't been implemented yet, so all divisions must be integer divisions.
````
var z = x + y;
// z now contains 10 (5 + 5)
````
You can construct arbitrarily complex expressions as well:
````
var c = h:x+4:(y*2)+5:'blah':6
// c now contains, uhh... 'Hello, world!915blah6'
````
Strings can also be coerced into integers if you so desire:
````
var ten = 2 * '5'; // works
````
Finally, you can print out the value of any variable or expression with the `print` keyword:
````
print x;        // prints 5
print x+6;      // prints 11
print x:'t';    // prints 5t
print h:x;      // prints Hello, world!5
````
Newlines can be escaped in printed strings via `\n`.
````
print x:'\n';   // prints 5, followed by a newline
````
Even though I've been using //... to denote comments, there are actually no comments. I'll implement them eventually.
