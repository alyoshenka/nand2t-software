@256
D=A
@SP
M=D
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
@1
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
0;JMP
 // actually go// equality function (true)
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
   A=M-1 // go to next value
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
(END)
   @END
   0;JMP
