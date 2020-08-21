@256
D=A
@SP
M=D
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// EQ

// equality compare value
@eq_val // setup
// go to setup
@BEFORE_EQ // start
// equality function (true)
(IS_EQ)
   @eq_val // get value
   M=-1 // true
   @AFTER_EQ // post set function
   0;JMP
// equality function (false)
(NOT_EQ)
   @eq_val // get value
   M=0 // false
   @AFTER_EQ // post set function
   0;JMP
// setup function
(BEFORE_EQ)
   @SP // go to stack pointer
   M=M-1 // decrement value
   A=M // go to top of stack
   D=M // store value in D
   M=0 // clear value
   @SP // go to stack pointer
   M=M-1 // decrement
   A=M // go to next value
   D=D-M // subtract
   @IS_EQ // set dest for true
   D;JEQ // jump if 0
   @NOT_EQ // set dest for false
   D;JNE // jump if not 0
// cleanup function
(AFTER_EQ) // after set value
   @eq_val // load return val
   D=M // store val
   @SP // go to stack pointer
   A=M-1 // go to top value
   M=D; // set value
@17
D=A
@SP
A=M
M=D
@SP
M=M+1
@16
D=A
@SP
A=M
M=D
@SP
M=M+1

// EQ

// equality compare value
@eq_val // setup
// go to setup
@BEFORE_EQ // start
// equality function (true)
(IS_EQ)
   @eq_val // get value
   M=-1 // true
   @AFTER_EQ // post set function
   0;JMP
// equality function (false)
(NOT_EQ)
   @eq_val // get value
   M=0 // false
   @AFTER_EQ // post set function
   0;JMP
// setup function
(BEFORE_EQ)
   @SP // go to stack pointer
   M=M-1 // decrement value
   A=M // go to top of stack
   D=M // store value in D
   M=0 // clear value
   @SP // go to stack pointer
   M=M-1 // decrement
   A=M // go to next value
   D=D-M // subtract
   @IS_EQ // set dest for true
   D;JEQ // jump if 0
   @NOT_EQ // set dest for false
   D;JNE // jump if not 0
// cleanup function
(AFTER_EQ) // after set value
   @eq_val // load return val
   D=M // store val
   @SP // go to stack pointer
   A=M-1 // go to top value
   M=D; // set value
@16
D=A
@SP
A=M
M=D
@SP
M=M+1
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

// EQ

// equality compare value
@eq_val // setup
// go to setup
@BEFORE_EQ // start
// equality function (true)
(IS_EQ)
   @eq_val // get value
   M=-1 // true
   @AFTER_EQ // post set function
   0;JMP
// equality function (false)
(NOT_EQ)
   @eq_val // get value
   M=0 // false
   @AFTER_EQ // post set function
   0;JMP
// setup function
(BEFORE_EQ)
   @SP // go to stack pointer
   M=M-1 // decrement value
   A=M // go to top of stack
   D=M // store value in D
   M=0 // clear value
   @SP // go to stack pointer
   M=M-1 // decrement
   A=M // go to next value
   D=D-M // subtract
   @IS_EQ // set dest for true
   D;JEQ // jump if 0
   @NOT_EQ // set dest for false
   D;JNE // jump if not 0
// cleanup function
(AFTER_EQ) // after set value
   @eq_val // load return val
   D=M // store val
   @SP // go to stack pointer
   A=M-1 // go to top value
   M=D; // set value
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@892
D=A
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@891
D=A
@SP
A=M
M=D
@SP
M=M+1
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1
@57
D=A
@SP
A=M
M=D
@SP
M=M+1
@31
D=A
@SP
A=M
M=D
@SP
M=M+1
@53
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
A=A-1
D=D+M
M=D
A=A+1
M=0
@112
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
A=A-1
D=D-M
M=D
A=A+1
M=0
@SP
A=M-1
M=-M
@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M&D
@SP
M=M+1
@82
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
M=M|D
@SP
M=M+1
@SP
A=M-1
M=!M
(END)
   @END
   0;JMP
