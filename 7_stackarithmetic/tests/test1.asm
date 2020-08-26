// initialize SP to 256
@256 // import 256
D=A // set D to 256
@SP // import SP(0)
M=D // set mem to 256

// initialize variables
@cur_func // current function, NO reset
@line_num // line function couter, DOES reset
@push_val // the pushed value

@MAIN
0;JMP // start program

(ADD)
   @SP // go to stack pointer
   M=M-1 // decrement stack
   A=M // go to top of stack
   D=M // store top value
   A=A-1 // get address of next value
   D=D+M // add
   M=D // store
   A=A+1 // get top value
   M=0 // clear
   @MAIN
   0;JMP // return control to main

(SUB)
   @SP // go to stack pointer
   M=M-1 // decrement stack
   A=M // go to top of stack
   D=M // store top value
   A=A-1 // get address of next value
   D=D-M // sub
   M=D // store
   A=A+1 // get top value
   M=0 // clear
   @MAIN
   0;JMP // return control to main

(NEG)
   @SP // go to stack pointer
   A=M-1 // go to top value of stack
   M=-M // negate value
   @MAIN
   0;JMP // return control to main

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
(EQ)
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
   @MAIN
   0;JMP // return control to main

(GT)
   @MAIN
   0;JMP // return control to main

(LT)
   @MAIN
   0;JMP // return control to main

(AND)
   @SP // go to stack pointer
   M=M-1 // decrement value to get first number
   A=M // go to stack
   D=M // store first number
   @SP // go to stack pointer
   M=M-1 // decrement value
   @SP // go to stack pointer
   A=M // go to stack
   M=M&D // calculate value
   @SP // go to stack pointer
   M=M+1 // increment value;
   @MAIN
   0;JMP // return control to main

(OR)
   @SP // go to stack pointer
   M=M-1 // decrement value to get first number
   A=M // go to stack
   D=M // store first number
   @SP // go to stack pointer
   M=M-1 // decrement value
   @SP // go to stack pointer
   A=M // go to stack
   M=M|D // calculate value
   @SP // go to stack pointer
   M=M+1 // increment value
   @MAIN
   0;JMP // return control to main

(NOT)
   @SP // go to stack pointer
   A=M-1 // go to top value of stack
   M=!M // bitwise negation
   @MAIN
   0;JMP // return control to main

// main function loop
(MAIN)
   @cur_func
   M=M+1 // increment
   @line_num
   M=0 // reset line counter

   // import number constant
   @1
   D=M // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=M // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @EQ
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=M // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=M // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @ADD
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=M // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   // import number constant
   @1
   D=M // store address as value
   @push_val
   M=D // set value

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @PUSH
   D;JEQ

   @line_num
   M=M+1 // increment

   @cur_func
   D=M // store value
   @line_num
   A=M // store value
   D=D-A // check to run next func
   @SUB
   D;JEQ

   @line_num
   M=M+1 // increment

   @END
   0;JMP // finish 

(END)
   @END
   0;JMP
