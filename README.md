# Command Line Calculator

A C++ program that implements an interpreter for arithmetic calculations and simple memory management. To use it, simply compile the .cpp files in the src directory. Using the g++ compiler in Git Bash, it can be done with the command:

```
g++ src/*.cpp -o main.exe
```

Afterwars, execute the resulting .exe file. In Git Bash:

```
./main.exe
```

### Arithmetic Operators

The supported arithmetic binary operations are listed below in order of increasing priority:

- `+` (addition);
- `-` (subtraction);
- `*` (multiplication);
- `%` (modulo): 
  - Calculates remainder of division;
  - Accepts floating point operands;
- `//` (truncated division): 
  - Calculates quotient of division;
  - Accepts floating point operands
- `/` (division);
- `^` (exponentiation).

*Obs: the operators `+` and `-` can be unary.*

### Assignment Operators

Assignment operators always operate on a variable (left) and an expression (right). Each of the above operations has an "assignment operator" version. The assignment operator `=` simply stores the result of the expression on the variable, and is the only operator that can create a variable. The other assignment operators apply an arithmetic operation to the value stored by the variable and the expression, and then store the result in the variable. All assignment operators are listed below in order of increasing priority:

- `+=` (addition assignment);
- `-=` (subtraction assignment): as addition assignment;
- `*=` (multiplication assignment): as addition assignment;
- `%=` (modulo assignment): as addition assignment;
- `//=` (truncated division assignment): as addition assignment;
- `^=` (subtraction assignment): as addition assignment;
- `=` (assignment).

*Obs: all assignment operators have lower priority than the arithmetic operators. The "=" assignment operator has the highest priority among them.*

 ### Expressions
 
 Expressions are strings containing numbers (or varibles) and the above operations. They can always be reduced to a single number by the application of the operations, following their priorities and considering the usage of parentheses. The result of an expression inputed by the user is shown in the following line. Here are some examples of valid expressions:
 
```
>> (1+0.5)*3*10/2 + 5*2 + 1
   33.5
>> -2.5+(2+7.2)*6
   52.7
```

Invalid expressions will trigger errors:

```
>> 3*2+
   Expected expression after + operator.
>> 7/(2-2*1)
   Division by zero.
>> *1+7
   Expected expression before * operator.
```

*Obs: whitespace between the operators, numbers and variables is ignored.*
 
 ### Variables
 
 A variables is a name that can store the result of an expression. They can be created with the assignment operator `=`. They can also be updated with the use of `=` or other assignment operators, such as `+=`, `*=`, etc. There are some examples of correct usage below:
 
 ```
>> var1 = 1.5 + 2
   3.5
>> var2 = var1*10
   35
>> var2 += 3
   38
>> var1 //= 2
   1
```

Trying to use a varible before it was created, either as an operand for an arithmetic operation or with the use of an assignment operator other than `=`, will inevitably result in an error:

 ```
>> undef_var + 2
   Undefined variable: 'undef_var'
>> undef_var += 5
   Undefined variable: 'undef_var'
```

Notice that each assignment operation is itself an expression, as can be seen by the results shown below them. That is because an assignment operation always returns the value that was stored in the variable. That property can be used cleverly to create/update multiple variable in a cascading way:

```
>> b = 2
   2
>> a = b = c = 7
   7
>> a
   7
>> b
   7
```

That is possible because, having the same priority, the operators `=` are evaluated left to right. Since other assignment operators have less priority, the must come before in that cascade. That can be worked around with the use of parentheses.

```
>> a = 2
   2
>> a += b = 5
   7
>> b
   5
>> a = b += 6
   Left hand side of assignment operator (5.000000) must be a variable.
>> a
   5
>> a = (b += 6)
   11
```

The fourth input line fails because the `=` operator has higher priority than the `+=` operator, thus it is executed first. However, `=` returns a number, not a variable, as required by `+=` on its left had side. Therefore, in a cascade of assignment operators, the lower priority operators should always come first. On the other hand, notice that, even though the fourth input failed, the operation `a = b` was executed, as it can be seen that `a` holds `5` afterwards. Hence, cascading different assignment operators can be quite dangerous, and explicit ordering with parentheses is recomended even if in the correct order.

When naming variables, there are some rules that must be followed:

- All variable names must contain only alphaumeric characters or the special character `_` (*e.g.* `var1`, `big_number`, `_var5_esp` are valid);
- They must not start with a digit (*e.g.* `2var`, `5_of_number` are invalid).

### Interface

The interpreter signals with `>>` the place for user input. The result of the inputed expression is shown below the input line. However, showing the output can be supressed by the use of a trailing semicolon. That property can be quite advantageous when creating varables:

```
>> a = 2;
>> b = a + 3;
>> b
   5
```

The variable `_` is always available (does not have to be created) and stores the value of the last expression:

```
>> 1 + 2 + 3 + 4;
   10
>> _*3
   30
>> c = _;
>> c
   30
```

The program can be exited at any time with the `exit()` command:

```
>> exit()
```
