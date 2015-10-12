# Avocado

Avocado is a tiny programming language, implemented using Lex and Yacc.

## Syntax overview

The syntax is fairly simple.

Statements must be terminated with semicolons;

#### Variable semantics

Variables are declared using the `var` keyword, a la Javascript:
```
var x;
```
Variables can be assigned to using `=`, once they have been declared.
```
x = 5;
```
Variables can also be declared and initialized in one fell swoop:
```
var y = 5;
```
Variables can hold floating-point numbers as well:
```
var f = 5.34;
```
String literals are enclosed in single (or double) quotes. Variables can hold strings.
```
var h = 'Hello, world!';
var i = "I love ice cream!";
```
Variables and expressions can be interpolated into double-quoted strings using curly braces, like so:
```
var age = 1000;
var forsaken = "I am {age} years old."; // contains "I am 1000 years old."
var birthday = "Next year I'll be {age+1} years old."; // contains "Next year I'll be 1001 years old."
```
Lists of values are enclosed in square brackets; they are also subscripted with angle brackets. You can't assign to list elements at the moment, but I'm working on it. List subscripts start at 0.
```
var list = [1, 2, 3, 4, 5];
print list[3];  // prints '4'
print list;     // prints '1 2 3 4 5'
```
A variable declared with `var` lasts until its current scope (i.e. block of curly braces) ends. Anything that has curly braces has its own scope, even `if`s and `while`s.
```
var x = 2;
var y = 5;
{
    var x = 6;
    print x; // prints 6
    print y; // prints 5, since a new y has not been declared
}
print x; // prints 2; the x = 6 is now out of scope
print y; // still prints 5
```
Functions are declared with the `def` keyword, and called by using their name. Functions are actually just variables. Calling and defining functions does not need parentheses, except to avoid ambiguity. Functions can be defined using parentheses if you want. Also, functions that just return an expression do not need a block; they do need the keyword `as`.

**Note: these semantics may change at any time as they're sort of confusing**
```
def println (x) {
    print x:"\n";
}
// (equivalent to)
def println x {
    print x:"\n";
}

def add x, y as x + y;

println add 4, 5; // prints "9\n"
```
(Note: Functions without parameters do need to be called with an empty pair of parentheses `()`; otherwise it will assume you are talking about the variable that holds the function, not intending to execute the function.)
(Note: Return values from functions with blocks don't really work right. I am working on it.)
(Actually, the current one in the repository might not support return values at all; it will soon, though.)

#### Operators and things like that

Comments are preceded by a `//`, and last until the end of the line:
```
// This is a comment
```
The `:` operator is used for concatenation of strings (and numbers):

**Note: this may also change in the future**
```
var h5 = h:y;
// h5 now contains the string 'Hello, world!5'
var h_i = h:' ':i;
// h_i now contains the string 'Hello, world! I love ice cream!'
```
You can use `+`, `-`, `*`, and `/` to add, subtract, multiply, and divide variables.
```
var z = x + y;
// z now contains 10 (i.e. 5 + 5)
```
You can construct arbitrarily complex expressions as well:
```
var c = h:x+4:(y*2)+5:'blah':6;
// c now contains, uhh... 'Hello, world!915blah6'
```
You can print out the value of any variable or expression with the `print` keyword:
```
print x;        // prints 5
print x+6;      // prints 11
print x:'t';    // prints 5t
print h:x;      // prints Hello, world!5
```
I've stolen the comparison operators from Perl. Variables are coerced into whichever form you are comparing them as.
```
==  numeric equality
!=  numeric inequality
<=  numeric less-than-or-equal-to
>=  numeric greater-than-or-equal-to
<   numeric less-than
>   numeric greater-than
eq  string equality
ne  string inequality
le  string less-than-or-equal-to
ge  string greater-than-or-equal-to
lt  string less-than
gt  string greater-than
```
You can do compound assignment with `+=`, `-=`, `*=`, `/=`, and `:=` (concatenation).
```
var x = 5;
x += 2; // x is now 7. This is exactly equivalent to writing 'x = x + 2'.
```

#### Booleans and tests

The special values `true`, `false`, and `nothing` can also be assigned to variables:
```
var yes = true;
var no = false;
var ghosts = nothing;
```
You can evaluate variables with the `if`, `else`, and `while` statements. `nothing`, `false`, 0, and the empty list evaluate to false; everything else evaluates to true (even the string '0').
```
if yes {
    print 'Yes!';
}
// prints 'Yes!'

if no {
    print 'No!';
}
// doesn't print anything

if ghosts {
    print 'Ghosts exist!';
} else {
    print "Ghosts aren't real.";
}
// prints 'Ghosts aren't real.'

var w = 5;
while w > 0 {
    print w;
    w = w - 1;
}
// prints '54321'
```

#### Other stuff

Strings can be coerced into integers if you so desire:
```
var ten = 2 * '5';      // ten = 10
var five = '5';
var ten2 = 2 * five;    // ten2 also = 10
```
By surrounding a string expression with backticks, you can access the value of the variable referred to by that expression.

**Note: this might not actually work and will be removed very soon**
```
var ref = 'foo';
var ref2 = 'fo';
var foo = 'hello';
var hello = 'world';

print `ref`;        // prints value of variable foo, 'hello'
print `ref2:'o'`;   // also prints hello
print ``ref``;      // prints 'world' (``ref`` -> `foo` -> hello)
```
Newlines and tabs can be escaped in double-quoted strings via `\n` and `\t`.
```
print "\t":x:"\n";   // prints 5, preceded by a tab and followed by a newline
```
